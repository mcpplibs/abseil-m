# abseil

> Abseil（Google 的 C++ 通用库，LTS 20250512.1：字符串、容器、哈希、状态、时间、同步、日志、命令行标志与随机数）的 C++23 模块封装。

[English](README.md) · **简体中文** · [Upstream](https://github.com/abseil/abseil-cpp) · [Releases](https://github.com/mcpplibs/abseil-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [Index](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/abseil-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/abseil-m/actions/workflows/ci.yml)

上游的 C++ API 保持原样：`absl::StrCat`、`absl::flat_hash_map`、`absl::Status`、`absl::Time` 以及其他公开名字
都是上游的实体，在上游声明它们的命名空间里。库本身是 `compat.abseil` 20250512.1，由 mcpp 从同一发布包构建；
本包提供模块（库的每个分组一个）以及宏的常量。同时使用本索引中 protobuf 或 gRPC 的程序链接的是同一份 Abseil。

## Modules

- `import mcpplibs.mwrap.abseil;`：下列全部分组与宏常量
- `import mcpplibs.mwrap.abseil.strings;`：`StrCat`、`StrFormat`、`StrSplit`、`StrJoin`、`Cord`、数字与转义
- `import mcpplibs.mwrap.abseil.container;`：`flat_hash_map`/`set`、`node_hash_map`/`set`、`btree_map`/`set`、`InlinedVector`、`FixedArray`
- `import mcpplibs.mwrap.abseil.status;`：`Status`、`StatusOr`
- `import mcpplibs.mwrap.abseil.time;`：`Time`、`Duration`、`TimeZone`、民用时间、格式化与解析
- `import mcpplibs.mwrap.abseil.macros;`：`ABSL_LTS_RELEASE_VERSION`、`ABSL_HAVE_*` 标志等，位于 `mcpplibs::mwrap::abseil::macros`

其余分组：`base`、`meta`、`utility`、`memory`、`functional`、`algorithm`、`numeric`、`types`、`hash`、`crc`、
`cleanup`、`debugging`、`synchronization`、`random`、`log`、`flags`。

> More Modules API -> [模块与 API](docs/usage.md)

## 快速开始

```sh
mcpp new basics --template mcpplibs.mwrap.abseil@20250512.1
cd basics
mcpp run
```

默认模板用 `flat_hash_map` 统计词频，把记录解析为 `StatusOr`（其中一条失败并用 `LOG` 记录），格式化 UTC 时间，
并通过 `absl::LogSink` 收集日志行。

```toml
[dependencies]
mcpplibs.mwrap.abseil = "20250512.1"
```

```cpp
#include <mwrap/abseil/macros.hpp>   // LOG、CHECK、ABSL_FLAG ……（仅在使用宏时需要）

import std;
import mcpplibs.mwrap.abseil;

int main() {
    absl::flat_hash_map<std::string, int> counts;
    for (absl::string_view word : absl::StrSplit("a b a", ' ')) ++counts[word];
    LOG(INFO) << absl::StrFormat("a appears %d times", counts["a"]);
}
```

## 宏与包含顺序

模块不能导出宏。`<mwrap/abseil/macros.hpp>` 包含库的全部公开头文件：`LOG`、`CHECK`、`ABSL_FLAG`、
`ABSL_PREDICT_TRUE`、属性与线程安全注解宏。**请在 import 之前包含它（以及任何 Abseil 头文件）**：
GCC 16 不接受在 import 本模块之后再包含头文件。Clang 两种顺序都接受。

整数与标志宏也以同名常量位于 `mcpplibs::mwrap::abseil::macros`（`ABSL_LTS_RELEASE_VERSION`、`ABSL_HAVE_MMAP`、
`ABSL_IS_LITTLE_ENDIAN` ……）。在包含了头文件的翻译单元中宏优先：宏也会替换限定名。

## 封装范围

- 已封装：20 个分组的 813 个公开名字，由 `tools/surface.py` 按 clang 读到的头文件推导。
- 不在本包：测试与 mock 头文件（`MockingBitGen`、`ScopedMockLog`、状态匹配器：它们需要 GoogleTest），
  以及实现命名空间（`*_internal`）；其中声明的公开类型运算符除外。
- `absl::kLogDebugFatal` 取决于使用方的 `NDEBUG`，从头文件获得；`kFixedArrayUseDefault`（头文件中为内部链接）
  为 `mcpplibs::mwrap::abseil::kFixedArrayUseDefault`。
- GCC 16：`absl::Flag`、`GetFlag`、`SetFlag` 与 `GetFlagReflectionHandle` 来自头文件（GCC 不接受导出它们）；
  Clang 下模块也导出它们。使用标志的代码本来就要包含头文件（`ABSL_FLAG`）。
- Web（wasm32）：单线程。

## 验证

- `mcpp test`：仅通过模块使用 API（字符串、Cord、各容器、哈希、Status、时间与民用时间、int128 与位运算、CRC-32C、
  函数工具、随机数范围、Mutex 与线程）；每个映射常量与其宏比对；与模块一起使用标志、`LOG` 到 sink 与 `CHECK`；
  通过头文件与模块看到的是同一实体。
- `python3 tools/check_exports.py`：源码与 `tools/surface.json` 完全一致；提供 clang++ 时（CI 的 LLVM 行必需）
  从头文件重新推导记录并比较。
- `python3 tools/test_template.py`：从已安装副本 `mcpp new`，严格构建并运行。
- CI：Linux x86-64 与 arm64（GCC 16、LLVM 23）、macOS 与 Windows（LLVM 23），每行 dev 与 release 两种配置，以及 node 下的 wasm32。

## 许可证

封装为 Apache-2.0（mcpp-community）。Abseil 为 Apache-2.0，© The Abseil Authors。上游的 README 与 LICENSE
保留在 `upstream/abseil-cpp/`，并随程序的许可证一起部署。来源：`upstream/documents.json`。
