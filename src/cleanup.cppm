// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.cleanup — the names of <absl/cleanup/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/cleanup/cleanup.h>

export module mcpplibs.mwrap.abseil.cleanup;

export namespace absl {
// types (1)
using ::absl::Cleanup;
// functions and operators (1)
using ::absl::MakeCleanup;
}  // namespace absl
