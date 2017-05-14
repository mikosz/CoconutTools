#ifndef COCONUTTOOLS_ENUM_FLAG_HPP_
#define COCONUTTOOLS_ENUM_FLAG_HPP_

#include "enum.hpp"

/**
 * Usage example:
 *
 * CT_FLAG(
 *     Access,
 *     (READ)
 *     (WRITE)
 * )
 *
 * or
 *
 * CT_FLAG_VALUES(
 *     Access,
 *     (READ)(1 << 0)
 *     (WRITE)(1 << 1)
 * )
 *
 * Creates an enum class with READ and WRITE values set to 1 << 0 and 1 << 1 and functions:
 * * std::unordered_set<Access> allAccessValues()
 * * const std::string& toString(Access)
 * * void fromString(Access&, const std::string&)
 * * void fromIntegral(Access&, const std::string&)
 * * std::ostream& operator<<(std::ostream&, const Access&)
 * 
 * IsFlag<Access>::value and IsFlagV<Access> are constant expressions equalling true.
 *
 * Also provided are CT_MEMBER_FLAG and CT_MEMBER_FLAG_VALUES variants which are usable as class
 * member types.
 *
 * NOTE: there is no verification done in CT_FLAG_VALUES or CT_MEMBER_FLAG_VALUES checking
 * that the values provided are correct flag values.
 */

#include "enum.hpp"

namespace detail {

template <class T>
constexpr bool isFlag(const T&) noexcept {
	return false;
}

} // namespace detail

template <class T>
struct IsFlag {
private:

	template <class U>
	static constexpr bool checkIsFlag(std::enable_if_t<std::is_enum_v<U>>* = nullptr) noexcept {
		using detail::isFlag;
		return isFlag(static_cast<T>(0));
	}

	template <class U>
	static constexpr bool checkIsFlag(std::enable_if_t<!std::is_enum_v<U>>* = nullptr) noexcept {
		return false;
	}

public:

	static constexpr auto value = checkIsFlag<T>();

};

template <class T>
constexpr auto IsFlagV = IsFlag<T>::value;

#define CT_FLAG_value_incrementing(r, data, i, value) \
	(value)(1 << i)

#define CT_FLAG_value_provided(r, data, value) \
	(value)

#define CT_FLAG_domain_incrementing(values) \
	BOOST_PP_SEQ_FOR_EACH_I(CT_FLAG_value_incrementing, 0, values)

#define CT_FLAG_domain_provided(values) \
	BOOST_PP_SEQ_FOR_EACH(CT_FLAG_value_provided, 0, values)

#define CT_FLAG_definitions(EnumName, ccnEnumBase, values, domainType, localFunctionModifier) \
	BOOST_PP_CAT(ccnEnumBase, _VALUES)(EnumName, \
		BOOST_PP_CAT(CT_FLAG_domain_, domainType)(values) \
	) \
	\
	localFunctionModifier constexpr bool isFlag(EnumName) noexcept { \
		return true; \
	};

#define CT_FLAG(EnumName, values) \
	CT_FLAG_definitions(EnumName, CT_ENUM, values, incrementing, inline)

#define CT_FLAG_VALUES(EnumName, values) \
	CT_FLAG_definitions(EnumName, CT_ENUM, values, provided, inline)

#define CT_MEMBER_FLAG(EnumName, values) \
	CT_FLAG_definitions(EnumName, CT_MEMBER_ENUM, values, incrementing, friend)

#define CT_MEMBER_FLAG_VALUES(EnumName, values) \
	CT_FLAG_definitions(EnumName, CT_MEMBER_ENUM, values, provided, friend)

#endif /* COCONUTTOOLS_FLAG_FLAG_HPP_ */
