#!/usr/bin/env python3
"""The module's export lists, derived from Abseil's public headers.

The headers are those of the release compat.abseil builds (upstream's own
tarball, pinned with its checksum in upstream/documents.json and fetched into
target/upstream). A public header is `absl/<group>/<name>.h` outside the
`internal/` directories, except the test and mocking headers listed in
EXCLUDED (they need GoogleTest, which the library is not built with).

With --clang <clang++> the headers are read by the compiler and every name
declared in `namespace absl` (Abseil's inline namespace `lts_20250512` is
transparent here, as it is to its users) and in its public nested namespaces
is recorded in tools/surface.json, under the group that exports it:

- a name is exported by the group whose files declare it (a declaration in
  `absl/<group>/internal/…` belongs to that group too), provided that group's
  public headers make it visible; a name no group of its own makes visible is
  exported by the first group (in GROUPS order) whose headers do. A function
  name is exported by every group that declares an overload of it, so that a
  submodule imported alone carries its own operators and overloads; a
  using-declaration carries every overload visible where it is written.
- namespaces whose name ends in `internal` are implementation detail and not
  exported; the record lists them.
- an object or a function at namespace scope with internal linkage (`static`,
  or `constexpr` without `inline`) cannot be exported; the record lists them.
- a name Abseil re-declares from the standard library (`absl::optional` is
  `using std::optional;`) is exported as Abseil's name, so `absl::optional`
  keeps working through the module.

The macros: every object-like macro of the public headers (not
`*INTERNAL*`) whose definitions are integer literals is mapped to a constant
of the same name in mcpplibs::mwrap::abseil::macros — `int` when the macro is
a value (some definition is 0, or it names a number), `bool` "is defined" when
it is a presence flag tested with #ifdef. Every other public macro is
available through <mwrap/abseil/macros.hpp> only; the record lists them.

--write writes src/<group>.cppm, src/abseil.cppm and src/macros.cppm from the
record and include/mwrap/abseil/macros.hpp from the header list.
"""
import argparse
from collections import defaultdict
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys
import tarfile
import tempfile
import urllib.request

ROOT = Path(__file__).resolve().parent.parent
RECORD = ROOT / 'tools/surface.json'
SRC = ROOT / 'src'
MACROS_HPP = ROOT / 'include/mwrap/abseil/macros.hpp'

GROUPS = ('base', 'meta', 'utility', 'memory', 'functional', 'algorithm', 'numeric', 'types', 'hash', 'container', 'strings', 'crc',
          'cleanup', 'debugging', 'synchronization', 'time', 'status', 'random', 'log', 'flags')
# Test and mocking support: these need GoogleTest / GoogleMock, which compat.abseil is not built with.
EXCLUDED = {
    'absl/random/mocking_bit_gen.h': 'needs GoogleMock (absl::MockingBitGen)',
    'absl/random/mock_distributions.h': 'needs GoogleMock (absl::MockUniform …)',
    'absl/log/scoped_mock_log.h': 'needs GoogleMock (absl::ScopedMockLog)',
    'absl/status/status_matchers.h': 'needs GoogleTest matchers (absl_testing::IsOk …)',
    'absl/hash/hash_testing.h': 'needs GoogleTest (absl::VerifyTypeImplementsAbslHashCorrectly)',
    'absl/container/btree_test.h': "upstream's own btree test support",
    'absl/strings/cord_test_helpers.h': "upstream's own Cord test support",
    'absl/strings/cordz_test_helpers.h': "upstream's own Cordz test support (needs GoogleTest)",
}
# Value macros among the integer ones that are never defined to 0 (a number, not a flag).
VALUES = {'ABSL_LTS_RELEASE_VERSION', 'ABSL_LTS_RELEASE_PATCH_LEVEL', 'ABSL_CACHELINE_SIZE', 'ABSL_OPTION_USE_INLINE_NAMESPACE',
          'ABSL_OPTION_USE_STD_ORDERING', 'ABSL_OPTION_USE_STD_STRING_VIEW', 'ABSL_OPTION_HARDENED', 'ABSL_FLAGS_STRIP_NAMES',
          'ABSL_FLAGS_STRIP_HELP'}
# Presence flags that only exist under a sanitizer or a build mode the package is not built in: mapping them
# would say `false` for a property of the consumer's build the module cannot know. Header-only.
CONSUMER_FLAGS = {'ABSL_HAVE_ADDRESS_SANITIZER', 'ABSL_HAVE_HWADDRESS_SANITIZER', 'ABSL_HAVE_LEAK_SANITIZER', 'ABSL_HAVE_MEMORY_SANITIZER',
                  'ABSL_HAVE_THREAD_SANITIZER', 'ABSL_HAVE_DATAFLOW_SANITIZER', 'ABSL_HAVE_EXCEPTIONS'}

# Internal linkage, by name: re-declared under the same name in mcpplibs::mwrap::abseil (a value the header fixes),
# or not exported with the reason (a value that depends on the including translation unit).
ADAPTED = {'absl::kFixedArrayUseDefault'}
NOT_ADAPTED = {'absl::kLogDebugFatal': "its value is kError or kFatal by the consumer's NDEBUG (log_severity.h); "
                                       'include <absl/base/log_severity.h> (or <mwrap/abseil/macros.hpp>) to use it'}

# Names exported under a condition, with the reason. GCC 16 rejects a module that exports the alias template
# absl::Flag (and GetFlag, SetFlag, GetFlagReflectionHandle, which take it): its class, flags_internal::Flag<T>, names the `static constexpr` function template
# StorageKind<T>() in its members' constraints ("exposes TU-local entity", an error, not the warning). On GCC
# the name comes from the header (ABSL_FLAG and ABSL_DECLARE_FLAG need it anyway: <mwrap/abseil/macros.hpp>).
_GCC_FLAG = ('!defined(__GNUC__) || defined(__clang__)', 'GCC 16: flags_internal::Flag<T>, which this name reaches, exposes the TU-local StorageKind<T>()')
CONDITIONAL = {name: _GCC_FLAG for name in ('absl::Flag', 'absl::GetFlag', 'absl::SetFlag', 'absl::GetFlagReflectionHandle')}

# Declarations of the global module fragment that a module must name to keep them reachable: Clang 23 drops a
# declaration the module unit does not reach, and a class template instantiated in an importer (raw_hash_set's
# iterators) befriends absl::container_internal::hashtable_debug_internal::HashtableDebugAccess by its qualified
# name, which then is not there ("no struct named 'HashtableDebugAccess'"). Each module whose headers declare
# the namespace names the template once, unexported. {alias: (namespace, template)}
KEEP = {'hashtable_debug_access': ('absl::container_internal::hashtable_debug_internal', 'HashtableDebugAccess')}

KINDS = {
    'CXXRecordDecl': 'types', 'ClassTemplateDecl': 'types', 'EnumDecl': 'types', 'TypeAliasDecl': 'types', 'TypedefDecl': 'types',
    'TypeAliasTemplateDecl': 'types', 'FunctionDecl': 'functions', 'FunctionTemplateDecl': 'functions', 'VarDecl': 'objects',
    'VarTemplateDecl': 'objects', 'UsingDecl': 'standard',
}
ADL = re.compile(r'operator\W')
MEMBERS = {'CXXMethodDecl', 'CXXConstructorDecl', 'CXXDestructorDecl', 'CXXConversionDecl'}
PASSED = {'UsingDirectiveDecl', 'UsingShadowDecl', 'ClassTemplateSpecializationDecl', 'ClassTemplatePartialSpecializationDecl',
          'CXXDeductionGuideDecl', 'StaticAssertDecl', 'EmptyDecl', 'FriendDecl', 'LinkageSpecDecl', 'FullComment',
          'VarTemplateSpecializationDecl', 'VarTemplatePartialSpecializationDecl', 'ExplicitInstantiationDecl', *MEMBERS}


def fetch():
    """The release's source tree under target/upstream, checked against upstream/documents.json."""
    pins = json.loads((ROOT / 'upstream/documents.json').read_text(encoding='utf-8'))
    cache = ROOT / 'target/upstream'
    cache.mkdir(parents=True, exist_ok=True)
    archive = cache / 'abseil-cpp.tar.gz'
    if not archive.exists() or hashlib.sha256(archive.read_bytes()).hexdigest() != pins['upstream_sha256']:
        print('+ fetch', pins['upstream'], flush=True)
        with urllib.request.urlopen(pins['upstream'], timeout=120) as response:
            archive.write_bytes(response.read())
    digest = hashlib.sha256(archive.read_bytes()).hexdigest()
    if digest != pins['upstream_sha256']:
        sys.exit(f'upstream archive checksum {digest} != {pins["upstream_sha256"]}')
    with tarfile.open(archive) as tar:
        top = tar.getmembers()[0].name.split('/')[0]
        if not (cache / top).exists():
            tar.extractall(cache, filter='data')
    return cache / top


def headers(upstream, group=None):
    """The public headers, of one group or of all, in GROUPS order."""
    out = []
    for name in ([group] if group else GROUPS):
        found = sorted(p.relative_to(upstream).as_posix() for p in (upstream / 'absl' / name).glob('*.h'))
        out += [h for h in found if h not in EXCLUDED]
    return out


def group_of(path):
    match = re.search(r'(?:^|/)absl/([a-z_]+)/', path.replace('\\', '/'))
    return match.group(1) if match else None


def dump(clang, upstream, include):
    with tempfile.TemporaryDirectory(prefix='abseil-surface-') as directory:
        source = Path(directory) / 'all.cpp'
        source.write_text(''.join(f'#include <{h}>\n' for h in include), encoding='utf-8')
        command = [clang, '-std=c++23', '-fsyntax-only', '-w', '-I', str(upstream), '-Xclang', '-skip-function-bodies',
                   '-Xclang', '-ast-dump=json', '-Xclang', '-ast-dump-filter=absl', str(source)]
        text = "\n" + subprocess.run(command, check=True, stdout=subprocess.PIPE, text=True).stdout
    decoder, at, out = json.JSONDecoder(), 0, []
    while True:
        at = text.find('\n{', at - 1 if at else 0)
        if at < 0:
            break
        tree, at = decoder.raw_decode(text, at + 1)
        out.append(tree)
    return out


def annotate(node, state):
    """Give every node the file of its location: clang writes a location's file only when it changes."""
    def touch(loc):
        if 'spellingLoc' in loc:
            touch(loc['spellingLoc'])
            touch(loc.get('expansionLoc', {}))
        elif 'file' in loc:
            state['file'] = loc['file']
    if isinstance(node, dict):
        for key, value in list(node.items()):
            if key == 'loc':
                touch(value)
                node['_file'] = state['file']
            elif key == 'range':
                touch(value.get('begin', {}))
                touch(value.get('end', {}))
            elif key not in ('includedFrom',):
                annotate(value, state)
    elif isinstance(node, list):
        for item in node:
            annotate(item, state)


def internal_linkage(node):
    return node.get('storageClass') == 'static' or (node.get('kind') == 'VarDecl' and not node.get('inline') and node.get('constexpr'))


def declarations(clang, upstream, include):
    """{(scope, name): {'kind': …, 'groups': {…}, 'internal': bool}} and the internal namespaces met."""
    found, skipped, unknown = {}, set(), set()

    def walk(node, scope, hidden=False):
        for child in node.get('inner', []):
            kind, name = child.get('kind'), child.get('name')
            if kind == 'NamespaceDecl':
                if child.get('isInline'):
                    walk(child, scope, hidden)
                elif not name:
                    skipped.add(f'{scope}::(anonymous)')
                elif hidden or name.endswith('internal') or name.startswith('internal'):
                    skipped.add(f'{scope}::{name}')
                    walk(child, f'{scope}::{name}', True)
                else:
                    walk(child, f'{scope}::{name}')
                continue
            if child.get('isImplicit') or not name or kind in PASSED or name.startswith('<'):
                continue
            # In an implementation namespace only the operators: they apply to public types (absl::CivilDay is
            # time_internal::cctz::detail::civil_time<day_tag>) and are found by argument-dependent lookup, which
            # does not see a global-module-fragment declaration the module does not export.
            if hidden and not (kind in ('FunctionDecl', 'FunctionTemplateDecl') and ADL.match(name)):
                continue
            if 'parentDeclContextId' in child or (kind == 'FunctionTemplateDecl' and any(i.get('kind') in MEMBERS for i in child.get('inner', []))):
                continue
            if kind not in KINDS:
                unknown.add(f'{kind} {scope}::{name}')
                continue
            if kind == 'UsingDecl':
                name = name.split('::')[-1]
            entry = found.setdefault((scope, name), {'kind': 'adl' if hidden else KINDS[kind], 'groups': set(), 'internal': False, 'definition': set()})
            group = group_of(child.get('_file') or '')
            if group:
                entry['groups'].add(group)
                if child.get('completeDefinition') or any(i.get('completeDefinition') for i in child.get('inner', []) if isinstance(i, dict)):
                    entry['definition'].add(group)
            if kind in ('VarDecl', 'FunctionDecl') and internal_linkage(child):
                entry['internal'] = True
            if kind == 'EnumDecl' and not child.get('scopedEnumTag'):
                for item in child.get('inner', []):
                    if item.get('kind') == 'EnumConstantDecl':
                        e = found.setdefault((scope, item['name']), {'kind': 'enumerators', 'groups': set(), 'internal': False, 'definition': set()})
                        if group:
                            e['groups'].add(group)

    state = {'file': None}
    for tree in dump(clang, upstream, include):
        annotate(tree, state)
        if tree.get('kind') == 'NamespaceDecl' and tree.get('name') == 'absl':
            walk(tree, 'absl')
    assert not unknown, sorted(unknown)
    return found, skipped


def macros(upstream):
    """Object-like macros of the public headers: the mapped ones by kind, and every other public name."""
    definitions = defaultdict(list)
    for header in headers(upstream):
        text = (upstream / header).read_text(encoding='utf-8')
        text = text.replace('\\\n', ' ')
        for match in re.finditer(r'^[ \t]*#[ \t]*define[ \t]+([A-Za-z_][A-Za-z0-9_]*)(\(?)([^\n]*)', text, flags=re.M):
            name, function_like, value = match.group(1), match.group(2), match.group(3).strip()
            if 'INTERNAL' in name or name.endswith('_H_') or not name.isupper():
                continue
            definitions[name].append((bool(function_like), value))
    values, flags, header_only = [], [], []
    for name, defs in sorted(definitions.items()):
        if all(not fl and re.fullmatch(r'-?\d+', v or '') for fl, v in defs) and name not in CONSUMER_FLAGS:
            if name in VALUES or any(v == '0' for _, v in defs):
                values.append(name)
            else:
                flags.append(name)
        else:
            header_only.append(name)
    return values, flags, header_only


def derive(clang):
    upstream = fetch()
    every, skipped = declarations(clang, upstream, headers(upstream))
    per_group = {group: declarations(clang, upstream, headers(upstream, group)) for group in GROUPS}
    visible = {group: set(per_group[group][0]) for group in GROUPS}
    record = {group: defaultdict(lambda: defaultdict(list)) for group in GROUPS}
    internal = {}
    for (scope, name), entry in sorted(every.items()):
        key = (scope, name)
        if entry['internal'] and f'{scope}::{name}' not in ADAPTED:
            assert f'{scope}::{name}' in NOT_ADAPTED, f'{scope}::{name}: internal linkage, neither adapted nor explained'
            internal[f'{scope}::{name}'] = NOT_ADAPTED[f'{scope}::{name}']
            continue
        if entry['kind'] in ('functions', 'adl'):
            owners = [g for g in GROUPS if g in entry['groups'] and key in visible[g]]
        else:
            preferred = entry['definition'] or entry['groups']
            owners = [g for g in GROUPS if g in preferred and key in visible[g]][:1]
        if not owners:
            owners = [g for g in GROUPS if key in visible[g]][:1]
        assert owners, f'{scope}::{name} is visible through no group'
        for group in owners:
            record[group][scope]['adapted' if entry['internal'] else entry['kind']].append(name)
    values, flags, header_only = macros(upstream)
    return {
        'release': json.loads((ROOT / 'upstream/documents.json').read_text(encoding='utf-8'))['upstream'],
        'groups': {g: {s: {k: sorted(v) for k, v in sorted(kinds.items())} for s, kinds in sorted(record[g].items())} for g in GROUPS},
        'kept reachable': {g: sorted(k for k in KEEP if KEEP[k][0] in per_group[g][1]) for g in GROUPS if any(KEEP[k][0] in per_group[g][1] for k in KEEP)},
        'not exported': {
            'headers (need GoogleTest/GoogleMock or are upstream test support)': EXCLUDED,
            'implementation namespaces': sorted(skipped),
            'internal linkage (static, or constexpr not inline: every includer has its own; a module cannot export them)': internal,
            'internal linkage, adapted (declared again with its value in mcpplibs::mwrap::abseil)': sorted(ADAPTED),
            'exported under a condition': {name: {'condition': c, 'reason': r} for name, (c, r) in CONDITIONAL.items()},
        },
        'macros': {
            'values (int constants)': values,
            'flags (bool: defined)': flags,
            'through <mwrap/abseil/macros.hpp> only': header_only,
            'consumer build properties (through the header only)': sorted(CONSUMER_FLAGS),
        },
    }


def record():
    return json.loads(RECORD.read_text(encoding='utf-8'))


HEADER = '// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.\n'
TITLES = (('types', 'types'), ('enumerators', 'enumerators of unscoped enumerations'), ('objects', 'objects'),
          ('functions', 'functions and operators'), ('standard', "standard library names Abseil re-declares as its own"),
          ('adl', 'operators of public types declared in an implementation namespace, for argument-dependent lookup'))


def group_text(group, surface, include):
    lines = [HEADER, f'// mcpplibs.mwrap.abseil.{group} — the names of <absl/{group}/…> (Abseil LTS 20250512.1), unchanged:',
             '// each is a using-declaration of the upstream entity in the namespace upstream declares it in.',
             'module;', *[f'#include <{h}>' for h in include], '', f'export module mcpplibs.mwrap.abseil.{group};', '']
    for scope, kinds in surface['groups'][group].items():
        if set(kinds) == {'adapted'}:
            continue
        lines.append(f'export namespace {scope} {{')
        for kind, title in TITLES:
            names = kinds.get(kind, [])
            if names:
                lines.append(f'// {title} ({len(names)})')
                for name in names:
                    condition = CONDITIONAL.get(f'{scope}::{name}')
                    lines += [f'#if {condition[0]}', f'using ::{scope}::{name};', '#endif'] if condition else [f'using ::{scope}::{name};']
        lines += [f'}}  // namespace {scope}', '']
    kept = surface.get('kept reachable', {}).get(group, [])
    if kept:
        lines += ['// Not exported: names that keep global-module-fragment declarations reachable (see tools/surface.py, KEEP).',
                  'namespace mwrap_abseil_reachable {']
        lines += [f'template <class C> using {alias} = ::{KEEP[alias][0]}::{KEEP[alias][1]}<C>;' for alias in kept]
        lines += ['}  // namespace mwrap_abseil_reachable', '']
    for scope, kinds in surface['groups'][group].items():
        if kinds.get('adapted'):
            target = 'mcpplibs::mwrap::abseil' + scope.removeprefix('absl')
            lines += ["// constants of internal linkage in the header, declared again under their names with their values",
                      f'export namespace {target} {{']
            lines += [f'inline constexpr auto {name} = ::{scope}::{name};' for name in kinds['adapted']]
            lines += [f'}}  // namespace {target}', '']
    return '\n'.join(lines)


def root_text():
    lines = [HEADER, '// mcpplibs.mwrap.abseil — Abseil, Google\'s C++ common libraries (LTS 20250512.1), as C++ modules.',
             '// The root re-exports every group of the library and the macro mappings; each group can also be imported',
             '// alone (import mcpplibs.mwrap.abseil.strings;). The library itself is compat.abseil, built from the same release.',
             'export module mcpplibs.mwrap.abseil;', '']
    lines += [f'export import mcpplibs.mwrap.abseil.{g};' for g in GROUPS]
    lines += ['export import mcpplibs.mwrap.abseil.macros;', '']
    return '\n'.join(lines)


def macros_text(surface, include):
    m = surface['macros']
    values, flags = m['values (int constants)'], m['flags (bool: defined)']
    lines = [HEADER, '// mcpplibs.mwrap.abseil.macros — the integer and flag macros of Abseil\'s public headers as constants of the',
             '// same names in mcpplibs::mwrap::abseil::macros, with the values they have where the module is built. A macro',
             '// is not exported by a module: the others (LOG, CHECK, ABSL_FLAG, the attribute and annotation macros …)',
             '// come from #include <mwrap/abseil/macros.hpp>, before the import.', 'module;', *[f'#include <{h}>' for h in include], '',
             'namespace mwrap_abseil_macros {']
    for name in values:
        lines += [f'#ifdef {name}', f'inline constexpr int value_{name} = {name};', f'#define MWRAP_HAS_{name} 1', '#endif']
    for name in flags:
        lines += [f'#ifdef {name}', f'inline constexpr bool value_{name} = true;', '#else', f'inline constexpr bool value_{name} = false;', '#endif']
    lines.append('}  // namespace mwrap_abseil_macros\n')
    lines += [f'#undef {name}' for name in values + flags]
    lines += ['', 'export module mcpplibs.mwrap.abseil.macros;', '', 'export namespace mcpplibs::mwrap::abseil::macros {', '']
    for name in values:
        lines += [f'#ifdef MWRAP_HAS_{name}', f'inline constexpr int {name} = mwrap_abseil_macros::value_{name};', '#endif']
    lines += [f'inline constexpr bool {name} = mwrap_abseil_macros::value_{name};' for name in flags]
    lines.append('\n}  // namespace mcpplibs::mwrap::abseil::macros\n')
    return '\n'.join(lines)


def macros_hpp_text(include):
    lines = ['// <mwrap/abseil/macros.hpp> — Abseil\'s macros (LOG, CHECK, ABSL_FLAG, ABSL_PREDICT_TRUE, the attribute and',
             '// thread-safety annotation macros …), which a module cannot export: every public header of the library, in the',
             '// order the modules include them. Include it BEFORE `import mcpplibs.mwrap.abseil…;` (GCC requires the',
             '// includes of a translation unit to come before its imports). Written by tools/surface.py.',
             '#pragma once', *[f'#include <{h}>' for h in include], '']
    return '\n'.join(lines)


def macros_test_text(surface):
    """Every mapped constant against its macro: the macro's value is taken while it is defined, the macro
    undefined, and only then the module imported (a macro would replace the qualified name too)."""
    m = surface['macros']
    values, flags = m['values (int constants)'], m['flags (bool: defined)']
    lines = ['// Written by tools/surface.py: every constant of mcpplibs.mwrap.abseil.macros against the macro of the same',
             '// name in the headers, which are included first. The macro\'s value is taken, the macro undefined, and only',
             '// then the module imported: a defined macro would replace the qualified name as well.',
             '#include <mwrap/abseil/macros.hpp>', '', 'namespace header {']
    for name in values:
        lines += [f'#ifdef {name}', f'constexpr int {name.lower()} = {name};', f'#define MWRAP_TEST_HAS_{name} 1', '#endif']
    for name in flags:
        lines += [f'#ifdef {name}', f'constexpr bool {name.lower()} = true;', '#else', f'constexpr bool {name.lower()} = false;', '#endif']
    lines.append('}  // namespace header')
    lines += [f'#undef {name}' for name in values + flags]
    lines += ['', '#include <gtest/gtest.h>', '', 'import mcpplibs.mwrap.abseil.macros;', '',
              'namespace macros = mcpplibs::mwrap::abseil::macros;', '']
    for name in values:
        lines += [f'#ifdef MWRAP_TEST_HAS_{name}', f'static_assert(macros::{name} == header::{name.lower()});', '#endif']
    lines += [f'static_assert(macros::{name} == header::{name.lower()});' for name in flags]
    lines += ['', '// Values the release fixes.', 'static_assert(macros::ABSL_LTS_RELEASE_VERSION == 20250512 && macros::ABSL_LTS_RELEASE_PATCH_LEVEL == 1);',
              'static_assert(macros::ABSL_OPTION_USE_INLINE_NAMESPACE == 1 && macros::ABSL_IS_LITTLE_ENDIAN != macros::ABSL_IS_BIG_ENDIAN);',
              'static_assert(macros::ABSL_HAVE_STD_OPTIONAL && macros::ABSL_USES_STD_OPTIONAL && macros::ABSL_USES_STD_STRING_VIEW);', '',
              f'TEST(Macros, MappedAsTheHeadersDefineThem) {{ EXPECT_EQ({len(values) + len(flags)}, {len(values) + len(flags)}); }}', '']
    return '\n'.join(lines)


GROUP_TITLES = {
    'base': 'call_once, casts, LogSeverity, the nullability annotations', 'meta': 'type traits', 'utility': 'utility (std names)',
    'memory': 'WrapUnique, pointer helpers', 'functional': 'AnyInvocable, FunctionRef, Overload, bind_front',
    'algorithm': 'the c_ container algorithms', 'numeric': 'int128, uint128, bits, endian', 'types': 'Span, optional, variant, any, compare',
    'hash': 'Hash, HashOf, HashState', 'container': 'flat/node hash maps and sets, btree, InlinedVector, FixedArray',
    'strings': 'StrCat, StrFormat, StrSplit, StrJoin, Cord, numbers, escaping, ascii', 'crc': 'CRC-32C',
    'cleanup': 'Cleanup', 'debugging': 'stack traces, symbolization, failure signal handler, leak checks',
    'synchronization': 'Mutex, Notification, Barrier, BlockingCounter', 'time': 'Time, Duration, TimeZone, civil time, formatting',
    'status': 'Status, StatusOr', 'random': 'BitGen and the distributions', 'log': 'LogSink, LogEntry, log globals and initialization',
    'flags': 'command-line flags: parsing, reflection, usage'}


def usage_text(surface):
    m, n = surface['macros'], surface['not exported']
    count = lambda group: sum(len(v) for kinds in surface['groups'][group].values() for v in kinds.values())
    lines = ['# Modules and API', '', '[README](../README.md) · written by `tools/surface.py` from `tools/surface.json` (audited by `tools/check_exports.py`).', '',
             'Every exported name is the upstream entity, in the namespace upstream declares it in (`absl`; Abseil\'s inline',
             'namespace `lts_20250512` is transparent). `import mcpplibs.mwrap.abseil;` imports all groups and the macro constants;',
             'a group can be imported alone.', '', '| Module | Names | Of |', '|---|---:|---|']
    lines += [f'| `mcpplibs.mwrap.abseil.{g}` | {count(g)} | {GROUP_TITLES[g]} |' for g in GROUPS]
    lines += [f'| `mcpplibs.mwrap.abseil.macros` | {len(m["values (int constants)"]) + len(m["flags (bool: defined)"])} | the integer and flag macros as constants |', '',
              '## How names are assigned', '',
              '- A name belongs to the group whose files declare it; a function name to every group that declares an overload of it,',
              '  so a group imported alone carries its own operators.',
              '- Names Abseil re-declares from the standard library (`absl::optional`, `absl::string_view`, `absl::bit_cast` …) are',
              '  exported as Abseil\'s names.',
              '- Operators of public types that upstream declares in an implementation namespace (the civil-time comparisons in',
              '  `time_internal::cctz::detail`, `str_format_internal`, `random_internal`, `log_internal`) are exported there, so that',
              '  argument-dependent lookup finds them through the module.', '',
              '## Not exported', '']
    for title, items in n.items():
        lines.append(f'- {title}:')
        if isinstance(items, dict):
            lines += [f'  - `{k}`: {v if isinstance(v, str) else v["reason"] + " (exported when `" + v["condition"] + "`)"}' for k, v in items.items()]
        else:
            lines.append('  ' + ', '.join(f'`{i}`' for i in items))
    lines += ['', '## Macros', '',
              'A module does not export macros. `#include <mwrap/abseil/macros.hpp>` (every public header) **before** the imports',
              'brings all of them; GCC requires a translation unit\'s includes to come before its imports.', '',
              f'- Integer values as `int` in `mcpplibs::mwrap::abseil::macros`: ' + ', '.join(f'`{x}`' for x in m['values (int constants)']),
              f'- Flags as `bool` (defined where the module is built): ' + ', '.join(f'`{x}`' for x in m['flags (bool: defined)']),
              f'- Properties of the consumer\'s own build (sanitizers, exceptions), through the header only: ' + ', '.join(f'`{x}`' for x in m['consumer build properties (through the header only)']),
              f'- Through the header only ({len(m["through <mwrap/abseil/macros.hpp> only"])}): ' + ', '.join(f'`{x}`' for x in m['through <mwrap/abseil/macros.hpp> only']), '']
    return '\n'.join(lines)


def outputs(surface=None):
    surface = surface or record()
    upstream = fetch()
    out = {SRC / f'{g}.cppm': group_text(g, surface, headers(upstream, g)) for g in GROUPS}
    out[SRC / 'abseil.cppm'] = root_text()
    out[SRC / 'macros.cppm'] = macros_text(surface, headers(upstream))
    out[MACROS_HPP] = macros_hpp_text(headers(upstream))
    out[ROOT / 'tests/macros_test.cpp'] = macros_test_text(surface)
    out[ROOT / 'docs/usage.md'] = usage_text(surface)
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--clang', help='derive tools/surface.json with this clang++')
    parser.add_argument('--write', action='store_true', help='write the module sources and the macros header')
    args = parser.parse_args()
    if args.clang:
        RECORD.write_text(json.dumps(derive(args.clang), indent=1) + '\n', encoding='utf-8')
    if args.write:
        for path, text in outputs().items():
            path.parent.mkdir(parents=True, exist_ok=True)
            if not path.exists() or path.read_text(encoding='utf-8') != text:
                path.write_text(text, encoding='utf-8')
    surface = record()
    for group, scopes in surface['groups'].items():
        print(group + ': ' + '; '.join(f'{scope} ' + ', '.join(f'{len(n)} {k}' for k, n in kinds.items()) for scope, kinds in scopes.items()))


if __name__ == '__main__':
    sys.exit(main())
