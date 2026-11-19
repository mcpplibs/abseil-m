// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.random — the names of <absl/random/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/random/bernoulli_distribution.h>
#include <absl/random/beta_distribution.h>
#include <absl/random/bit_gen_ref.h>
#include <absl/random/discrete_distribution.h>
#include <absl/random/distributions.h>
#include <absl/random/exponential_distribution.h>
#include <absl/random/gaussian_distribution.h>
#include <absl/random/log_uniform_int_distribution.h>
#include <absl/random/poisson_distribution.h>
#include <absl/random/random.h>
#include <absl/random/seed_gen_exception.h>
#include <absl/random/seed_sequences.h>
#include <absl/random/uniform_int_distribution.h>
#include <absl/random/uniform_real_distribution.h>
#include <absl/random/zipf_distribution.h>

export module mcpplibs.mwrap.abseil.random;

export namespace absl {
// types (19)
using ::absl::BitGen;
using ::absl::BitGenRef;
using ::absl::InsecureBitGen;
using ::absl::IntervalClosedClosedTag;
using ::absl::IntervalClosedOpenTag;
using ::absl::IntervalOpenClosedTag;
using ::absl::IntervalOpenOpenTag;
using ::absl::SeedGenException;
using ::absl::SeedSeq;
using ::absl::bernoulli_distribution;
using ::absl::beta_distribution;
using ::absl::discrete_distribution;
using ::absl::exponential_distribution;
using ::absl::gaussian_distribution;
using ::absl::log_uniform_int_distribution;
using ::absl::poisson_distribution;
using ::absl::uniform_int_distribution;
using ::absl::uniform_real_distribution;
using ::absl::zipf_distribution;
// objects (6)
using ::absl::IntervalClosed;
using ::absl::IntervalClosedClosed;
using ::absl::IntervalClosedOpen;
using ::absl::IntervalOpen;
using ::absl::IntervalOpenClosed;
using ::absl::IntervalOpenOpen;
// functions and operators (12)
using ::absl::Bernoulli;
using ::absl::Beta;
using ::absl::CreateSeedSeqFrom;
using ::absl::Exponential;
using ::absl::Gaussian;
using ::absl::LogUniform;
using ::absl::MakeSeedSeq;
using ::absl::Poisson;
using ::absl::Uniform;
using ::absl::Zipf;
using ::absl::operator<<;
using ::absl::operator>>;
}  // namespace absl

export namespace absl::random_internal {
// operators of public types declared in an implementation namespace, for argument-dependent lookup (2)
using ::absl::random_internal::operator!=;
using ::absl::random_internal::operator==;
}  // namespace absl::random_internal
