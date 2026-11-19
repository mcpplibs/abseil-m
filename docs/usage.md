# Modules and API

[README](../README.md) · written by `tools/surface.py` from `tools/surface.json` (audited by `tools/check_exports.py`).

Every exported name is the upstream entity, in the namespace upstream declares it in (`absl`; Abseil's inline
namespace `lts_20250512` is transparent). `import mcpplibs.mwrap.abseil;` imports all groups and the macro constants;
a group can be imported alone.

| Module | Names | Of |
|---|---:|---|
| `mcpplibs.mwrap.abseil.base` | 27 | call_once, casts, LogSeverity, the nullability annotations |
| `mcpplibs.mwrap.abseil.meta` | 38 | type traits |
| `mcpplibs.mwrap.abseil.utility` | 16 | utility (std names) |
| `mcpplibs.mwrap.abseil.memory` | 9 | WrapUnique, pointer helpers |
| `mcpplibs.mwrap.abseil.functional` | 4 | AnyInvocable, FunctionRef, Overload, bind_front |
| `mcpplibs.mwrap.abseil.algorithm` | 89 | the c_ container algorithms |
| `mcpplibs.mwrap.abseil.numeric` | 82 | int128, uint128, bits, endian |
| `mcpplibs.mwrap.abseil.types` | 34 | Span, optional, variant, any, compare |
| `mcpplibs.mwrap.abseil.hash` | 3 | Hash, HashOf, HashState |
| `mcpplibs.mwrap.abseil.container` | 23 | flat/node hash maps and sets, btree, InlinedVector, FixedArray |
| `mcpplibs.mwrap.abseil.strings` | 169 | StrCat, StrFormat, StrSplit, StrJoin, Cord, numbers, escaping, ascii |
| `mcpplibs.mwrap.abseil.crc` | 9 | CRC-32C |
| `mcpplibs.mwrap.abseil.cleanup` | 2 | Cleanup |
| `mcpplibs.mwrap.abseil.debugging` | 18 | stack traces, symbolization, failure signal handler, leak checks |
| `mcpplibs.mwrap.abseil.synchronization` | 18 | Mutex, Notification, Barrier, BlockingCounter |
| `mcpplibs.mwrap.abseil.time` | 131 | Time, Duration, TimeZone, civil time, formatting |
| `mcpplibs.mwrap.abseil.status` | 54 | Status, StatusOr |
| `mcpplibs.mwrap.abseil.random` | 39 | BitGen and the distributions |
| `mcpplibs.mwrap.abseil.log` | 27 | LogSink, LogEntry, log globals and initialization |
| `mcpplibs.mwrap.abseil.flags` | 21 | command-line flags: parsing, reflection, usage |
| `mcpplibs.mwrap.abseil.macros` | 41 | the integer and flag macros as constants |

## How names are assigned

- A name belongs to the group whose files declare it; a function name to every group that declares an overload of it,
  so a group imported alone carries its own operators.
- Names Abseil re-declares from the standard library (`absl::optional`, `absl::string_view`, `absl::bit_cast` …) are
  exported as Abseil's names.
- Operators of public types that upstream declares in an implementation namespace (the civil-time comparisons in
  `time_internal::cctz::detail`, `str_format_internal`, `random_internal`, `log_internal`) are exported there, so that
  argument-dependent lookup finds them through the module.

## Not exported

- headers (need GoogleTest/GoogleMock or are upstream test support):
  - `absl/random/mocking_bit_gen.h`: needs GoogleMock (absl::MockingBitGen)
  - `absl/random/mock_distributions.h`: needs GoogleMock (absl::MockUniform …)
  - `absl/log/scoped_mock_log.h`: needs GoogleMock (absl::ScopedMockLog)
  - `absl/status/status_matchers.h`: needs GoogleTest matchers (absl_testing::IsOk …)
  - `absl/hash/hash_testing.h`: needs GoogleTest (absl::VerifyTypeImplementsAbslHashCorrectly)
  - `absl/container/btree_test.h`: upstream's own btree test support
  - `absl/strings/cord_test_helpers.h`: upstream's own Cord test support
  - `absl/strings/cordz_test_helpers.h`: upstream's own Cordz test support (needs GoogleTest)
- implementation namespaces:
  `absl::ascii_internal`, `absl::base_internal`, `absl::cleanup_internal`, `absl::compare_internal`, `absl::container_algorithm_internal`, `absl::container_internal`, `absl::container_internal::hashtable_debug_internal`, `absl::container_internal::internal_compressed_tuple`, `absl::container_internal::internal_layout`, `absl::container_internal::internal_layout::adl_barrier`, `absl::container_internal::memory_internal`, `absl::cord_internal`, `absl::crc_internal`, `absl::debugging_internal`, `absl::flags_internal`, `absl::functional_internal`, `absl::hash_internal`, `absl::inlined_vector_internal`, `absl::int128_internal`, `absl::internal`, `absl::internal_any_invocable`, `absl::internal_stacktrace`, `absl::internal_statusor`, `absl::log_internal`, `absl::log_internal::detect_specialization`, `absl::macros_internal`, `absl::memory_internal`, `absl::nullability_internal`, `absl::numbers_internal`, `absl::numeric_internal`, `absl::profiling_internal`, `absl::random_internal`, `absl::raw_log_internal`, `absl::span_internal`, `absl::status_internal`, `absl::str_format_internal`, `absl::strings_internal`, `absl::substitute_internal`, `absl::swap_internal`, `absl::synchronization_internal`, `absl::time_internal`, `absl::time_internal::cctz`, `absl::time_internal::cctz::detail`, `absl::time_internal::cctz::detail::impl`, `absl::type_traits_internal`, `absl::variant_internal`
- internal linkage (static, or constexpr not inline: every includer has its own; a module cannot export them):
  - `absl::kLogDebugFatal`: its value is kError or kFatal by the consumer's NDEBUG (log_severity.h); include <absl/base/log_severity.h> (or <mwrap/abseil/macros.hpp>) to use it
- internal linkage, adapted (declared again with its value in mcpplibs::mwrap::abseil):
  `absl::kFixedArrayUseDefault`
- exported under a condition:
  - `absl::Flag`: GCC 16: flags_internal::Flag<T>, which this name reaches, exposes the TU-local StorageKind<T>() (exported when `!defined(__GNUC__) || defined(__clang__)`)
  - `absl::GetFlag`: GCC 16: flags_internal::Flag<T>, which this name reaches, exposes the TU-local StorageKind<T>() (exported when `!defined(__GNUC__) || defined(__clang__)`)
  - `absl::SetFlag`: GCC 16: flags_internal::Flag<T>, which this name reaches, exposes the TU-local StorageKind<T>() (exported when `!defined(__GNUC__) || defined(__clang__)`)
  - `absl::GetFlagReflectionHandle`: GCC 16: flags_internal::Flag<T>, which this name reaches, exposes the TU-local StorageKind<T>() (exported when `!defined(__GNUC__) || defined(__clang__)`)

## Macros

A module does not export macros. `#include <mwrap/abseil/macros.hpp>` (every public header) **before** the imports
brings all of them; GCC requires a translation unit's includes to come before its imports.

- Integer values as `int` in `mcpplibs::mwrap::abseil::macros`: `ABSL_CACHELINE_SIZE`, `ABSL_FLAGS_STRIP_NAMES`, `ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL`, `ABSL_HAVE_ATTRIBUTE_SECTION`, `ABSL_HAVE_ATTRIBUTE_WEAK`, `ABSL_LTS_RELEASE_PATCH_LEVEL`, `ABSL_LTS_RELEASE_VERSION`, `ABSL_OPTION_HARDENED`, `ABSL_OPTION_USE_INLINE_NAMESPACE`, `ABSL_OPTION_USE_STD_ORDERING`, `ABSL_OPTION_USE_STD_STRING_VIEW`
- Flags as `bool` (defined where the module is built): `ABSL_HAVE_ALARM`, `ABSL_HAVE_ATTRIBUTE_ALWAYS_INLINE`, `ABSL_HAVE_ATTRIBUTE_NOINLINE`, `ABSL_HAVE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION`, `ABSL_HAVE_CONSTANT_EVALUATED`, `ABSL_HAVE_INTRINSIC_INT128`, `ABSL_HAVE_MMAP`, `ABSL_HAVE_PREFETCH`, `ABSL_HAVE_PTHREAD_GETSCHEDPARAM`, `ABSL_HAVE_SCHED_GETCPU`, `ABSL_HAVE_SCHED_YIELD`, `ABSL_HAVE_SEMAPHORE_H`, `ABSL_HAVE_STD_ANY`, `ABSL_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE`, `ABSL_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE`, `ABSL_HAVE_STD_IS_TRIVIALLY_COPYABLE`, `ABSL_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE`, `ABSL_HAVE_STD_OPTIONAL`, `ABSL_HAVE_STD_ORDERING`, `ABSL_HAVE_STD_STRING_VIEW`, `ABSL_HAVE_STD_VARIANT`, `ABSL_HAVE_THREAD_LOCAL`, `ABSL_HAVE_TLS`, `ABSL_IS_BIG_ENDIAN`, `ABSL_IS_LITTLE_ENDIAN`, `ABSL_USES_STD_ANY`, `ABSL_USES_STD_OPTIONAL`, `ABSL_USES_STD_ORDERING`, `ABSL_USES_STD_STRING_VIEW`, `ABSL_USES_STD_VARIANT`
- Properties of the consumer's own build (sanitizers, exceptions), through the header only: `ABSL_HAVE_ADDRESS_SANITIZER`, `ABSL_HAVE_DATAFLOW_SANITIZER`, `ABSL_HAVE_EXCEPTIONS`, `ABSL_HAVE_HWADDRESS_SANITIZER`, `ABSL_HAVE_LEAK_SANITIZER`, `ABSL_HAVE_MEMORY_SANITIZER`, `ABSL_HAVE_THREAD_SANITIZER`
- Through the header only (290): `ABSL_ACQUIRED_AFTER`, `ABSL_ACQUIRED_BEFORE`, `ABSL_ADDRESS_SANITIZER_REDZONE`, `ABSL_ANNOTATE_BENIGN_RACE`, `ABSL_ANNOTATE_BENIGN_RACE_SIZED`, `ABSL_ANNOTATE_BENIGN_RACE_STATIC`, `ABSL_ANNOTATE_CONTIGUOUS_CONTAINER`, `ABSL_ANNOTATE_ENABLE_RACE_DETECTION`, `ABSL_ANNOTATE_IGNORE_READS_AND_WRITES_BEGIN`, `ABSL_ANNOTATE_IGNORE_READS_AND_WRITES_END`, `ABSL_ANNOTATE_IGNORE_READS_BEGIN`, `ABSL_ANNOTATE_IGNORE_READS_END`, `ABSL_ANNOTATE_IGNORE_WRITES_BEGIN`, `ABSL_ANNOTATE_IGNORE_WRITES_END`, `ABSL_ANNOTATE_MEMORY_IS_INITIALIZED`, `ABSL_ANNOTATE_MEMORY_IS_UNINITIALIZED`, `ABSL_ANNOTATE_RWLOCK_ACQUIRED`, `ABSL_ANNOTATE_RWLOCK_CREATE`, `ABSL_ANNOTATE_RWLOCK_CREATE_STATIC`, `ABSL_ANNOTATE_RWLOCK_DESTROY`, `ABSL_ANNOTATE_RWLOCK_RELEASED`, `ABSL_ANNOTATE_THREAD_NAME`, `ABSL_ANNOTATE_UNPROTECTED_READ`, `ABSL_ARRAYSIZE`, `ABSL_ASSERT`, `ABSL_ASSERT_EXCLUSIVE_LOCK`, `ABSL_ASSERT_SHARED_LOCK`, `ABSL_ASSUME`, `ABSL_ATTRIBUTE_ALWAYS_INLINE`, `ABSL_ATTRIBUTE_COLD`, `ABSL_ATTRIBUTE_CONST_FUNCTION`, `ABSL_ATTRIBUTE_FUNC_ALIGN`, `ABSL_ATTRIBUTE_HOT`, `ABSL_ATTRIBUTE_INITIAL_EXEC`, `ABSL_ATTRIBUTE_LIFETIME_BOUND`, `ABSL_ATTRIBUTE_NOINLINE`, `ABSL_ATTRIBUTE_NONNULL`, `ABSL_ATTRIBUTE_NORETURN`, `ABSL_ATTRIBUTE_NO_SANITIZE_ADDRESS`, `ABSL_ATTRIBUTE_NO_SANITIZE_CFI`, `ABSL_ATTRIBUTE_NO_SANITIZE_MEMORY`, `ABSL_ATTRIBUTE_NO_SANITIZE_SAFESTACK`, `ABSL_ATTRIBUTE_NO_SANITIZE_THREAD`, `ABSL_ATTRIBUTE_NO_SANITIZE_UNDEFINED`, `ABSL_ATTRIBUTE_NO_TAIL_CALL`, `ABSL_ATTRIBUTE_NO_UNIQUE_ADDRESS`, `ABSL_ATTRIBUTE_OWNER`, `ABSL_ATTRIBUTE_PACKED`, `ABSL_ATTRIBUTE_PURE_FUNCTION`, `ABSL_ATTRIBUTE_REINITIALIZES`, `ABSL_ATTRIBUTE_RETURNS_NONNULL`, `ABSL_ATTRIBUTE_SECTION`, `ABSL_ATTRIBUTE_SECTION_START`, `ABSL_ATTRIBUTE_SECTION_STOP`, `ABSL_ATTRIBUTE_SECTION_VARIABLE`, `ABSL_ATTRIBUTE_STACK_ALIGN_FOR_OLD_LIBC`, `ABSL_ATTRIBUTE_TRIVIAL_ABI`, `ABSL_ATTRIBUTE_UNINITIALIZED`, `ABSL_ATTRIBUTE_UNUSED`, `ABSL_ATTRIBUTE_VIEW`, `ABSL_ATTRIBUTE_WARN_UNUSED`, `ABSL_ATTRIBUTE_WEAK`, `ABSL_BAD_CALL_IF`, `ABSL_BLOCK_TAIL_CALL_OPTIMIZATION`, `ABSL_CACHELINE_ALIGNED`, `ABSL_CHECK`, `ABSL_CHECK_EQ`, `ABSL_CHECK_GE`, `ABSL_CHECK_GT`, `ABSL_CHECK_LE`, `ABSL_CHECK_LT`, `ABSL_CHECK_NE`, `ABSL_CHECK_OK`, `ABSL_CHECK_STRCASEEQ`, `ABSL_CHECK_STRCASENE`, `ABSL_CHECK_STREQ`, `ABSL_CHECK_STRNE`, `ABSL_COMPARE_INLINE_BASECLASS_DECL`, `ABSL_COMPARE_INLINE_INIT`, `ABSL_COMPARE_INLINE_SUBCLASS_DECL`, `ABSL_CONST_INIT`, `ABSL_DCHECK`, `ABSL_DCHECK_EQ`, `ABSL_DCHECK_GE`, `ABSL_DCHECK_GT`, `ABSL_DCHECK_LE`, `ABSL_DCHECK_LT`, `ABSL_DCHECK_NE`, `ABSL_DCHECK_OK`, `ABSL_DCHECK_STRCASEEQ`, `ABSL_DCHECK_STRCASENE`, `ABSL_DCHECK_STREQ`, `ABSL_DCHECK_STRNE`, `ABSL_DECLARE_ATTRIBUTE_SECTION_VARS`, `ABSL_DECLARE_FLAG`, `ABSL_DEFINE_ATTRIBUTE_SECTION_VARS`, `ABSL_DEPRECATED`, `ABSL_DEPRECATE_AND_INLINE`, `ABSL_DIE_IF_NULL`, `ABSL_DLL`, `ABSL_DLOG`, `ABSL_DLOG_EVERY_N`, `ABSL_DLOG_EVERY_N_SEC`, `ABSL_DLOG_EVERY_POW_2`, `ABSL_DLOG_FIRST_N`, `ABSL_DLOG_IF`, `ABSL_DLOG_IF_EVERY_N`, `ABSL_DLOG_IF_EVERY_N_SEC`, `ABSL_DLOG_IF_EVERY_POW_2`, `ABSL_DLOG_IF_FIRST_N`, `ABSL_DVLOG`, `ABSL_EXCLUSIVE_LOCKS_REQUIRED`, `ABSL_EXCLUSIVE_LOCK_FUNCTION`, `ABSL_EXCLUSIVE_TRYLOCK_FUNCTION`, `ABSL_FALLTHROUGH_INTENDED`, `ABSL_FLAG`, `ABSL_FLAGS_STRIP_HELP`, `ABSL_FLAG_IMPL`, `ABSL_FLAG_IMPL_DECLARE_DEF_VAL_WRAPPER`, `ABSL_FLAG_IMPL_DECLARE_HELP_WRAPPER`, `ABSL_FLAG_IMPL_DEFAULT_ARG`, `ABSL_FLAG_IMPL_FILENAME`, `ABSL_FLAG_IMPL_FLAGHELP`, `ABSL_FLAG_IMPL_FLAGNAME`, `ABSL_FLAG_IMPL_FLAG_PTR`, `ABSL_FLAG_IMPL_HELP_ARG`, `ABSL_FLAG_IMPL_REGISTRAR`, `ABSL_FLAG_IMPL_TYPENAME`, `ABSL_GUARDED_BY`, `ABSL_GUARDED_BY_FIXME`, `ABSL_HARDENING_ASSERT`, `ABSL_HARDENING_ASSERT_SLOW`, `ABSL_HAVE_ADDRESS_SANITIZER`, `ABSL_HAVE_ATTRIBUTE`, `ABSL_HAVE_BUILTIN`, `ABSL_HAVE_CPP_ATTRIBUTE`, `ABSL_HAVE_DATAFLOW_SANITIZER`, `ABSL_HAVE_EXCEPTIONS`, `ABSL_HAVE_FEATURE`, `ABSL_HAVE_HWADDRESS_SANITIZER`, `ABSL_HAVE_LEAK_SANITIZER`, `ABSL_HAVE_MEMORY_SANITIZER`, `ABSL_HAVE_THREAD_SANITIZER`, `ABSL_INIT_ATTRIBUTE_SECTION_VARS`, `ABSL_LOCKABLE`, `ABSL_LOCKS_EXCLUDED`, `ABSL_LOCK_RETURNED`, `ABSL_LOG`, `ABSL_LOG_EVERY_N`, `ABSL_LOG_EVERY_N_SEC`, `ABSL_LOG_EVERY_POW_2`, `ABSL_LOG_FIRST_N`, `ABSL_LOG_IF`, `ABSL_LOG_IF_EVERY_N`, `ABSL_LOG_IF_EVERY_N_SEC`, `ABSL_LOG_IF_EVERY_POW_2`, `ABSL_LOG_IF_FIRST_N`, `ABSL_MUST_USE_RESULT`, `ABSL_NAMESPACE_BEGIN`, `ABSL_NAMESPACE_END`, `ABSL_NO_THREAD_SAFETY_ANALYSIS`, `ABSL_NO_THREAD_SAFETY_ANALYSIS_FIXME`, `ABSL_NULLABILITY_COMPATIBLE`, `ABSL_OPTION_INLINE_NAMESPACE_NAME`, `ABSL_PCHECK`, `ABSL_PLOG`, `ABSL_PLOG_EVERY_N`, `ABSL_PLOG_EVERY_N_SEC`, `ABSL_PLOG_EVERY_POW_2`, `ABSL_PLOG_FIRST_N`, `ABSL_PLOG_IF`, `ABSL_PLOG_IF_EVERY_N`, `ABSL_PLOG_IF_EVERY_N_SEC`, `ABSL_PLOG_IF_EVERY_POW_2`, `ABSL_PLOG_IF_FIRST_N`, `ABSL_POINTERS_DEFAULT_NONNULL`, `ABSL_PREDICT_FALSE`, `ABSL_PREDICT_TRUE`, `ABSL_PRINTF_ATTRIBUTE`, `ABSL_PT_GUARDED_BY`, `ABSL_QCHECK`, `ABSL_QCHECK_EQ`, `ABSL_QCHECK_GE`, `ABSL_QCHECK_GT`, `ABSL_QCHECK_LE`, `ABSL_QCHECK_LT`, `ABSL_QCHECK_NE`, `ABSL_QCHECK_OK`, `ABSL_QCHECK_STRCASEEQ`, `ABSL_QCHECK_STRCASENE`, `ABSL_QCHECK_STREQ`, `ABSL_QCHECK_STRNE`, `ABSL_REQUIRE_EXPLICIT_INIT`, `ABSL_REQUIRE_STACK_ALIGN_TRAMPOLINE`, `ABSL_RETIRED_FLAG`, `ABSL_SCANF_ATTRIBUTE`, `ABSL_SCOPED_LOCKABLE`, `ABSL_SHARED_LOCKS_REQUIRED`, `ABSL_SHARED_LOCK_FUNCTION`, `ABSL_SHARED_TRYLOCK_FUNCTION`, `ABSL_TEST_DLL`, `ABSL_TS_FIXME`, `ABSL_TS_UNCHECKED`, `ABSL_TS_UNCHECKED_READ`, `ABSL_UNLOCK_FUNCTION`, `ABSL_UNREACHABLE`, `ABSL_VLOG`, `ABSL_VLOG_EVERY_N`, `ABSL_VLOG_EVERY_N_SEC`, `ABSL_VLOG_EVERY_POW_2`, `ABSL_VLOG_FIRST_N`, `ABSL_VLOG_IS_ON`, `ABSL_XRAY_ALWAYS_INSTRUMENT`, `ABSL_XRAY_LOG_ARGS`, `ABSL_XRAY_NEVER_INSTRUMENT`, `CHECK`, `CHECK_EQ`, `CHECK_GE`, `CHECK_GT`, `CHECK_LE`, `CHECK_LT`, `CHECK_NE`, `CHECK_OK`, `CHECK_STRCASEEQ`, `CHECK_STRCASENE`, `CHECK_STREQ`, `CHECK_STRNE`, `COMPOP`, `DCHECK`, `DCHECK_EQ`, `DCHECK_GE`, `DCHECK_GT`, `DCHECK_LE`, `DCHECK_LT`, `DCHECK_NE`, `DCHECK_OK`, `DCHECK_STRCASEEQ`, `DCHECK_STRCASENE`, `DCHECK_STREQ`, `DCHECK_STRNE`, `DLOG`, `DLOG_EVERY_N`, `DLOG_EVERY_N_SEC`, `DLOG_EVERY_POW_2`, `DLOG_FIRST_N`, `DLOG_IF`, `DLOG_IF_EVERY_N`, `DLOG_IF_EVERY_N_SEC`, `DLOG_IF_EVERY_POW_2`, `DLOG_IF_FIRST_N`, `DVLOG`, `LOG`, `LOG_EVERY_N`, `LOG_EVERY_N_SEC`, `LOG_EVERY_POW_2`, `LOG_FIRST_N`, `LOG_IF`, `LOG_IF_EVERY_N`, `LOG_IF_EVERY_N_SEC`, `LOG_IF_EVERY_POW_2`, `LOG_IF_FIRST_N`, `PCHECK`, `PLOG`, `PLOG_EVERY_N`, `PLOG_EVERY_N_SEC`, `PLOG_EVERY_POW_2`, `PLOG_FIRST_N`, `PLOG_IF`, `PLOG_IF_EVERY_N`, `PLOG_IF_EVERY_N_SEC`, `PLOG_IF_EVERY_POW_2`, `PLOG_IF_FIRST_N`, `QCHECK`, `QCHECK_EQ`, `QCHECK_GE`, `QCHECK_GT`, `QCHECK_LE`, `QCHECK_LT`, `QCHECK_NE`, `QCHECK_OK`, `QCHECK_STRCASEEQ`, `QCHECK_STRCASENE`, `QCHECK_STREQ`, `QCHECK_STRNE`, `VLOG`, `VLOG_EVERY_N`, `VLOG_EVERY_N_SEC`, `VLOG_EVERY_POW_2`, `VLOG_FIRST_N`, `VLOG_IS_ON`
