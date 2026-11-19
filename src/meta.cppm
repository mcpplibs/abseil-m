// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.meta — the names of <absl/meta/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/meta/type_traits.h>

export module mcpplibs.mwrap.abseil.meta;

export namespace absl {
// types (5)
using ::absl::is_trivially_relocatable;
using ::absl::remove_cvref;
using ::absl::remove_cvref_t;
using ::absl::result_of_t;
using ::absl::void_t;
// functions and operators (1)
using ::absl::is_constant_evaluated;
// standard library names Abseil re-declares as its own (32)
using ::absl::add_const_t;
using ::absl::add_cv_t;
using ::absl::add_lvalue_reference_t;
using ::absl::add_pointer_t;
using ::absl::add_rvalue_reference_t;
using ::absl::add_volatile_t;
using ::absl::common_type_t;
using ::absl::conditional_t;
using ::absl::conjunction;
using ::absl::decay_t;
using ::absl::disjunction;
using ::absl::enable_if_t;
using ::absl::is_copy_assignable;
using ::absl::is_function;
using ::absl::is_move_assignable;
using ::absl::is_trivially_copy_assignable;
using ::absl::is_trivially_copy_constructible;
using ::absl::is_trivially_default_constructible;
using ::absl::is_trivially_destructible;
using ::absl::is_trivially_move_assignable;
using ::absl::is_trivially_move_constructible;
using ::absl::make_signed_t;
using ::absl::make_unsigned_t;
using ::absl::negation;
using ::absl::remove_all_extents_t;
using ::absl::remove_const_t;
using ::absl::remove_cv_t;
using ::absl::remove_extent_t;
using ::absl::remove_pointer_t;
using ::absl::remove_reference_t;
using ::absl::remove_volatile_t;
using ::absl::underlying_type_t;
}  // namespace absl
