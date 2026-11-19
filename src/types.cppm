// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.types — the names of <absl/types/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/types/any.h>
#include <absl/types/compare.h>
#include <absl/types/optional.h>
#include <absl/types/span.h>
#include <absl/types/variant.h>

export module mcpplibs.mwrap.abseil.types;

export namespace absl {
// types (1)
using ::absl::Span;
// functions and operators (9)
using ::absl::ConvertVariantTo;
using ::absl::MakeConstSpan;
using ::absl::MakeSpan;
using ::absl::operator!=;
using ::absl::operator<;
using ::absl::operator<=;
using ::absl::operator==;
using ::absl::operator>;
using ::absl::operator>=;
// standard library names Abseil re-declares as its own (24)
using ::absl::any;
using ::absl::any_cast;
using ::absl::bad_any_cast;
using ::absl::bad_optional_access;
using ::absl::bad_variant_access;
using ::absl::get;
using ::absl::get_if;
using ::absl::holds_alternative;
using ::absl::make_any;
using ::absl::make_optional;
using ::absl::monostate;
using ::absl::nullopt;
using ::absl::nullopt_t;
using ::absl::optional;
using ::absl::partial_ordering;
using ::absl::strong_ordering;
using ::absl::variant;
using ::absl::variant_alternative;
using ::absl::variant_alternative_t;
using ::absl::variant_npos;
using ::absl::variant_size;
using ::absl::variant_size_v;
using ::absl::visit;
using ::absl::weak_ordering;
}  // namespace absl
