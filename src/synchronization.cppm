// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.synchronization — the names of <absl/synchronization/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/synchronization/barrier.h>
#include <absl/synchronization/blocking_counter.h>
#include <absl/synchronization/mutex.h>
#include <absl/synchronization/notification.h>

export module mcpplibs.mwrap.abseil.synchronization;

export namespace absl {
// types (13)
using ::absl::Barrier;
using ::absl::BlockingCounter;
using ::absl::CondVar;
using ::absl::Condition;
using ::absl::Mutex;
using ::absl::MutexLock;
using ::absl::MutexLockMaybe;
using ::absl::Notification;
using ::absl::OnDeadlockCycle;
using ::absl::ReaderMutexLock;
using ::absl::ReleasableMutexLock;
using ::absl::SynchWaitParams;
using ::absl::WriterMutexLock;
// functions and operators (5)
using ::absl::EnableMutexInvariantDebugging;
using ::absl::RegisterCondVarTracer;
using ::absl::RegisterMutexProfiler;
using ::absl::RegisterMutexTracer;
using ::absl::SetMutexDeadlockDetectionMode;
}  // namespace absl
