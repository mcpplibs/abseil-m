// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.log — the names of <absl/log/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/log/absl_check.h>
#include <absl/log/absl_log.h>
#include <absl/log/absl_vlog_is_on.h>
#include <absl/log/check.h>
#include <absl/log/die_if_null.h>
#include <absl/log/flags.h>
#include <absl/log/globals.h>
#include <absl/log/initialize.h>
#include <absl/log/log.h>
#include <absl/log/log_entry.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <absl/log/log_streamer.h>
#include <absl/log/structured.h>
#include <absl/log/vlog_is_on.h>

export module mcpplibs.mwrap.abseil.log;

export namespace absl {
// types (4)
using ::absl::LogEntry;
using ::absl::LogSink;
using ::absl::LogStreamer;
using ::absl::ScopedStderrThreshold;
// functions and operators (21)
using ::absl::AddLogSink;
using ::absl::ClearLogBacktraceLocation;
using ::absl::EnableLogPrefix;
using ::absl::FlushLogSinks;
using ::absl::InitializeLog;
using ::absl::LogAsLiteral;
using ::absl::LogDebugFatalStreamer;
using ::absl::LogErrorStreamer;
using ::absl::LogFatalStreamer;
using ::absl::LogInfoStreamer;
using ::absl::LogWarningStreamer;
using ::absl::MinLogLevel;
using ::absl::RemoveLogSink;
using ::absl::SetAndroidNativeTag;
using ::absl::SetGlobalVLogLevel;
using ::absl::SetLogBacktraceLocation;
using ::absl::SetMinLogLevel;
using ::absl::SetStderrThreshold;
using ::absl::SetVLogLevel;
using ::absl::ShouldPrependLogPrefix;
using ::absl::StderrThreshold;
}  // namespace absl

export namespace absl::log_internal {
// operators of public types declared in an implementation namespace, for argument-dependent lookup (1)
using ::absl::log_internal::operator<<;
}  // namespace absl::log_internal

export namespace absl::log_internal::detect_specialization {
// operators of public types declared in an implementation namespace, for argument-dependent lookup (1)
using ::absl::log_internal::detect_specialization::operator<<;
}  // namespace absl::log_internal::detect_specialization
