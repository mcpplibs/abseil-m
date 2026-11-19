# abseil

> Abseil, Google's C++ common libraries (LTS 20250512.1): strings, containers, hashing, status, time, synchronization, logging, flags and random, through C++23 modules.

**English** · [简体中文](README.zh.md) · [Upstream](https://github.com/abseil/abseil-cpp) · [Releases](https://github.com/mcpplibs/abseil-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [Index](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/abseil-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/abseil-m/actions/workflows/ci.yml)

The upstream C++ API is unchanged: `absl::StrCat`, `absl::flat_hash_map`,
`absl::Status`, `absl::Time` and every other public name are the upstream
entities, in the namespaces upstream declares them in. The library is
`compat.abseil` 20250512.1, built by mcpp from the same release; this package
adds the modules, one per group of the library, and the constants of its
macros. A program that also uses protobuf or gRPC from this index links the
same single Abseil.

## Modules

- `import mcpplibs.mwrap.abseil;`: every group below and the macro constants
- `import mcpplibs.mwrap.abseil.strings;`: `StrCat`, `StrFormat`, `StrSplit`, `StrJoin`, `Cord`, numbers, escaping
- `import mcpplibs.mwrap.abseil.container;`: `flat_hash_map`/`set`, `node_hash_map`/`set`, `btree_map`/`set`, `InlinedVector`, `FixedArray`
- `import mcpplibs.mwrap.abseil.status;`: `Status`, `StatusOr`
- `import mcpplibs.mwrap.abseil.time;`: `Time`, `Duration`, `TimeZone`, civil time, formatting and parsing
- `import mcpplibs.mwrap.abseil.macros;`: `ABSL_LTS_RELEASE_VERSION`, the `ABSL_HAVE_*` flags … in `mcpplibs::mwrap::abseil::macros`

The other groups: `base`, `meta`, `utility`, `memory`, `functional`, `algorithm`, `numeric`, `types`, `hash`, `crc`,
`cleanup`, `debugging`, `synchronization`, `random`, `log`, `flags`.

> More Modules API -> [Modules and API](docs/usage.md)

## Getting started

```sh
mcpp new basics --template mcpplibs.mwrap.abseil@20250512.1
cd basics
mcpp run
```

The default template counts words in a `flat_hash_map`, parses records into a
`StatusOr` (one fails, and is logged with `LOG`), formats a UTC time and
collects the log line through an `absl::LogSink`.

```toml
[dependencies]
mcpplibs.mwrap.abseil = "20250512.1"
```

```cpp
#include <mwrap/abseil/macros.hpp>   // LOG, CHECK, ABSL_FLAG … (only if you use macros)

import std;
import mcpplibs.mwrap.abseil;

int main() {
    absl::flat_hash_map<std::string, int> counts;
    for (absl::string_view word : absl::StrSplit("a b a", ' ')) ++counts[word];
    LOG(INFO) << absl::StrFormat("a appears %d times", counts["a"]);
}
```

## Macros and the include order

A module cannot export macros. `<mwrap/abseil/macros.hpp>` includes every
public header of the library: `LOG`, `CHECK`, `ABSL_FLAG`, `ABSL_PREDICT_TRUE`,
the attribute and thread-safety annotation macros. **Include it (and any
Abseil header) before the imports**: GCC 16 rejects a header included after an
import of the module. Clang accepts both orders.

The integer and flag macros are also constants of the same names in
`mcpplibs::mwrap::abseil::macros` (`ABSL_LTS_RELEASE_VERSION`, `ABSL_HAVE_MMAP`,
`ABSL_IS_LITTLE_ENDIAN` …). In a unit that includes the header the macro wins:
a macro replaces the qualified name too.

## What is and is not wrapped

- Wrapped: 813 public names of the 20 groups, derived from the headers as clang reads them (`tools/surface.py`).
- Not here: the test and mocking headers (`MockingBitGen`, `ScopedMockLog`, the status matchers: they need GoogleTest),
  and the implementation namespaces (`*_internal`), except operators of public types that upstream declares there.
- `absl::kLogDebugFatal` depends on the consumer's `NDEBUG` and comes from the header;
  `kFixedArrayUseDefault` (internal linkage in the header) is `mcpplibs::mwrap::abseil::kFixedArrayUseDefault`.
- GCC 16: `absl::Flag`, `GetFlag`, `SetFlag` and `GetFlagReflectionHandle` come from the header (GCC rejects
  exporting them); with Clang the module exports them too. Code that uses flags includes the header anyway (`ABSL_FLAG`).
- The Web (wasm32): one thread.

## Verification

- `mcpp test`: the API through the module alone (strings, Cord, the containers, hashing, Status, time and civil time,
  int128 and bits, CRC-32C, functional, random bounds, Mutex and threads); every mapped constant against its macro;
  flags, `LOG` into a sink and `CHECK` with the module; the entities through the header and the module are the same.
- `python3 tools/check_exports.py`: the sources are exactly `tools/surface.json`; given a clang++ (required on
  CI's LLVM row) the record is derived again from the headers and compared.
- `python3 tools/test_template.py`: `mcpp new` from an installed copy, a strict build and a run.
- CI: Linux x86-64 and arm64 (GCC 16, LLVM 23), macOS and Windows (LLVM 23), each in the dev and release profiles,
  and wasm32 under node.

## License

The wrapper is Apache-2.0 (mcpp-community). Abseil is Apache-2.0, © The Abseil
Authors. Upstream's README and LICENSE are kept in `upstream/abseil-cpp/` and
deployed with a program's licenses. Provenance: `upstream/documents.json`.
