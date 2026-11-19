// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.time — the names of <absl/time/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/time/civil_time.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>

export module mcpplibs.mwrap.abseil.time;

export namespace absl {
// types (13)
using ::absl::CivilDay;
using ::absl::CivilHour;
using ::absl::CivilMinute;
using ::absl::CivilMonth;
using ::absl::CivilSecond;
using ::absl::CivilYear;
using ::absl::Duration;
using ::absl::Time;
using ::absl::TimeConversion;
using ::absl::TimeZone;
using ::absl::Weekday;
using ::absl::civil_diff_t;
using ::absl::civil_year_t;
// objects (4)
using ::absl::RFC1123_full;
using ::absl::RFC1123_no_wday;
using ::absl::RFC3339_full;
using ::absl::RFC3339_sec;
// functions and operators (105)
using ::absl::AbsDuration;
using ::absl::AbslParseFlag;
using ::absl::AbslStringify;
using ::absl::AbslUnparseFlag;
using ::absl::Ceil;
using ::absl::ConvertDateTime;
using ::absl::DurationFromTimespec;
using ::absl::DurationFromTimeval;
using ::absl::FDivDuration;
using ::absl::FixedTimeZone;
using ::absl::Floor;
using ::absl::FormatCivilTime;
using ::absl::FormatDuration;
using ::absl::FormatTime;
using ::absl::FromChrono;
using ::absl::FromCivil;
using ::absl::FromDateTime;
using ::absl::FromTM;
using ::absl::FromTimeT;
using ::absl::FromUDate;
using ::absl::FromUniversal;
using ::absl::FromUnixMicros;
using ::absl::FromUnixMillis;
using ::absl::FromUnixNanos;
using ::absl::FromUnixSeconds;
using ::absl::GetCurrentTimeNanos;
using ::absl::GetWeekday;
using ::absl::GetYearDay;
using ::absl::Hours;
using ::absl::IDivDuration;
using ::absl::InfiniteDuration;
using ::absl::InfiniteFuture;
using ::absl::InfinitePast;
using ::absl::LoadTimeZone;
using ::absl::LocalTimeZone;
using ::absl::Microseconds;
using ::absl::Milliseconds;
using ::absl::Minutes;
using ::absl::Nanoseconds;
using ::absl::NextWeekday;
using ::absl::Now;
using ::absl::ParseCivilTime;
using ::absl::ParseDuration;
using ::absl::ParseFlag;
using ::absl::ParseLenientCivilTime;
using ::absl::ParseTime;
using ::absl::PrevWeekday;
using ::absl::Seconds;
using ::absl::SleepFor;
using ::absl::TimeFromTimespec;
using ::absl::TimeFromTimeval;
using ::absl::ToChronoHours;
using ::absl::ToChronoMicroseconds;
using ::absl::ToChronoMilliseconds;
using ::absl::ToChronoMinutes;
using ::absl::ToChronoNanoseconds;
using ::absl::ToChronoSeconds;
using ::absl::ToChronoTime;
using ::absl::ToCivilDay;
using ::absl::ToCivilHour;
using ::absl::ToCivilMinute;
using ::absl::ToCivilMonth;
using ::absl::ToCivilSecond;
using ::absl::ToCivilYear;
using ::absl::ToDoubleHours;
using ::absl::ToDoubleMicroseconds;
using ::absl::ToDoubleMilliseconds;
using ::absl::ToDoubleMinutes;
using ::absl::ToDoubleNanoseconds;
using ::absl::ToDoubleSeconds;
using ::absl::ToInt64Hours;
using ::absl::ToInt64Microseconds;
using ::absl::ToInt64Milliseconds;
using ::absl::ToInt64Minutes;
using ::absl::ToInt64Nanoseconds;
using ::absl::ToInt64Seconds;
using ::absl::ToTM;
using ::absl::ToTimeT;
using ::absl::ToTimespec;
using ::absl::ToTimeval;
using ::absl::ToUDate;
using ::absl::ToUniversal;
using ::absl::ToUnixMicros;
using ::absl::ToUnixMillis;
using ::absl::ToUnixNanos;
using ::absl::ToUnixSeconds;
using ::absl::Trunc;
using ::absl::UTCTimeZone;
using ::absl::UniversalEpoch;
using ::absl::UnixEpoch;
using ::absl::UnparseFlag;
using ::absl::ZeroDuration;
using ::absl::operator!=;
using ::absl::operator%;
using ::absl::operator*;
using ::absl::operator+;
using ::absl::operator-;
using ::absl::operator/;
using ::absl::operator<;
using ::absl::operator<<;
using ::absl::operator<=;
using ::absl::operator<=>;
using ::absl::operator==;
using ::absl::operator>;
using ::absl::operator>=;
}  // namespace absl

export namespace absl::time_internal {
// operators of public types declared in an implementation namespace, for argument-dependent lookup (1)
using ::absl::time_internal::operator<<;
}  // namespace absl::time_internal

export namespace absl::time_internal::cctz::detail {
// operators of public types declared in an implementation namespace, for argument-dependent lookup (8)
using ::absl::time_internal::cctz::detail::operator!=;
using ::absl::time_internal::cctz::detail::operator-;
using ::absl::time_internal::cctz::detail::operator<;
using ::absl::time_internal::cctz::detail::operator<<;
using ::absl::time_internal::cctz::detail::operator<=;
using ::absl::time_internal::cctz::detail::operator==;
using ::absl::time_internal::cctz::detail::operator>;
using ::absl::time_internal::cctz::detail::operator>=;
}  // namespace absl::time_internal::cctz::detail
