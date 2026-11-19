// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.utility — the names of <absl/utility/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/utility/utility.h>

export module mcpplibs.mwrap.abseil.utility;

export namespace absl {
// standard library names Abseil re-declares as its own (16)
using ::absl::apply;
using ::absl::exchange;
using ::absl::forward;
using ::absl::in_place;
using ::absl::in_place_index;
using ::absl::in_place_index_t;
using ::absl::in_place_t;
using ::absl::in_place_type;
using ::absl::in_place_type_t;
using ::absl::index_sequence;
using ::absl::index_sequence_for;
using ::absl::integer_sequence;
using ::absl::make_from_tuple;
using ::absl::make_index_sequence;
using ::absl::make_integer_sequence;
using ::absl::move;
}  // namespace absl
