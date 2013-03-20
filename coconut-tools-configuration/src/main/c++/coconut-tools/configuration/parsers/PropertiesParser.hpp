#ifndef COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTIESPARSER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTIESPARSER_HPP_

#include "FlatParser.hpp"

namespace coconut_tools {
namespace configuration {
namespace parsers {

class PropertiesParser : public FlatParser {
public:

    using FlatParser::parse;

    void parse(std::istream& is, KeyValueCallback keyValueCallback) const;

};

}  // namespace parsers
}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTIESPARSER_HPP_ */
