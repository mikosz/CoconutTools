#ifndef _COCONUT_TOOLS_SERIALISATION_JSONSERIALISER_HPP_
#define _COCONUT_TOOLS_SERIALISATION_JSONSERIALISER_HPP_

#include <iosfwd>

#include "Serialiser.hpp"

namespace coconut_tools {
namespace serialisation {

class JSONSerialiser : public Serialiser {
public:

	JSONSerialiser(std::ostream& os) : // TODO: needs to remain valid through lifetime of this object - enforce?
		os_(os)
	{
		os_.exceptions(std::ios::badbit | std::ios::failbit);
	}

protected:

	void writeObjectStart() override;

	void writeObjectEnd() override;

	void writeArrayStart(std::uint32_t elementCount) override;

	void writeArrayEnd() override;

	void writeLabel(const std::string& label) override;

	void write(bool b) override;

	void write(std::uint8_t i) override;

	void write(std::int8_t i) override;

	void write(std::uint16_t i) override;

	void write(std::int16_t i) override;

	void write(std::uint32_t i) override;

	void write(std::int32_t i) override;

	void write(std::uint64_t i) override;

	void write(std::int64_t i) override;

	void write(float f) override;

	void write(const std::string& s) override;

private:

	std::ostream& os_;

	bool newLinePending_ = false;

	size_t indentation_ = 0;

	bool commaPending_ = false;

	void flushComma();

	void indent();

};

} // namespace serialisation

using serialisation::JSONSerialiser;

} // namespace coconut_tools


#endif /* _COCONUT_TOOLS_SERIALISATION_JSONSERIALISER_HPP_ */
