#ifndef _COCONUT_TOOLS_SERIALISATION_JSONDESERIALISER_HPP_
#define _COCONUT_TOOLS_SERIALISATION_JSONDESERIALISER_HPP_

#include <iosfwd>
#include <stack>
#include <memory>

#include <boost/property_tree/ptree.hpp>

#include "Deserialiser.hpp"

namespace coconut_tools {
namespace serialisation {

class JSONDeserialiser : public Deserialiser {
public:

	JSONDeserialiser(std::istream& is); // TODO: needs to remain valid through lifetime of this object - enforce?

	~JSONDeserialiser();

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

	class PropertyTreeNode;

	class ValueNode;

	class ArrayNode;

	std::istream& is_;

	boost::property_tree::ptree propertyTree_;

	std::stack<std::unique_ptr<PropertyTreeNode>> path_;

	std::unique_ptr<PropertyTreeNode> currentNode_;

	template <class T>
	void readValue(T& v);

};

} // namespace serialisation

using serialisation::JSONDeserialiser;

} // namespace coconut_tools


#endif /* _COCONUT_TOOLS_SERIALISATION_JSONDESERIALISER_HPP_ */
