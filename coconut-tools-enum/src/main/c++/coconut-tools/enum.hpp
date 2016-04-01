#ifndef COCONUTTOOLS_ENUM_HPP_
#define COCONUTTOOLS_ENUM_HPP_

#include <boost/preprocessor.hpp>

#include <unordered_map>

/**
 * Usage example:
 *
 * CCN_ENUM(
 *     Shape,
 *     (TRIANGLE)
 *     (SQUARE)
 *     (HEXAGON)
 * )
 *
 * Creates an enum class with TRIANGLE, SQUARE and HEXAGON with specified values and two functions:
 * * const std::string& toString(Shape)
 * * void fromString(Shape&, const std::string&)
 */

#define CCN_ENUM_value(r, data, value) \
	value BOOST_PP_COMMA()

#define CCN_ENUM_valueName(r, data, value) \
	{ data ## ::value BOOST_PP_COMMA() BOOST_PP_STRINGIZE(value) } BOOST_PP_COMMA()

#define CCN_ENUM_nameValue(r, data, value) \
	{ BOOST_PP_STRINGIZE(value) BOOST_PP_COMMA() data ## ::value } BOOST_PP_COMMA()

#define CCN_ENUM(EnumName, values) \
	enum class EnumName { \
		BOOST_PP_SEQ_FOR_EACH(CCN_ENUM_value, 0, values) \
	}; \
	\
	\
	inline const std::string& toString(EnumName value) { \
		/* TODO: this builds on visual c++, but is probably invalid C++ (no hash function for enum class) */ \
		static const std::unordered_map<EnumName, std::string> EnumName ## _NAMES = { \
			BOOST_PP_SEQ_FOR_EACH(CCN_ENUM_valueName, EnumName, values) \
			}; \
		return EnumName ## _NAMES.at(value); \
	} \
	\
	void fromString(EnumName& value, const std::string& name) { \
		static const std::unordered_map<std::string, EnumName> NAMES_TO_ ## EnumName = { \
			BOOST_PP_SEQ_FOR_EACH(CCN_ENUM_nameValue, EnumName, values) \
			}; \
		value = NAMES_TO_ ## EnumName.at(name); \
	}

#endif /* COCONUTTOOLS_ENUM_HPP_ */
