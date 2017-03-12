#ifndef _COCONUT_TOOLS_SERIALISATION_COMMONSERIALISERS_HPP_
#define _COCONUT_TOOLS_SERIALISATION_COMMONSERIALISERS_HPP_

#include <algorithm>
#include <iterator>
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

// --- containers

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
