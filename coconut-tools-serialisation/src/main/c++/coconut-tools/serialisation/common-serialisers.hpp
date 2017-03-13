#ifndef _COCONUT_TOOLS_SERIALISATION_COMMONSERIALISERS_HPP_
#define _COCONUT_TOOLS_SERIALISATION_COMMONSERIALISERS_HPP_

#include <algorithm>
#include <iterator>
#include <tuple>
#include <unordered_map>

#include "Deserialiser.hpp"
#include "Serialiser.hpp"

namespace coconut_tools {
namespace serialisation {

// --- enums

template <class EnumType>
inline void serialise(
	Deserialiser& deserialiser,
	EnumType& enumValue,
	std::enable_if_t<std::is_enum<EnumType>::value>* = nullptr
	)
{
	std::string name;
	deserialiser >> name;
	fromString(enumValue, name);
}


template <class EnumType>
inline void serialise(
	Serialiser& serialiser,
	EnumType enumValue,
	std::enable_if_t<std::is_enum<EnumType>::value>* = nullptr
	)
{
	serialiser << toString(enumValue);
}

// --- pair & tuple

// TODO: wanted to make SerialiserType a template paremeter, but then compilation fails...
template <class FirstType, class SecondType>
inline void serialise(
	Serialiser& serialiser,
	typename Serialiser::template SerialiseArgument<std::pair<FirstType, SecondType>> pair
	)
{
	serialiser(Serialiser::Label("first"), pair.first);
	serialiser(Serialiser::Label("second"), pair.second);
}

template <class FirstType, class SecondType>
inline void serialise(
	Deserialiser& serialiser,
	typename Deserialiser::template SerialiseArgument<std::pair<FirstType, SecondType>> pair
	)
{
	serialiser(Deserialiser::Label("first"), pair.first);
	serialiser(Deserialiser::Label("second"), pair.second);
}

namespace detail {

// TODO: see above
template <size_t ELEMENT, class... T>
inline std::enable_if_t<ELEMENT == sizeof...(T), void> serialise(
	Serialiser& serialiser,
	typename Serialiser::template SerialiseArgument<std::tuple<T...>> tuple
	)
{
}

template <size_t ELEMENT, class... T>
inline std::enable_if_t<ELEMENT < sizeof...(T), void> serialise(
	Serialiser& serialiser,
	typename Serialiser::template SerialiseArgument<std::tuple<T...>> tuple
	)
{
	serialiser(Serialiser::Label("element-" + std::to_string(ELEMENT)), std::get<ELEMENT>(tuple));
	serialise<ELEMENT + 1, T...>(serialiser, tuple);
}

template <size_t ELEMENT, class... T>
inline std::enable_if_t<ELEMENT == sizeof...(T), void> serialise(
	Deserialiser& deserialiser,
	typename Deserialiser::template SerialiseArgument<std::tuple<T...>> tuple
	)
{
}

template <size_t ELEMENT, class... T>
inline std::enable_if_t<ELEMENT < sizeof...(T), void> serialise(
	Deserialiser& deserialiser,
	typename Deserialiser::template SerialiseArgument<std::tuple<T...>> tuple
	)
{
	deserialiser(Deserialiser::Label("element-" + std::to_string(ELEMENT)), std::get<ELEMENT>(tuple));
	serialise<ELEMENT + 1, T...>(deserialiser, tuple);
}

} // namespace detail

template <class... T>
inline void serialise(
	Serialiser& serialiser,
	typename Serialiser::template SerialiseArgument<std::tuple<T...>> tuple
	)
{
	detail::serialise<0, T...>(serialiser, tuple);
}

template <class... T>
inline void serialise(
	Deserialiser& deserialiser,
	typename Deserialiser::template SerialiseArgument<std::tuple<T...>> tuple
	)
{
	detail::serialise<0, T...>(deserialiser, tuple);
}

// --- containers

template <class Key, class Value>
inline void serialise(Deserialiser& deserialiser, std::unordered_map<Key, Value>& map) {
	auto entries = std::vector<std::pair<Key, Value>>();
	deserialiser >> entries;
	std::move(entries.begin(), entries.end(), std::inserter(map, map.end()));
}

template <class Key, class Value>
inline void serialise(Serialiser& serialiser, const std::unordered_map<Key, Value>& map) {
	auto entries = std::vector<std::pair<Key, Value>>(map.begin(), map.end());
	serialiser << entries;
}

} // namespace serialisation
} // namespace coconut_tools

#endif /* _COCONUT_TOOLS_SERIALISATION_COMMONSERIALISERS_HPP_ */
