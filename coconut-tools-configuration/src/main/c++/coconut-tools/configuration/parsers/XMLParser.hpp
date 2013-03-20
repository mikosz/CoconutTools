#ifndef COCONUT_TOOLS_CONFIGURATION_PARSERS_XMLPARSER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_PARSERS_XMLPARSER_HPP_

#include "PropertyTreeParser.hpp"

namespace coconut_tools {
namespace configuration {
namespace parsers {

class XMLParser : public PropertyTreeParser {
protected:

    void doParse(std::istream& is, boost::property_tree::ptree* tree) const;

};

} // namespace parsers
} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_PARSERS_XMLPARSER_HPP_ */
