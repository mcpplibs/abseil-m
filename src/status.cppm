// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.status — the names of <absl/status/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/status/status.h>
#include <absl/status/status_payload_printer.h>
#include <absl/status/statusor.h>

export module mcpplibs.mwrap.abseil.status;

export namespace absl {
// types (5)
using ::absl::BadStatusOrAccess;
using ::absl::Status;
using ::absl::StatusCode;
using ::absl::StatusOr;
using ::absl::StatusToStringMode;
// functions and operators (49)
using ::absl::AbortedError;
using ::absl::AbslStringify;
using ::absl::AlreadyExistsError;
using ::absl::CancelledError;
using ::absl::DataLossError;
using ::absl::DeadlineExceededError;
using ::absl::ErrnoToStatus;
using ::absl::ErrnoToStatusCode;
using ::absl::FailedPreconditionError;
using ::absl::InternalError;
using ::absl::InvalidArgumentError;
using ::absl::IsAborted;
using ::absl::IsAlreadyExists;
using ::absl::IsCancelled;
using ::absl::IsDataLoss;
using ::absl::IsDeadlineExceeded;
using ::absl::IsFailedPrecondition;
using ::absl::IsInternal;
using ::absl::IsInvalidArgument;
using ::absl::IsNotFound;
using ::absl::IsOutOfRange;
using ::absl::IsPermissionDenied;
using ::absl::IsResourceExhausted;
using ::absl::IsUnauthenticated;
using ::absl::IsUnavailable;
using ::absl::IsUnimplemented;
using ::absl::IsUnknown;
using ::absl::NotFoundError;
using ::absl::OkStatus;
using ::absl::OutOfRangeError;
using ::absl::PermissionDeniedError;
using ::absl::ResourceExhaustedError;
using ::absl::StatusCodeToString;
using ::absl::StatusMessageAsCStr;
using ::absl::UnauthenticatedError;
using ::absl::UnavailableError;
using ::absl::UnimplementedError;
using ::absl::UnknownError;
using ::absl::operator!=;
using ::absl::operator&;
using ::absl::operator&=;
using ::absl::operator<<;
using ::absl::operator==;
using ::absl::operator^;
using ::absl::operator^=;
using ::absl::operator|;
using ::absl::operator|=;
using ::absl::operator~;
using ::absl::swap;
}  // namespace absl
