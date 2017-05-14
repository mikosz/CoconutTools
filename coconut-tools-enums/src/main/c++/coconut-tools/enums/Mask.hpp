#ifndef COCONUTTOOLS_ENUMS_MASK_HPP_
#define COCONUTTOOLS_ENUMS_MASK_HPP_

#include <type_traits>

#include "flag.hpp"

namespace coconut_tools {
namespace enums {

template <class F, class = std::enable_if_t<IsFlagV<F>>>
class Mask {
public:

	constexpr Mask(F flag) noexcept :
		mask_(static_cast<IntegralType>(flag))
	{
	}

	constexpr explicit operator bool() const noexcept {
		return mask_ != IntegralType(0);
	}

	friend constexpr Mask operator|(Mask lhs, Mask rhs) noexcept {
		return lhs.mask_ | rhs.mask_;
	}

	friend constexpr Mask operator&(Mask lhs, Mask rhs) noexcept {
		return lhs.mask_ & rhs.mask_;
	}

private:

	using IntegralType = std::underlying_type_t<F>;

	IntegralType mask_;

	constexpr Mask(IntegralType i) noexcept :
		mask_(i)
	{
	}

};

} // namespace enums

using enums::Mask;

} // namespace coconut_tools

#endif /* COCONUTTOOLS_ENUMS_MASK_HPP_ */
