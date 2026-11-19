// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.container — the names of <absl/container/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/container/btree_map.h>
#include <absl/container/btree_set.h>
#include <absl/container/fixed_array.h>
#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <absl/container/hash_container_defaults.h>
#include <absl/container/inlined_vector.h>
#include <absl/container/node_hash_map.h>
#include <absl/container/node_hash_set.h>

export module mcpplibs.mwrap.abseil.container;

export namespace absl {
// types (13)
using ::absl::DefaultHashContainerEq;
using ::absl::DefaultHashContainerHash;
using ::absl::FixedArray;
using ::absl::InlinedVector;
using ::absl::SynchLocksHeld;
using ::absl::btree_map;
using ::absl::btree_multimap;
using ::absl::btree_multiset;
using ::absl::btree_set;
using ::absl::flat_hash_map;
using ::absl::flat_hash_set;
using ::absl::node_hash_map;
using ::absl::node_hash_set;
// functions and operators (9)
using ::absl::AbslHashValue;
using ::absl::erase_if;
using ::absl::operator!=;
using ::absl::operator<;
using ::absl::operator<=;
using ::absl::operator==;
using ::absl::operator>;
using ::absl::operator>=;
using ::absl::swap;
}  // namespace absl

// Not exported: names that keep global-module-fragment declarations reachable (see tools/surface.py, KEEP).
namespace mwrap_abseil_reachable {
template <class C> using hashtable_debug_access = ::absl::container_internal::hashtable_debug_internal::HashtableDebugAccess<C>;
}  // namespace mwrap_abseil_reachable

// constants of internal linkage in the header, declared again under their names with their values
export namespace mcpplibs::mwrap::abseil {
inline constexpr auto kFixedArrayUseDefault = ::absl::kFixedArrayUseDefault;
}  // namespace mcpplibs::mwrap::abseil
