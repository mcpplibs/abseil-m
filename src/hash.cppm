// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.hash — the names of <absl/hash/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/hash/hash.h>

export module mcpplibs.mwrap.abseil.hash;

export namespace absl {
// types (2)
using ::absl::Hash;
using ::absl::HashState;
// functions and operators (1)
using ::absl::HashOf;
}  // namespace absl
