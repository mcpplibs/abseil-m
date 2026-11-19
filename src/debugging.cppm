// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.debugging — the names of <absl/debugging/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/debugging/failure_signal_handler.h>
#include <absl/debugging/leak_check.h>
#include <absl/debugging/stacktrace.h>
#include <absl/debugging/symbolize.h>

export module mcpplibs.mwrap.abseil.debugging;

export namespace absl {
// types (2)
using ::absl::FailureSignalHandlerOptions;
using ::absl::LeakCheckDisabler;
// functions and operators (16)
using ::absl::DefaultStackUnwinder;
using ::absl::DoIgnoreLeak;
using ::absl::FindAndReportLeaks;
using ::absl::GetStackFrames;
using ::absl::GetStackFramesWithContext;
using ::absl::GetStackTrace;
using ::absl::GetStackTraceWithContext;
using ::absl::HaveLeakSanitizer;
using ::absl::IgnoreLeak;
using ::absl::InitializeSymbolizer;
using ::absl::InstallFailureSignalHandler;
using ::absl::LeakCheckerIsActive;
using ::absl::RegisterLivePointers;
using ::absl::SetStackUnwinder;
using ::absl::Symbolize;
using ::absl::UnRegisterLivePointers;
}  // namespace absl
