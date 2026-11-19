// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.flags — the names of <absl/flags/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/flags/commandlineflag.h>
#include <absl/flags/config.h>
#include <absl/flags/declare.h>
#include <absl/flags/flag.h>
#include <absl/flags/marshalling.h>
#include <absl/flags/parse.h>
#include <absl/flags/reflection.h>
#include <absl/flags/usage.h>
#include <absl/flags/usage_config.h>

export module mcpplibs.mwrap.abseil.flags;

export namespace absl {
// types (5)
using ::absl::CommandLineFlag;
#if !defined(__GNUC__) || defined(__clang__)
using ::absl::Flag;
#endif
using ::absl::FlagSaver;
using ::absl::FlagsUsageConfig;
using ::absl::UnrecognizedFlag;
// functions and operators (16)
using ::absl::AbslParseFlag;
using ::absl::AbslUnparseFlag;
using ::absl::FindCommandLineFlag;
using ::absl::GetAllFlags;
#if !defined(__GNUC__) || defined(__clang__)
using ::absl::GetFlag;
#endif
#if !defined(__GNUC__) || defined(__clang__)
using ::absl::GetFlagReflectionHandle;
#endif
using ::absl::ParseAbseilFlagsOnly;
using ::absl::ParseCommandLine;
using ::absl::ParseFlag;
using ::absl::ProgramUsageMessage;
using ::absl::ReportUnrecognizedFlags;
#if !defined(__GNUC__) || defined(__clang__)
using ::absl::SetFlag;
#endif
using ::absl::SetFlagsUsageConfig;
using ::absl::SetProgramUsageMessage;
using ::absl::UnparseFlag;
using ::absl::operator==;
}  // namespace absl

// Not exported: names that keep global-module-fragment declarations reachable (see tools/surface.py, KEEP).
namespace mwrap_abseil_reachable {
template <class C> using hashtable_debug_access = ::absl::container_internal::hashtable_debug_internal::HashtableDebugAccess<C>;
}  // namespace mwrap_abseil_reachable
