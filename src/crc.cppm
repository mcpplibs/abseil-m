// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.crc — the names of <absl/crc/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/crc/crc32c.h>

export module mcpplibs.mwrap.abseil.crc;

export namespace absl {
// types (1)
using ::absl::crc32c_t;
// functions and operators (8)
using ::absl::ComputeCrc32c;
using ::absl::ConcatCrc32c;
using ::absl::ExtendCrc32c;
using ::absl::ExtendCrc32cByZeroes;
using ::absl::MemcpyCrc32c;
using ::absl::RemoveCrc32cPrefix;
using ::absl::RemoveCrc32cSuffix;
using ::absl::operator<<;
}  // namespace absl
