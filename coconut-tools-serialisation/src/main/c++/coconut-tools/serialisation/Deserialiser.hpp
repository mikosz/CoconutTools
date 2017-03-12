#ifndef _COCONUT_TOOLS_SERIALISATION_DESERIALISER_HPP_
#define _COCONUT_TOOLS_SERIALISATION_DESERIALISER_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <type_traits>

namespace coconut_tools {
namespace serialisation {

class Deserialiser {
public:

	template <class T>
	using SerialiseArgument = T&;

	struct Label {

		std::string label;

		explicit Label(std::string label) :
			label(std::move(label))
		{
		}

	};

	virtual ~Deserialiser() = default;

	template <class T, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
	Deserialiser& operator>>(T& value) {
		read(value);
		return *this;
	}

	template <
		class T,
		std::enable_if_t<
			std::is_class<T>::value || std::is_enum<T>::value || std::is_union<T>::value
			>* = nullptr
		>
	Deserialiser& operator>>(T& value) {
		readObjectStart();
		serialise(*this, value);
		readObjectEnd();
		return *this;
	}

	// TODO: figure out how to do for all IsIterable
	template <class T>
	Deserialiser& operator>>(std::vector<T>& vector) {
		auto arrayElementsCount = readArrayStart();
		vector.reserve(arrayElementsCount);
		auto element = T();
		for (auto arrayElementsLeft = arrayElementsCount; arrayElementsLeft > 0; --arrayElementsLeft) {
			*this >> element;
			vector.emplace_back(std::move(element));
		}
		readArrayEnd();
		return *this;
	}

	template <>
	Deserialiser& operator>>(const Label& label) {
		readLabel(std::move(label.label));
		return *this;
	}

	template <>
	Deserialiser& operator >> (Label& label) {
		readLabel(std::move(label.label));
		return *this;
	}

	template <>
	Deserialiser& operator>>(std::string& s) {
		read(s);
		return *this;
	}

	template <class T>
	Deserialiser& operator()(T& value) {
		*this >> value;
		return *this;
	}

	template <class T>
	Deserialiser& operator()(const Label& label, T& value) {
		*this >> label >> value;
		return *this;
	}

protected:

	Deserialiser() = default;

	virtual void readObjectStart() = 0;

	virtual void readObjectEnd() = 0;

	virtual std::uint32_t readArrayStart() = 0;

	virtual void readArrayEnd() = 0;

	virtual void readLabel(std::string label) = 0;

	virtual void read(bool& b) = 0;

	virtual void read(std::uint8_t& i) = 0;

	virtual void read(std::int8_t& i) = 0;

	virtual void read(std::uint16_t& i) = 0;

	virtual void read(std::int16_t& i) = 0;

	virtual void read(std::uint32_t& i) = 0;

	virtual void read(std::int32_t& i) = 0;

	virtual void read(std::uint64_t& i) = 0;

	virtual void read(std::int64_t& i) = 0;

	virtual void read(float& f) = 0;

	virtual void read(std::string& s) = 0; // TODO: avoid reading extra-long strings in error

private:

	Deserialiser(const Deserialiser&) = delete;

	void operator=(const Deserialiser&) = delete;

};

} // namespace serialisation

using serialisation::Deserialiser;

} // namespace coconut_tools


#endif /* _COCONUT_TOOLS_SERIALISATION_DESERIALISER_HPP_ */
