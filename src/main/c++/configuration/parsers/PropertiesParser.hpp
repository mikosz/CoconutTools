#ifndef COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTIESPARSER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTIESPARSER_HPP_

#include "SimpleParser.hpp"

namespace coconut_tools {
namespace configuration {
namespace parsers {

class PropertiesParser : public SimpleParser {
public:

    using SimpleParser::parse;

    void parse(std::istream& is, KeyValueCallback keyValueCallback) const;

};

}  // namespace parsers
}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTIESPARSER_HPP_ */
