#ifndef _COCONUT_TOOLS_SERIALISATION_SERIALISER_HPP_
#define _COCONUT_TOOLS_SERIALISATION_SERIALISER_HPP_

#include <string>
#include <vector>
#include <cstddef>
#include <type_traits>

// TODO: document, support versioning

namespace coconut_tools {
namespace serialisation {

class Serialiser {
public:

	template <class T>
	using SerialiseArgument = const T&;

	struct Label {

		std::string label;

		Label(const std::string& label) :
			label(label)
		{
		}

		Label(std::string&& label) :
			label(std::move(label))
		{
		}

	};

	virtual ~Serialiser() = default;

	template <class T, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
	Serialiser& operator<<(const T& value) {
		write(value);
		return *this;
	}

	template <
		class T,
		std::enable_if_t<std::is_class<T>::value || std::is_enum<T>::value || std::is_union<T>::value
		>* = nullptr>
	Serialiser& operator<<(const T& value) {
		writeObjectStart();
		serialise(*this, value);
		writeObjectEnd();
		return *this;
	}

	// TODO: customise for iterable?
	template <class T>
	Serialiser& operator<<(const std::vector<T>& vector) {
		// TODO: verify array not larger than max uint32_t
		writeArrayStart(static_cast<std::uint32_t>(vector.size()));
		for (const auto& element : vector) {
			*this << element;
		}
		writeArrayEnd();
		return *this;
	}

	template <>
	Serialiser& operator<<(const Label& label) {
		writeLabel(label.label);
		return *this;
	}

	Serialiser& operator<<(const char* s) {
		write(std::string(s));
		return *this;
	}

	template <>
	Serialiser& operator<<(const std::string& s) {
		write(s);
		return *this;
	}

	template <class T>
	Serialiser& operator()(const T& value) { // TODO: use call_traits param type
		*this << value;
		return *this;
	}

	template <class T>
	Serialiser& operator()(const Label& label, const T& value) { // TODO: use call_traits param type
		*this << label << value;
		return *this;
	}

protected:

	Serialiser() = default;

	virtual void writeObjectStart() = 0;

	virtual void writeObjectEnd() = 0;

	virtual void writeArrayStart(std::uint32_t elementCount) = 0;

	virtual void writeArrayEnd() = 0;

	virtual void writeLabel(const std::string& label) = 0;

	virtual void write(bool b) = 0;

	virtual void write(std::uint8_t i) = 0;

	virtual void write(std::int8_t i) = 0;

	virtual void write(std::uint16_t i) = 0;

	virtual void write(std::int16_t i) = 0;

	virtual void write(std::uint32_t i) = 0;

	virtual void write(std::int32_t i) = 0;

	virtual void write(std::uint64_t i) = 0;

	virtual void write(std::int64_t i) = 0;

	virtual void write(float f) = 0;

	virtual void write(const std::string& s) = 0;

private:

	Serialiser(const Serialiser&) = delete;

	void operator=(const Serialiser&) = delete;

};

template <class EnumType>
inline void serialise(serialisation::Serialiser& serialiser, EnumType enumValue, std::enable_if_t<std::is_enum<EnumType>::value>* = nullptr) {
	serialiser << toString(enumValue);
}

} // namespace serialisation
} // namespace coconut_tools


#endif /* _COCONUT_TOOLS_SERIALISATION_SERIALISER_HPP_ */
