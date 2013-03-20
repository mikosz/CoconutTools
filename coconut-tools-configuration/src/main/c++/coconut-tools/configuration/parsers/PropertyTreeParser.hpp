#ifndef COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTYTREEPARSER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTYTREEPARSER_HPP_

#include "HierarchicalParser.hpp"

#include <boost/property_tree/ptree.hpp>

namespace coconut_tools {
namespace configuration {
namespace parsers {

class PropertyTreeParser : public HierarchicalParser {
public:

	using HierarchicalParser::parse;

    void parse(std::istream& is, NewChildCallback newChildCallback, ChildrenEndCallback childrenEndCallback) const;

protected:

	virtual void doParse(std::istream& is, boost::property_tree::ptree* tree) const = 0;

};

} // namespace parsers
} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTYTREEPARSER_HPP_ */
