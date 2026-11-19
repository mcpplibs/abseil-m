// Written by tools/surface.py: every constant of mcpplibs.mwrap.abseil.macros against the macro of the same
// name in the headers, which are included first. The macro's value is taken, the macro undefined, and only
// then the module imported: a defined macro would replace the qualified name as well.
#include <mwrap/abseil/macros.hpp>

namespace header {
#ifdef ABSL_CACHELINE_SIZE
constexpr int absl_cacheline_size = ABSL_CACHELINE_SIZE;
#define MWRAP_TEST_HAS_ABSL_CACHELINE_SIZE 1
#endif
#ifdef ABSL_FLAGS_STRIP_NAMES
constexpr int absl_flags_strip_names = ABSL_FLAGS_STRIP_NAMES;
#define MWRAP_TEST_HAS_ABSL_FLAGS_STRIP_NAMES 1
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL
constexpr int absl_have_attribute_no_tail_call = ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL;
#define MWRAP_TEST_HAS_ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL 1
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_SECTION
constexpr int absl_have_attribute_section = ABSL_HAVE_ATTRIBUTE_SECTION;
#define MWRAP_TEST_HAS_ABSL_HAVE_ATTRIBUTE_SECTION 1
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_WEAK
constexpr int absl_have_attribute_weak = ABSL_HAVE_ATTRIBUTE_WEAK;
#define MWRAP_TEST_HAS_ABSL_HAVE_ATTRIBUTE_WEAK 1
#endif
#ifdef ABSL_LTS_RELEASE_PATCH_LEVEL
constexpr int absl_lts_release_patch_level = ABSL_LTS_RELEASE_PATCH_LEVEL;
#define MWRAP_TEST_HAS_ABSL_LTS_RELEASE_PATCH_LEVEL 1
#endif
#ifdef ABSL_LTS_RELEASE_VERSION
constexpr int absl_lts_release_version = ABSL_LTS_RELEASE_VERSION;
#define MWRAP_TEST_HAS_ABSL_LTS_RELEASE_VERSION 1
#endif
#ifdef ABSL_OPTION_HARDENED
constexpr int absl_option_hardened = ABSL_OPTION_HARDENED;
#define MWRAP_TEST_HAS_ABSL_OPTION_HARDENED 1
#endif
#ifdef ABSL_OPTION_USE_INLINE_NAMESPACE
constexpr int absl_option_use_inline_namespace = ABSL_OPTION_USE_INLINE_NAMESPACE;
#define MWRAP_TEST_HAS_ABSL_OPTION_USE_INLINE_NAMESPACE 1
#endif
#ifdef ABSL_OPTION_USE_STD_ORDERING
constexpr int absl_option_use_std_ordering = ABSL_OPTION_USE_STD_ORDERING;
#define MWRAP_TEST_HAS_ABSL_OPTION_USE_STD_ORDERING 1
#endif
#ifdef ABSL_OPTION_USE_STD_STRING_VIEW
constexpr int absl_option_use_std_string_view = ABSL_OPTION_USE_STD_STRING_VIEW;
#define MWRAP_TEST_HAS_ABSL_OPTION_USE_STD_STRING_VIEW 1
#endif
#ifdef ABSL_HAVE_ALARM
constexpr bool absl_have_alarm = true;
#else
constexpr bool absl_have_alarm = false;
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_ALWAYS_INLINE
constexpr bool absl_have_attribute_always_inline = true;
#else
constexpr bool absl_have_attribute_always_inline = false;
#endif
#ifdef ABSL_HAVE_ATTRIBUTE_NOINLINE
constexpr bool absl_have_attribute_noinline = true;
#else
constexpr bool absl_have_attribute_noinline = false;
#endif
#ifdef ABSL_HAVE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION
constexpr bool absl_have_class_template_argument_deduction = true;
#else
constexpr bool absl_have_class_template_argument_deduction = false;
#endif
#ifdef ABSL_HAVE_CONSTANT_EVALUATED
constexpr bool absl_have_constant_evaluated = true;
#else
constexpr bool absl_have_constant_evaluated = false;
#endif
#ifdef ABSL_HAVE_INTRINSIC_INT128
constexpr bool absl_have_intrinsic_int128 = true;
#else
constexpr bool absl_have_intrinsic_int128 = false;
#endif
#ifdef ABSL_HAVE_MMAP
constexpr bool absl_have_mmap = true;
#else
constexpr bool absl_have_mmap = false;
#endif
#ifdef ABSL_HAVE_PREFETCH
constexpr bool absl_have_prefetch = true;
#else
constexpr bool absl_have_prefetch = false;
#endif
#ifdef ABSL_HAVE_PTHREAD_GETSCHEDPARAM
constexpr bool absl_have_pthread_getschedparam = true;
#else
constexpr bool absl_have_pthread_getschedparam = false;
#endif
#ifdef ABSL_HAVE_SCHED_GETCPU
constexpr bool absl_have_sched_getcpu = true;
#else
constexpr bool absl_have_sched_getcpu = false;
#endif
#ifdef ABSL_HAVE_SCHED_YIELD
constexpr bool absl_have_sched_yield = true;
#else
constexpr bool absl_have_sched_yield = false;
#endif
#ifdef ABSL_HAVE_SEMAPHORE_H
constexpr bool absl_have_semaphore_h = true;
#else
constexpr bool absl_have_semaphore_h = false;
#endif
#ifdef ABSL_HAVE_STD_ANY
constexpr bool absl_have_std_any = true;
#else
constexpr bool absl_have_std_any = false;
#endif
#ifdef ABSL_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE
constexpr bool absl_have_std_is_trivially_assignable = true;
#else
constexpr bool absl_have_std_is_trivially_assignable = false;
#endif
#ifdef ABSL_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE
constexpr bool absl_have_std_is_trivially_constructible = true;
#else
constexpr bool absl_have_std_is_trivially_constructible = false;
#endif
#ifdef ABSL_HAVE_STD_IS_TRIVIALLY_COPYABLE
constexpr bool absl_have_std_is_trivially_copyable = true;
#else
constexpr bool absl_have_std_is_trivially_copyable = false;
#endif
#ifdef ABSL_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE
constexpr bool absl_have_std_is_trivially_destructible = true;
#else
constexpr bool absl_have_std_is_trivially_destructible = false;
#endif
#ifdef ABSL_HAVE_STD_OPTIONAL
constexpr bool absl_have_std_optional = true;
#else
constexpr bool absl_have_std_optional = false;
#endif
#ifdef ABSL_HAVE_STD_ORDERING
constexpr bool absl_have_std_ordering = true;
#else
constexpr bool absl_have_std_ordering = false;
#endif
#ifdef ABSL_HAVE_STD_STRING_VIEW
constexpr bool absl_have_std_string_view = true;
#else
constexpr bool absl_have_std_string_view = false;
#endif
#ifdef ABSL_HAVE_STD_VARIANT
constexpr bool absl_have_std_variant = true;
#else
constexpr bool absl_have_std_variant = false;
#endif
#ifdef ABSL_HAVE_THREAD_LOCAL
constexpr bool absl_have_thread_local = true;
#else
constexpr bool absl_have_thread_local = false;
#endif
#ifdef ABSL_HAVE_TLS
constexpr bool absl_have_tls = true;
#else
constexpr bool absl_have_tls = false;
#endif
#ifdef ABSL_IS_BIG_ENDIAN
constexpr bool absl_is_big_endian = true;
#else
constexpr bool absl_is_big_endian = false;
#endif
#ifdef ABSL_IS_LITTLE_ENDIAN
constexpr bool absl_is_little_endian = true;
#else
constexpr bool absl_is_little_endian = false;
#endif
#ifdef ABSL_USES_STD_ANY
constexpr bool absl_uses_std_any = true;
#else
constexpr bool absl_uses_std_any = false;
#endif
#ifdef ABSL_USES_STD_OPTIONAL
constexpr bool absl_uses_std_optional = true;
#else
constexpr bool absl_uses_std_optional = false;
#endif
#ifdef ABSL_USES_STD_ORDERING
constexpr bool absl_uses_std_ordering = true;
#else
constexpr bool absl_uses_std_ordering = false;
#endif
#ifdef ABSL_USES_STD_STRING_VIEW
constexpr bool absl_uses_std_string_view = true;
#else
constexpr bool absl_uses_std_string_view = false;
#endif
#ifdef ABSL_USES_STD_VARIANT
constexpr bool absl_uses_std_variant = true;
#else
constexpr bool absl_uses_std_variant = false;
#endif
}  // namespace header
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

#include <gtest/gtest.h>

import mcpplibs.mwrap.abseil.macros;

namespace macros = mcpplibs::mwrap::abseil::macros;

#ifdef MWRAP_TEST_HAS_ABSL_CACHELINE_SIZE
static_assert(macros::ABSL_CACHELINE_SIZE == header::absl_cacheline_size);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_FLAGS_STRIP_NAMES
static_assert(macros::ABSL_FLAGS_STRIP_NAMES == header::absl_flags_strip_names);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL
static_assert(macros::ABSL_HAVE_ATTRIBUTE_NO_TAIL_CALL == header::absl_have_attribute_no_tail_call);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_HAVE_ATTRIBUTE_SECTION
static_assert(macros::ABSL_HAVE_ATTRIBUTE_SECTION == header::absl_have_attribute_section);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_HAVE_ATTRIBUTE_WEAK
static_assert(macros::ABSL_HAVE_ATTRIBUTE_WEAK == header::absl_have_attribute_weak);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_LTS_RELEASE_PATCH_LEVEL
static_assert(macros::ABSL_LTS_RELEASE_PATCH_LEVEL == header::absl_lts_release_patch_level);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_LTS_RELEASE_VERSION
static_assert(macros::ABSL_LTS_RELEASE_VERSION == header::absl_lts_release_version);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_OPTION_HARDENED
static_assert(macros::ABSL_OPTION_HARDENED == header::absl_option_hardened);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_OPTION_USE_INLINE_NAMESPACE
static_assert(macros::ABSL_OPTION_USE_INLINE_NAMESPACE == header::absl_option_use_inline_namespace);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_OPTION_USE_STD_ORDERING
static_assert(macros::ABSL_OPTION_USE_STD_ORDERING == header::absl_option_use_std_ordering);
#endif
#ifdef MWRAP_TEST_HAS_ABSL_OPTION_USE_STD_STRING_VIEW
static_assert(macros::ABSL_OPTION_USE_STD_STRING_VIEW == header::absl_option_use_std_string_view);
#endif
static_assert(macros::ABSL_HAVE_ALARM == header::absl_have_alarm);
static_assert(macros::ABSL_HAVE_ATTRIBUTE_ALWAYS_INLINE == header::absl_have_attribute_always_inline);
static_assert(macros::ABSL_HAVE_ATTRIBUTE_NOINLINE == header::absl_have_attribute_noinline);
static_assert(macros::ABSL_HAVE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION == header::absl_have_class_template_argument_deduction);
static_assert(macros::ABSL_HAVE_CONSTANT_EVALUATED == header::absl_have_constant_evaluated);
static_assert(macros::ABSL_HAVE_INTRINSIC_INT128 == header::absl_have_intrinsic_int128);
static_assert(macros::ABSL_HAVE_MMAP == header::absl_have_mmap);
static_assert(macros::ABSL_HAVE_PREFETCH == header::absl_have_prefetch);
static_assert(macros::ABSL_HAVE_PTHREAD_GETSCHEDPARAM == header::absl_have_pthread_getschedparam);
static_assert(macros::ABSL_HAVE_SCHED_GETCPU == header::absl_have_sched_getcpu);
static_assert(macros::ABSL_HAVE_SCHED_YIELD == header::absl_have_sched_yield);
static_assert(macros::ABSL_HAVE_SEMAPHORE_H == header::absl_have_semaphore_h);
static_assert(macros::ABSL_HAVE_STD_ANY == header::absl_have_std_any);
static_assert(macros::ABSL_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE == header::absl_have_std_is_trivially_assignable);
static_assert(macros::ABSL_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE == header::absl_have_std_is_trivially_constructible);
static_assert(macros::ABSL_HAVE_STD_IS_TRIVIALLY_COPYABLE == header::absl_have_std_is_trivially_copyable);
static_assert(macros::ABSL_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE == header::absl_have_std_is_trivially_destructible);
static_assert(macros::ABSL_HAVE_STD_OPTIONAL == header::absl_have_std_optional);
static_assert(macros::ABSL_HAVE_STD_ORDERING == header::absl_have_std_ordering);
static_assert(macros::ABSL_HAVE_STD_STRING_VIEW == header::absl_have_std_string_view);
static_assert(macros::ABSL_HAVE_STD_VARIANT == header::absl_have_std_variant);
static_assert(macros::ABSL_HAVE_THREAD_LOCAL == header::absl_have_thread_local);
static_assert(macros::ABSL_HAVE_TLS == header::absl_have_tls);
static_assert(macros::ABSL_IS_BIG_ENDIAN == header::absl_is_big_endian);
static_assert(macros::ABSL_IS_LITTLE_ENDIAN == header::absl_is_little_endian);
static_assert(macros::ABSL_USES_STD_ANY == header::absl_uses_std_any);
static_assert(macros::ABSL_USES_STD_OPTIONAL == header::absl_uses_std_optional);
static_assert(macros::ABSL_USES_STD_ORDERING == header::absl_uses_std_ordering);
static_assert(macros::ABSL_USES_STD_STRING_VIEW == header::absl_uses_std_string_view);
static_assert(macros::ABSL_USES_STD_VARIANT == header::absl_uses_std_variant);

// Values the release fixes.
static_assert(macros::ABSL_LTS_RELEASE_VERSION == 20250512 && macros::ABSL_LTS_RELEASE_PATCH_LEVEL == 1);
static_assert(macros::ABSL_OPTION_USE_INLINE_NAMESPACE == 1 && macros::ABSL_IS_LITTLE_ENDIAN != macros::ABSL_IS_BIG_ENDIAN);
static_assert(macros::ABSL_HAVE_STD_OPTIONAL && macros::ABSL_USES_STD_OPTIONAL && macros::ABSL_USES_STD_STRING_VIEW);

TEST(Macros, MappedAsTheHeadersDefineThem) { EXPECT_EQ(41, 41); }
