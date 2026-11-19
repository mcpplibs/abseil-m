// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.functional — the names of <absl/functional/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/functional/any_invocable.h>
#include <absl/functional/bind_front.h>
#include <absl/functional/function_ref.h>
#include <absl/functional/overload.h>

export module mcpplibs.mwrap.abseil.functional;

export namespace absl {
// types (3)
using ::absl::AnyInvocable;
using ::absl::FunctionRef;
using ::absl::Overload;
// standard library names Abseil re-declares as its own (1)
using ::absl::bind_front;
}  // namespace absl
