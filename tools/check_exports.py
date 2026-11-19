#!/usr/bin/env python3
"""Audit the modules against Abseil's public headers.

The module sources (src/*.cppm), <mwrap/abseil/macros.hpp> and tests/macros_test.cpp must be exactly what
tools/surface.py writes from tools/surface.json, and every name of that record must be spelled in a header
of the release. With a clang++ (--clang, or MWRAP_CLANG) the record itself is derived again from the headers
as the compiler reads them and must be the same: no public name left out, none exported that is not there.
MWRAP_REQUIRE_CLANG=1 makes the second half mandatory (CI's Linux LLVM row).
"""
import argparse
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import surface  # noqa: E402


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--clang', default=os.environ.get('MWRAP_CLANG'))
    args = parser.parse_args()
    record = surface.record()
    for path, text in surface.outputs(record).items():
        assert path.read_text(encoding='utf-8') == text, f'{path.relative_to(surface.ROOT)} is not what tools/surface.py --write gives'
    upstream = surface.fetch()
    text = ''.join(p.read_text(encoding='utf-8') for p in sorted((upstream / 'absl').rglob('*.h')))
    exported = adapted = 0
    for group, scopes in record['groups'].items():
        for scope, kinds in scopes.items():
            for kind, names in kinds.items():
                for name in names:
                    pattern = (r'\boperator\s*' + re.escape(name.removeprefix('operator').strip())) if name.startswith('operator') \
                        else r'(?<![\w])' + re.escape(name) + r'(?![\w])'
                    assert re.search(pattern, text), f'{scope}::{name} is in no header'
                    module = (surface.SRC / f'{group}.cppm').read_text(encoding='utf-8')
                    if kind == 'adapted':
                        adapted += 1
                        assert f'inline constexpr auto {name} = ::{scope}::{name};' in module, name
                    else:
                        exported += 1
                        assert f'using ::{scope}::{name};' in module, f'{scope}::{name} not in src/{group}.cppm'
    if args.clang:
        derived = surface.derive(args.clang)
        assert derived == record, 'tools/surface.json is not what clang derives from the headers: run tools/surface.py --clang <clang++> --write'
    else:
        assert os.environ.get('MWRAP_REQUIRE_CLANG') != '1', 'MWRAP_REQUIRE_CLANG=1 and no clang++ given'
    m = record['macros']
    print(f'{exported} using-declarations in {len(record["groups"])} groups, {adapted} constant(s) of internal linkage adapted, '
          f'{len(m["values (int constants)"]) + len(m["flags (bool: defined)"])} macros mapped, '
          f'{len(m["through <mwrap/abseil/macros.hpp> only"])} through the header only; '
          + ('the record is what clang derives from the headers' if args.clang else 'the record not derived again (no clang++ given)'))


if __name__ == '__main__':
    main()
