#ifndef COCONUTTOOLS_ENUMS_MASK_HPP_
#define COCONUTTOOLS_ENUMS_MASK_HPP_

#include <type_traits>
#include <iosfwd>
#include <bitset>

#include "flag.hpp"

namespace coconut_tools {
namespace enums {

template <class FlagType, class = std::enable_if_t<IsFlagV<FlagType>>>
class Mask {
public:

	using Flag = FlagType;

	constexpr Mask() noexcept :
		mask_(IntegralType(0))
	{
	}

	constexpr Mask(Flag flag) noexcept :
		mask_(static_cast<IntegralType>(flag))
	{
	}

	constexpr explicit operator bool() const noexcept {
		return mask_ != IntegralType(0);
	}

	friend constexpr bool operator ==(Mask lhs, Mask rhs) noexcept {
		return lhs.mask_ == rhs.mask_;
	}

	friend constexpr bool operator !=(Mask lhs, Mask rhs) noexcept {
		return lhs.mask_ != rhs.mask_;
	}

	friend constexpr Mask operator|(Mask lhs, Mask rhs) noexcept {
		return lhs.mask_ | rhs.mask_;
	}

	friend constexpr Mask operator&(Mask lhs, Mask rhs) noexcept {
		return lhs.mask_ & rhs.mask_;
	}

	friend constexpr Mask operator^(Mask lhs, Mask rhs) noexcept {
		return lhs.mask_ ^ rhs.mask_;
	}

	friend constexpr Mask operator~(Mask m) noexcept {
		return ~m.mask_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Mask& mask) {
		return os << std::bitset<8 * sizeof(IntegralType)>(mask.mask_);
	}

private:

	using IntegralType = std::underlying_type_t<Flag>;

	IntegralType mask_;

	constexpr Mask(IntegralType i) noexcept :
		mask_(i)
	{
	}

};

template <class FlagType, class = std::enable_if_t<IsFlagV<FlagType>>>
constexpr Mask<FlagType> operator|(FlagType lhs, FlagType rhs) noexcept {
	return Mask<FlagType>() | lhs | rhs;
}

template <class FlagType, class = std::enable_if_t<IsFlagV<FlagType>>>
constexpr Mask<FlagType> operator&(FlagType lhs, FlagType rhs) noexcept {
	return Mask<FlagType>(lhs) & rhs;
}

template <class FlagType, class = std::enable_if_t<IsFlagV<FlagType>>>
constexpr Mask<FlagType> operator^(FlagType lhs, FlagType rhs) noexcept {
	return Mask<FlagType>() ^ lhs ^ rhs;
}

} // namespace enums

using enums::Mask;

} // namespace coconut_tools

#endif /* COCONUTTOOLS_ENUMS_MASK_HPP_ */
