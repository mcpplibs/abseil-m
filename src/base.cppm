// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.base — the names of <absl/base/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/base/attributes.h>
#include <absl/base/call_once.h>
#include <absl/base/casts.h>
#include <absl/base/config.h>
#include <absl/base/const_init.h>
#include <absl/base/dynamic_annotations.h>
#include <absl/base/fast_type_id.h>
#include <absl/base/log_severity.h>
#include <absl/base/macros.h>
#include <absl/base/no_destructor.h>
#include <absl/base/nullability.h>
#include <absl/base/optimization.h>
#include <absl/base/options.h>
#include <absl/base/policy_checks.h>
#include <absl/base/port.h>
#include <absl/base/prefetch.h>
#include <absl/base/thread_annotations.h>

export module mcpplibs.mwrap.abseil.base;

export namespace absl {
// types (10)
using ::absl::ConstInitType;
using ::absl::FastTypeIdType;
using ::absl::LogSeverity;
using ::absl::LogSeverityAtLeast;
using ::absl::LogSeverityAtMost;
using ::absl::NoDestructor;
using ::absl::Nonnull;
using ::absl::NullabilityUnknown;
using ::absl::Nullable;
using ::absl::once_flag;
// enumerators of unscoped enumerations (1)
using ::absl::kConstInit;
// functions and operators (15)
using ::absl::FastTypeId;
using ::absl::HwasanTagPointer;
using ::absl::LogSeverities;
using ::absl::LogSeverityName;
using ::absl::NormalizeLogSeverity;
using ::absl::PrefetchToLocalCache;
using ::absl::PrefetchToLocalCacheForWrite;
using ::absl::PrefetchToLocalCacheNta;
using ::absl::call_once;
using ::absl::implicit_cast;
using ::absl::operator<;
using ::absl::operator<<;
using ::absl::operator<=;
using ::absl::operator>;
using ::absl::operator>=;
// standard library names Abseil re-declares as its own (1)
using ::absl::bit_cast;
}  // namespace absl
