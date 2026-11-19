// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.memory — the names of <absl/memory/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/memory/memory.h>

export module mcpplibs.mwrap.abseil.memory;

export namespace absl {
// types (2)
using ::absl::allocator_is_nothrow;
using ::absl::default_allocator_is_nothrow;
// functions and operators (4)
using ::absl::RawPtr;
using ::absl::ShareUniquePtr;
using ::absl::WeakenPtr;
using ::absl::WrapUnique;
// standard library names Abseil re-declares as its own (3)
using ::absl::allocator_traits;
using ::absl::make_unique;
using ::absl::pointer_traits;
}  // namespace absl
