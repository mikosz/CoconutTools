#ifndef _COCONUT_TOOLS_SERIALISATION_BINARYDESERIALISER_HPP_
#define _COCONUT_TOOLS_SERIALISATION_BINARYDESERIALISER_HPP_

#include <iosfwd>

#include "Deserialiser.hpp"

namespace coconut_tools {
namespace serialisation {

class BinaryDeserialiser : public Deserialiser {
public:

	BinaryDeserialiser(std::istream& is); // TODO: needs to remain valid through lifetime of this object - enforce?

protected:

	void readObjectStart() override;

	void readObjectEnd() override;

	std::uint32_t readArrayStart() override;

	void readArrayEnd() override;

	void readLabel(std::string label) override;

	void read(bool& b) override;

	void read(std::uint8_t& i) override;

	void read(std::int8_t& i) override;

	void read(std::uint16_t& i) override;

	void read(std::int16_t& i) override;

	void read(std::uint32_t& i) override;

	void read(std::int32_t& i) override;

	void read(std::uint64_t& i) override;

	void read(std::int64_t& i) override;

	void read(float& f) override;

	void read(std::string& s) override;

private:

	std::istream& is_;

	bool changeEndianness_;

};

} // namespace serialisation

using serialisation::BinaryDeserialiser;

} // namespace coconut_tools


#endif /* _COCONUT_TOOLS_SERIALISATION_BINARYDESERIALISER_HPP_ */
