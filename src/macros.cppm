// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.macros — the integer and flag macros of Abseil's public headers as constants of the
// same names in mcpplibs::mwrap::abseil::macros, with the values they have where the module is built. A macro
// is not exported by a module: the others (LOG, CHECK, ABSL_FLAG, the attribute and annotation macros …)
// come from #include <mwrap/abseil/macros.hpp>, before the import.
module;
#include <absl/base/attributes.h>
#include <absl/base/call_once.h>
#include <absl/base/casts.h>
#include <absl/base/config.h>
#include <absl/base/const_init.h>
#include <absl/base/dynamic_annotations.h>
#include <absl/base/fast_type_id.h>
#include <absl/base/log_severity.h>
#include <absl/base/macros.h>
#include <absl/base/no_destructor.h>
#include <absl/base/nullability.h>
#include <absl/base/optimization.h>
#include <absl/base/options.h>
#include <absl/base/policy_checks.h>
#include <absl/base/port.h>
#include <absl/base/prefetch.h>
#include <absl/base/thread_annotations.h>
#include <absl/meta/type_traits.h>
#include <absl/utility/utility.h>
#include <absl/memory/memory.h>
#include <absl/functional/any_invocable.h>
#include <absl/functional/bind_front.h>
#include <absl/functional/function_ref.h>
#include <absl/functional/overload.h>
#include <absl/algorithm/algorithm.h>
#include <absl/algorithm/container.h>
#include <absl/numeric/bits.h>
#include <absl/numeric/int128.h>
#include <absl/types/any.h>
#include <absl/types/compare.h>
#include <absl/types/optional.h>
#include <absl/types/span.h>
#include <absl/types/variant.h>
#include <absl/hash/hash.h>
#include <absl/container/btree_map.h>
#include <absl/container/btree_set.h>
#include <absl/container/fixed_array.h>
#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <absl/container/hash_container_defaults.h>
#include <absl/container/inlined_vector.h>
#include <absl/container/node_hash_map.h>
#include <absl/container/node_hash_set.h>
#include <absl/strings/ascii.h>
#include <absl/strings/charconv.h>
#include <absl/strings/charset.h>
#include <absl/strings/cord.h>
#include <absl/strings/cord_analysis.h>
#include <absl/strings/cord_buffer.h>
#include <absl/strings/escaping.h>
#include <absl/strings/has_absl_stringify.h>
#include <absl/strings/has_ostream_operator.h>
#include <absl/strings/match.h>
#include <absl/strings/numbers.h>
#include <absl/strings/str_cat.h>
#include <absl/strings/str_format.h>
#include <absl/strings/str_join.h>
#include <absl/strings/str_replace.h>
#include <absl/strings/str_split.h>
#include <absl/strings/string_view.h>
#include <absl/strings/strip.h>
#include <absl/strings/substitute.h>
#include <absl/crc/crc32c.h>
#include <absl/cleanup/cleanup.h>
#include <absl/debugging/failure_signal_handler.h>
#include <absl/debugging/leak_check.h>
#include <absl/debugging/stacktrace.h>
#include <absl/debugging/symbolize.h>
#include <absl/synchronization/barrier.h>
#include <absl/synchronization/blocking_counter.h>
#include <absl/synchronization/mutex.h>
#include <absl/synchronization/notification.h>
#include <absl/time/civil_time.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>
#include <absl/status/status.h>
#include <absl/status/status_payload_printer.h>
#include <absl/status/statusor.h>
#include <absl/random/bernoulli_distribution.h>
#include <absl/random/beta_distribution.h>
#include <absl/random/bit_gen_ref.h>
#include <absl/random/discrete_distribution.h>
#include <absl/random/distributions.h>
#include <absl/random/exponential_distribution.h>
#include <absl/random/gaussian_distribution.h>
#include <absl/random/log_uniform_int_distribution.h>
#include <absl/random/poisson_distribution.h>
#include <absl/random/random.h>
#include <absl/random/seed_gen_exception.h>
#include <absl/random/seed_sequences.h>
#include <absl/random/uniform_int_distribution.h>
#include <absl/random/uniform_real_distribution.h>
#include <absl/random/zipf_distribution.h>
#include <absl/log/absl_check.h>
#include <absl/log/absl_log.h>
#include <absl/log/absl_vlog_is_on.h>
#include <absl/log/check.h>
#include <absl/log/die_if_null.h>
#include <absl/log/flags.h>
#include <absl/log/globals.h>
#include <absl/log/initialize.h>
#include <absl/log/log.h>
#include <absl/log/log_entry.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <absl/log/log_streamer.h>
#include <absl/log/structured.h>
#include <absl/log/vlog_is_on.h>
#include <absl/flags/commandlineflag.h>
#include <absl/flags/config.h>
#include <absl/flags/declare.h>
#include <absl/flags/flag.h>
#include <absl/flags/marshalling.h>
#include <absl/flags/parse.h>
#include <absl/flags/reflection.h>
#include <absl/flags/usage.h>
#include <absl/flags/usage_config.h>

namespace mwrap_abseil_macros {
#ifdef ABSL_CACHELINE_SIZE
inline constexpr int value_ABSL_CACHELINE_SIZE = ABSL_CACHELINE_SIZE;
#define MWRAP_HAS_ABSL_CACHELINE_SIZE 1
#endif
#ifdef ABSL_FLAGS_STRIP_NAMES
inline constexpr int value_ABSL_FLAGS_STRIP_NAMES = ABSL_FLAGS_STRIP_NAMES;
#define MWRAP_HAS_ABSL_FLAGS_STRIP_NAMES 1
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL
inline constexpr int value_ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL = ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL;
#define MWRAP_HAS_ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL 1
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_SECTION
inline constexpr int value_ABSL_HAVE_ATTRIBUTE_SECTION = ABSL_HAVE_ATTRIBUTE_SECTION;
#define MWRAP_HAS_ABSL_HAVE_ATTRIBUTE_SECTION 1
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_WEAK
inline constexpr int value_ABSL_HAVE_ATTRIBUTE_WEAK = ABSL_HAVE_ATTRIBUTE_WEAK;
#define MWRAP_HAS_ABSL_HAVE_ATTRIBUTE_WEAK 1
#endif
#ifdef ABSL_LTS_RELEASE_PATCH_LEVEL
inline constexpr int value_ABSL_LTS_RELEASE_PATCH_LEVEL = ABSL_LTS_RELEASE_PATCH_LEVEL;
#define MWRAP_HAS_ABSL_LTS_RELEASE_PATCH_LEVEL 1
#endif
#ifdef ABSL_LTS_RELEASE_VERSION
inline constexpr int value_ABSL_LTS_RELEASE_VERSION = ABSL_LTS_RELEASE_VERSION;
#define MWRAP_HAS_ABSL_LTS_RELEASE_VERSION 1
#endif
#ifdef ABSL_OPTION_HARDENED
inline constexpr int value_ABSL_OPTION_HARDENED = ABSL_OPTION_HARDENED;
#define MWRAP_HAS_ABSL_OPTION_HARDENED 1
#endif
#ifdef ABSL_OPTION_USE_INLINE_NAMESPACE
inline constexpr int value_ABSL_OPTION_USE_INLINE_NAMESPACE = ABSL_OPTION_USE_INLINE_NAMESPACE;
#define MWRAP_HAS_ABSL_OPTION_USE_INLINE_NAMESPACE 1
#endif
#ifdef ABSL_OPTION_USE_STD_ORDERING
inline constexpr int value_ABSL_OPTION_USE_STD_ORDERING = ABSL_OPTION_USE_STD_ORDERING;
#define MWRAP_HAS_ABSL_OPTION_USE_STD_ORDERING 1
#endif
#ifdef ABSL_OPTION_USE_STD_STRING_VIEW
inline constexpr int value_ABSL_OPTION_USE_STD_STRING_VIEW = ABSL_OPTION_USE_STD_STRING_VIEW;
#define MWRAP_HAS_ABSL_OPTION_USE_STD_STRING_VIEW 1
#endif
#ifdef ABSL_HAVE_ALARM
inline constexpr bool value_ABSL_HAVE_ALARM = true;
#else
inline constexpr bool value_ABSL_HAVE_ALARM = false;
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_ALWAYS_INLINE
inline constexpr bool value_ABSL_HAVE_ATTRIBUTE_ALWAYS_INLINE = true;
#else
inline constexpr bool value_ABSL_HAVE_ATTRIBUTE_ALWAYS_INLINE = false;
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_NOINLINE
inline constexpr bool value_ABSL_HAVE_ATTRIBUTE_NOINLINE = true;
#else
inline constexpr bool value_ABSL_HAVE_ATTRIBUTE_NOINLINE = false;
#endif
#ifdef ABSL_HAVE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION
inline constexpr bool value_ABSL_HAVE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION = true;
#else
inline constexpr bool value_ABSL_HAVE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION = false;
#endif
#ifdef ABSL_HAVE_CONSTANT_EVALUATED
inline constexpr bool value_ABSL_HAVE_CONSTANT_EVALUATED = true;
#else
inline constexpr bool value_ABSL_HAVE_CONSTANT_EVALUATED = false;
#endif
#ifdef ABSL_HAVE_INTRINSIC_INT128
inline constexpr bool value_ABSL_HAVE_INTRINSIC_INT128 = true;
#else
inline constexpr bool value_ABSL_HAVE_INTRINSIC_INT128 = false;
#endif
#ifdef ABSL_HAVE_MMAP
inline constexpr bool value_ABSL_HAVE_MMAP = true;
#else
inline constexpr bool value_ABSL_HAVE_MMAP = false;
#endif
#ifdef ABSL_HAVE_PREFETCH
inline constexpr bool value_ABSL_HAVE_PREFETCH = true;
#else
inline constexpr bool value_ABSL_HAVE_PREFETCH = false;
#endif
#ifdef ABSL_HAVE_PTHREAD_GETSCHEDPARAM
inline constexpr bool value_ABSL_HAVE_PTHREAD_GETSCHEDPARAM = true;
#else
inline constexpr bool value_ABSL_HAVE_PTHREAD_GETSCHEDPARAM = false;
#endif
#ifdef ABSL_HAVE_SCHED_GETCPU
inline constexpr bool value_ABSL_HAVE_SCHED_GETCPU = true;
#else
inline constexpr bool value_ABSL_HAVE_SCHED_GETCPU = false;
#endif
#ifdef ABSL_HAVE_SCHED_YIELD
inline constexpr bool value_ABSL_HAVE_SCHED_YIELD = true;
#else
inline constexpr bool value_ABSL_HAVE_SCHED_YIELD = false;
#endif
#ifdef ABSL_HAVE_SEMAPHORE_H
inline constexpr bool value_ABSL_HAVE_SEMAPHORE_H = true;
#else
inline constexpr bool value_ABSL_HAVE_SEMAPHORE_H = false;
#endif
#ifdef ABSL_HAVE_STD_ANY
inline constexpr bool value_ABSL_HAVE_STD_ANY = true;
#else
inline constexpr bool value_ABSL_HAVE_STD_ANY = false;
#endif
#ifdef ABSL_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE
inline constexpr bool value_ABSL_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE = true;
#else
inline constexpr bool value_ABSL_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE = false;
#endif
#ifdef ABSL_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE
inline constexpr bool value_ABSL_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE = true;
#else
inline constexpr bool value_ABSL_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE = false;
#endif
#ifdef ABSL_HAVE_STD_IS_TRIVIALLY_COPYABLE
inline constexpr bool value_ABSL_HAVE_STD_IS_TRIVIALLY_COPYABLE = true;
#else
inline constexpr bool value_ABSL_HAVE_STD_IS_TRIVIALLY_COPYABLE = false;
#endif
#ifdef ABSL_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE
inline constexpr bool value_ABSL_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE = true;
#else
inline constexpr bool value_ABSL_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE = false;
#endif
#ifdef ABSL_HAVE_STD_OPTIONAL
inline constexpr bool value_ABSL_HAVE_STD_OPTIONAL = true;
#else
inline constexpr bool value_ABSL_HAVE_STD_OPTIONAL = false;
#endif
#ifdef ABSL_HAVE_STD_ORDERING
inline constexpr bool value_ABSL_HAVE_STD_ORDERING = true;
#else
inline constexpr bool value_ABSL_HAVE_STD_ORDERING = false;
#endif
#ifdef ABSL_HAVE_STD_STRING_VIEW
inline constexpr bool value_ABSL_HAVE_STD_STRING_VIEW = true;
#else
inline constexpr bool value_ABSL_HAVE_STD_STRING_VIEW = false;
#endif
#ifdef ABSL_HAVE_STD_VARIANT
inline constexpr bool value_ABSL_HAVE_STD_VARIANT = true;
#else
inline constexpr bool value_ABSL_HAVE_STD_VARIANT = false;
#endif
#ifdef ABSL_HAVE_THREAD_LOCAL
inline constexpr bool value_ABSL_HAVE_THREAD_LOCAL = true;
#else
inline constexpr bool value_ABSL_HAVE_THREAD_LOCAL = false;
#endif
#ifdef ABSL_HAVE_TLS
inline constexpr bool value_ABSL_HAVE_TLS = true;
#else
inline constexpr bool value_ABSL_HAVE_TLS = false;
#endif
#ifdef ABSL_IS_BIG_ENDIAN
inline constexpr bool value_ABSL_IS_BIG_ENDIAN = true;
#else
inline constexpr bool value_ABSL_IS_BIG_ENDIAN = false;
#endif
#ifdef ABSL_IS_LITTLE_ENDIAN
inline constexpr bool value_ABSL_IS_LITTLE_ENDIAN = true;
#else
inline constexpr bool value_ABSL_IS_LITTLE_ENDIAN = false;
#endif
#ifdef ABSL_USES_STD_ANY
inline constexpr bool value_ABSL_USES_STD_ANY = true;
#else
inline constexpr bool value_ABSL_USES_STD_ANY = false;
#endif
#ifdef ABSL_USES_STD_OPTIONAL
inline constexpr bool value_ABSL_USES_STD_OPTIONAL = true;
#else
inline constexpr bool value_ABSL_USES_STD_OPTIONAL = false;
#endif
#ifdef ABSL_USES_STD_ORDERING
inline constexpr bool value_ABSL_USES_STD_ORDERING = true;
#else
inline constexpr bool value_ABSL_USES_STD_ORDERING = false;
#endif
#ifdef ABSL_USES_STD_STRING_VIEW
inline constexpr bool value_ABSL_USES_STD_STRING_VIEW = true;
#else
inline constexpr bool value_ABSL_USES_STD_STRING_VIEW = false;
#endif
#ifdef ABSL_USES_STD_VARIANT
inline constexpr bool value_ABSL_USES_STD_VARIANT = true;
#else
inline constexpr bool value_ABSL_USES_STD_VARIANT = false;
#endif
}  // namespace mwrap_abseil_macros

#undef ABSL_CACHELINE_SIZE
#undef ABSL_FLAGS_STRIP_NAMES
#undef ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL
#undef ABSL_HAVE_ATTRIBUTE_SECTION
#undef ABSL_HAVE_ATTRIBUTE_WEAK
#undef ABSL_LTS_RELEASE_PATCH_LEVEL
#undef ABSL_LTS_RELEASE_VERSION
#undef ABSL_OPTION_HARDENED
#undef ABSL_OPTION_USE_INLINE_NAMESPACE
#undef ABSL_OPTION_USE_STD_ORDERING
#undef ABSL_OPTION_USE_STD_STRING_VIEW
#undef ABSL_HAVE_ALARM
#undef ABSL_HAVE_ATTRIBUTE_ALWAYS_INLINE
#undef ABSL_HAVE_ATTRIBUTE_NOINLINE
#undef ABSL_HAVE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION
#undef ABSL_HAVE_CONSTANT_EVALUATED
#undef ABSL_HAVE_INTRINSIC_INT128
#undef ABSL_HAVE_MMAP
#undef ABSL_HAVE_PREFETCH
#undef ABSL_HAVE_PTHREAD_GETSCHEDPARAM
#undef ABSL_HAVE_SCHED_GETCPU
#undef ABSL_HAVE_SCHED_YIELD
#undef ABSL_HAVE_SEMAPHORE_H
#undef ABSL_HAVE_STD_ANY
#undef ABSL_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE
#undef ABSL_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE
#undef ABSL_HAVE_STD_IS_TRIVIALLY_COPYABLE
#undef ABSL_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE
#undef ABSL_HAVE_STD_OPTIONAL
#undef ABSL_HAVE_STD_ORDERING
#undef ABSL_HAVE_STD_STRING_VIEW
#undef ABSL_HAVE_STD_VARIANT
#undef ABSL_HAVE_THREAD_LOCAL
#undef ABSL_HAVE_TLS
#undef ABSL_IS_BIG_ENDIAN
#undef ABSL_IS_LITTLE_ENDIAN
#undef ABSL_USES_STD_ANY
#undef ABSL_USES_STD_OPTIONAL
#undef ABSL_USES_STD_ORDERING
#undef ABSL_USES_STD_STRING_VIEW
#undef ABSL_USES_STD_VARIANT

export module mcpplibs.mwrap.abseil.macros;

export namespace mcpplibs::mwrap::abseil::macros {

#ifdef MWRAP_HAS_ABSL_CACHELINE_SIZE
inline constexpr int ABSL_CACHELINE_SIZE = mwrap_abseil_macros::value_ABSL_CACHELINE_SIZE;
#endif
#ifdef MWRAP_HAS_ABSL_FLAGS_STRIP_NAMES
inline constexpr int ABSL_FLAGS_STRIP_NAMES = mwrap_abseil_macros::value_ABSL_FLAGS_STRIP_NAMES;
#endif
#ifdef MWRAP_HAS_ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL
inline constexpr int ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL = mwrap_abseil_macros::value_ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL;
#endif
#ifdef MWRAP_HAS_ABSL_HAVE_ATTRIBUTE_SECTION
inline constexpr int ABSL_HAVE_ATTRIBUTE_SECTION = mwrap_abseil_macros::value_ABSL_HAVE_ATTRIBUTE_SECTION;
#endif
#ifdef MWRAP_HAS_ABSL_HAVE_ATTRIBUTE_WEAK
inline constexpr int ABSL_HAVE_ATTRIBUTE_WEAK = mwrap_abseil_macros::value_ABSL_HAVE_ATTRIBUTE_WEAK;
#endif
#ifdef MWRAP_HAS_ABSL_LTS_RELEASE_PATCH_LEVEL
inline constexpr int ABSL_LTS_RELEASE_PATCH_LEVEL = mwrap_abseil_macros::value_ABSL_LTS_RELEASE_PATCH_LEVEL;
#endif
#ifdef MWRAP_HAS_ABSL_LTS_RELEASE_VERSION
inline constexpr int ABSL_LTS_RELEASE_VERSION = mwrap_abseil_macros::value_ABSL_LTS_RELEASE_VERSION;
#endif
#ifdef MWRAP_HAS_ABSL_OPTION_HARDENED
inline constexpr int ABSL_OPTION_HARDENED = mwrap_abseil_macros::value_ABSL_OPTION_HARDENED;
#endif
#ifdef MWRAP_HAS_ABSL_OPTION_USE_INLINE_NAMESPACE
inline constexpr int ABSL_OPTION_USE_INLINE_NAMESPACE = mwrap_abseil_macros::value_ABSL_OPTION_USE_INLINE_NAMESPACE;
#endif
#ifdef MWRAP_HAS_ABSL_OPTION_USE_STD_ORDERING
inline constexpr int ABSL_OPTION_USE_STD_ORDERING = mwrap_abseil_macros::value_ABSL_OPTION_USE_STD_ORDERING;
#endif
#ifdef MWRAP_HAS_ABSL_OPTION_USE_STD_STRING_VIEW
inline constexpr int ABSL_OPTION_USE_STD_STRING_VIEW = mwrap_abseil_macros::value_ABSL_OPTION_USE_STD_STRING_VIEW;
#endif
inline constexpr bool ABSL_HAVE_ALARM = mwrap_abseil_macros::value_ABSL_HAVE_ALARM;
inline constexpr bool ABSL_HAVE_ATTRIBUTE_ALWAYS_INLINE = mwrap_abseil_macros::value_ABSL_HAVE_ATTRIBUTE_ALWAYS_INLINE;
inline constexpr bool ABSL_HAVE_ATTRIBUTE_NOINLINE = mwrap_abseil_macros::value_ABSL_HAVE_ATTRIBUTE_NOINLINE;
inline constexpr bool ABSL_HAVE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION = mwrap_abseil_macros::value_ABSL_HAVE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION;
inline constexpr bool ABSL_HAVE_CONSTANT_EVALUATED = mwrap_abseil_macros::value_ABSL_HAVE_CONSTANT_EVALUATED;
inline constexpr bool ABSL_HAVE_INTRINSIC_INT128 = mwrap_abseil_macros::value_ABSL_HAVE_INTRINSIC_INT128;
inline constexpr bool ABSL_HAVE_MMAP = mwrap_abseil_macros::value_ABSL_HAVE_MMAP;
inline constexpr bool ABSL_HAVE_PREFETCH = mwrap_abseil_macros::value_ABSL_HAVE_PREFETCH;
inline constexpr bool ABSL_HAVE_PTHREAD_GETSCHEDPARAM = mwrap_abseil_macros::value_ABSL_HAVE_PTHREAD_GETSCHEDPARAM;
inline constexpr bool ABSL_HAVE_SCHED_GETCPU = mwrap_abseil_macros::value_ABSL_HAVE_SCHED_GETCPU;
inline constexpr bool ABSL_HAVE_SCHED_YIELD = mwrap_abseil_macros::value_ABSL_HAVE_SCHED_YIELD;
inline constexpr bool ABSL_HAVE_SEMAPHORE_H = mwrap_abseil_macros::value_ABSL_HAVE_SEMAPHORE_H;
inline constexpr bool ABSL_HAVE_STD_ANY = mwrap_abseil_macros::value_ABSL_HAVE_STD_ANY;
inline constexpr bool ABSL_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE = mwrap_abseil_macros::value_ABSL_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE;
inline constexpr bool ABSL_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE = mwrap_abseil_macros::value_ABSL_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE;
inline constexpr bool ABSL_HAVE_STD_IS_TRIVIALLY_COPYABLE = mwrap_abseil_macros::value_ABSL_HAVE_STD_IS_TRIVIALLY_COPYABLE;
inline constexpr bool ABSL_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE = mwrap_abseil_macros::value_ABSL_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE;
inline constexpr bool ABSL_HAVE_STD_OPTIONAL = mwrap_abseil_macros::value_ABSL_HAVE_STD_OPTIONAL;
inline constexpr bool ABSL_HAVE_STD_ORDERING = mwrap_abseil_macros::value_ABSL_HAVE_STD_ORDERING;
inline constexpr bool ABSL_HAVE_STD_STRING_VIEW = mwrap_abseil_macros::value_ABSL_HAVE_STD_STRING_VIEW;
inline constexpr bool ABSL_HAVE_STD_VARIANT = mwrap_abseil_macros::value_ABSL_HAVE_STD_VARIANT;
inline constexpr bool ABSL_HAVE_THREAD_LOCAL = mwrap_abseil_macros::value_ABSL_HAVE_THREAD_LOCAL;
inline constexpr bool ABSL_HAVE_TLS = mwrap_abseil_macros::value_ABSL_HAVE_TLS;
inline constexpr bool ABSL_IS_BIG_ENDIAN = mwrap_abseil_macros::value_ABSL_IS_BIG_ENDIAN;
inline constexpr bool ABSL_IS_LITTLE_ENDIAN = mwrap_abseil_macros::value_ABSL_IS_LITTLE_ENDIAN;
inline constexpr bool ABSL_USES_STD_ANY = mwrap_abseil_macros::value_ABSL_USES_STD_ANY;
inline constexpr bool ABSL_USES_STD_OPTIONAL = mwrap_abseil_macros::value_ABSL_USES_STD_OPTIONAL;
inline constexpr bool ABSL_USES_STD_ORDERING = mwrap_abseil_macros::value_ABSL_USES_STD_ORDERING;
inline constexpr bool ABSL_USES_STD_STRING_VIEW = mwrap_abseil_macros::value_ABSL_USES_STD_STRING_VIEW;
inline constexpr bool ABSL_USES_STD_VARIANT = mwrap_abseil_macros::value_ABSL_USES_STD_VARIANT;

}  // namespace mcpplibs::mwrap::abseil::macros
