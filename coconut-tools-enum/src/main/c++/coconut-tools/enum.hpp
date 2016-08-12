#ifndef COCONUTTOOLS_ENUM_HPP_
#define COCONUTTOOLS_ENUM_HPP_

#include <boost/preprocessor.hpp>

#include <ostream>
#include <string>
#include <unordered_map>

/**
 * Usage example with incremental values starting at 0:
 *
 * CCN_ENUM(
 *     Colour,
 *     (BLACK)
 *     (RED)
 *     (BLUE)
 * )
 *
 * with custom values:
 *
 * CCN_ENUM_VALUES(
 *     Shape,
 *     (TRIANGLE)(3)
 *     (SQUARE)(4)
 * )
 *
 * Creates an enum class with TRIANGLE, SQUARE and HEXAGON with specified values and two functions:
 * * const std::string& toString(Shape)
 * * void fromString(Shape&, const std::string&)
 */

#define CCN_ENUM_is_column_left(i) \
	BOOST_PP_EQUAL(BOOST_PP_MOD(i, 2), 0)

#define CCN_ENUM_qualifiedValue(r, data, value) \
	data ## ::value BOOST_PP_COMMA()

#define CCN_ENUM_qualifiedValue_i(r, data, i, value) \
	BOOST_PP_IF( \
		CCN_ENUM_is_column_left(i), \
		CCN_ENUM_qualifiedValue, \
		BOOST_PP_TUPLE_EAT(3) \
		)(r, data, value)

#define CCN_ENUM_value(r, data, value) \
	value BOOST_PP_COMMA()

#define CCN_ENUM_valueName(r, data, value) \
	{ data ## ::value BOOST_PP_COMMA() BOOST_PP_STRINGIZE(value) } BOOST_PP_COMMA()

#define CCN_ENUM_nameValue(r, data, value) \
	{ BOOST_PP_STRINGIZE(value) BOOST_PP_COMMA() data ## ::value } BOOST_PP_COMMA()

#define CCN_ENUM_eq(value) \
	BOOST_PP_CAT(= value, BOOST_PP_COMMA())

#define CCN_ENUM_valueName_incrementing(EnumName, values) \
	BOOST_PP_SEQ_FOR_EACH(CCN_ENUM_valueName, EnumName, values)

#define CCN_ENUM_valueName_provided_i(r, data, i, value) \
	BOOST_PP_IF( \
		CCN_ENUM_is_column_left(i), \
		CCN_ENUM_valueName, \
		BOOST_PP_TUPLE_EAT(3) \
		)(r, data, value)

#define CCN_ENUM_valueName_provided(EnumName, values) \
	BOOST_PP_SEQ_FOR_EACH_I(CCN_ENUM_valueName_provided_i, EnumName, values)

#define CCN_ENUM_nameValue_incrementing(EnumName, values) \
	BOOST_PP_SEQ_FOR_EACH(CCN_ENUM_nameValue, EnumName, values)

#define CCN_ENUM_nameValue_provided_i(r, data, i, value) \
	BOOST_PP_IF( \
		CCN_ENUM_is_column_left(i), \
		CCN_ENUM_nameValue, \
		BOOST_PP_TUPLE_EAT(3) \
		)(r, data, value)

#define CCN_ENUM_nameValue_provided(EnumName, values) \
	BOOST_PP_SEQ_FOR_EACH_I(CCN_ENUM_nameValue_provided_i, EnumName, values)

#define CCN_ENUM_value_eq(r, data, i, value) \
	BOOST_PP_IF( \
		CCN_ENUM_is_column_left(i), \
		value BOOST_PP_TUPLE_EAT(1), \
		CCN_ENUM_eq \
		)(value)

#define CCN_ENUM_qualifiedValues_incrementing(EnumName, values) \
	BOOST_PP_SEQ_FOR_EACH(CCN_ENUM_qualifiedValue, EnumName, values)

#define CCN_ENUM_qualifiedValues_provided(EnumName, values) \
	BOOST_PP_SEQ_FOR_EACH_I(CCN_ENUM_qualifiedValue_i, EnumName, values)

#define CCN_ENUM_values(values) \
	BOOST_PP_SEQ_FOR_EACH(CCN_ENUM_value, 0, values)

#define CCN_ENUM_domain_incrementing(values) \
	BOOST_PP_SEQ_FOR_EACH(CCN_ENUM_value, 0, values)

#define CCN_ENUM_domain_provided(values) \
	BOOST_PP_SEQ_FOR_EACH_I(CCN_ENUM_value_eq, 0, values)

#define CCN_ENUM_definitions(EnumName, values, domainType, functionModifier) \
	enum class EnumName { \
		BOOST_PP_CAT(CCN_ENUM_domain_, domainType)(values) \
	}; \
	\
	using EnumName ## ValueList = std::vector<EnumName>; \
	\
	functionModifier const EnumName ## ValueList& all ## EnumName ## Values() { \
		static const EnumName ## ValueList VALUES = { \
			BOOST_PP_CAT(CCN_ENUM_qualifiedValues_, domainType)(EnumName, values) \
			}; \
		return VALUES; \
	} \
	\
	functionModifier const std::string& toString(EnumName value) { \
		/* TODO: this builds on visual c++, but is probably invalid C++ (no hash function for enum class) */ \
		static const std::unordered_map<EnumName, std::string> EnumName ## _NAMES = { \
			BOOST_PP_CAT(CCN_ENUM_valueName_, domainType)(EnumName, values) \
			}; \
		return EnumName ## _NAMES.at(value); \
	} \
	\
	functionModifier void fromString(EnumName& value, const std::string& name) { \
		static const std::unordered_map<std::string, EnumName> NAMES_TO_ ## EnumName = { \
			BOOST_PP_CAT(CCN_ENUM_nameValue_, domainType)(EnumName, values) \
			}; \
		/* TODO: this will throw out_of_range if name not found. return optional or throw custom exception */ \
		value = NAMES_TO_ ## EnumName.at(name); \
	} \
	\
	functionModifier std::ostream& operator<<(std::ostream& os, EnumName value) { \
		os << toString(value); \
		return os; \
	}

#define CCN_ENUM(EnumName, values) \
	CCN_ENUM_definitions(EnumName, values, incrementing, inline)

#define CCN_ENUM_VALUES(EnumName, values) \
	CCN_ENUM_definitions(EnumName, values, provided, inline)

#define CCN_MEMBER_ENUM(EnumName, values) \
	CCN_ENUM_definitions(EnumName, values, incrementing, friend)

#define CCN_MEMBER_ENUM_VALUES(EnumName, values) \
	CCN_ENUM_definitions(EnumName, values, provided, friend)

#endif /* COCONUTTOOLS_ENUM_HPP_ */
