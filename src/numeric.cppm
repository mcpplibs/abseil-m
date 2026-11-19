// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.numeric — the names of <absl/numeric/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/numeric/bits.h>
#include <absl/numeric/int128.h>

export module mcpplibs.mwrap.abseil.numeric;

export namespace absl {
// types (2)
using ::absl::int128;
using ::absl::uint128;
// functions and operators (37)
using ::absl::Int128High64;
using ::absl::Int128Low64;
using ::absl::Int128Max;
using ::absl::Int128Min;
using ::absl::MakeInt128;
using ::absl::MakeUint128;
using ::absl::Uint128High64;
using ::absl::Uint128Low64;
using ::absl::Uint128Max;
using ::absl::gbswap_16;
using ::absl::gbswap_32;
using ::absl::gbswap_64;
using ::absl::ghtonl;
using ::absl::ghtonll;
using ::absl::ghtons;
using ::absl::gntohl;
using ::absl::gntohll;
using ::absl::gntohs;
using ::absl::operator!;
using ::absl::operator!=;
using ::absl::operator%;
using ::absl::operator&;
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
using ::absl::operator>>;
using ::absl::operator^;
using ::absl::operator|;
using ::absl::operator~;
// standard library names Abseil re-declares as its own (13)
using ::absl::bit_ceil;
using ::absl::bit_floor;
using ::absl::bit_width;
using ::absl::byteswap;
using ::absl::countl_one;
using ::absl::countl_zero;
using ::absl::countr_one;
using ::absl::countr_zero;
using ::absl::endian;
using ::absl::has_single_bit;
using ::absl::popcount;
using ::absl::rotl;
using ::absl::rotr;
}  // namespace absl

export namespace absl::big_endian {
// functions and operators (15)
using ::absl::big_endian::FromHost;
using ::absl::big_endian::FromHost16;
using ::absl::big_endian::FromHost32;
using ::absl::big_endian::FromHost64;
using ::absl::big_endian::IsLittleEndian;
using ::absl::big_endian::Load16;
using ::absl::big_endian::Load32;
using ::absl::big_endian::Load64;
using ::absl::big_endian::Store16;
using ::absl::big_endian::Store32;
using ::absl::big_endian::Store64;
using ::absl::big_endian::ToHost;
using ::absl::big_endian::ToHost16;
using ::absl::big_endian::ToHost32;
using ::absl::big_endian::ToHost64;
}  // namespace absl::big_endian

export namespace absl::little_endian {
// functions and operators (15)
using ::absl::little_endian::FromHost;
using ::absl::little_endian::FromHost16;
using ::absl::little_endian::FromHost32;
using ::absl::little_endian::FromHost64;
using ::absl::little_endian::IsLittleEndian;
using ::absl::little_endian::Load16;
using ::absl::little_endian::Load32;
using ::absl::little_endian::Load64;
using ::absl::little_endian::Store16;
using ::absl::little_endian::Store32;
using ::absl::little_endian::Store64;
using ::absl::little_endian::ToHost;
using ::absl::little_endian::ToHost16;
using ::absl::little_endian::ToHost32;
using ::absl::little_endian::ToHost64;
}  // namespace absl::little_endian
