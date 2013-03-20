#include "XMLParser.hpp"

#include <boost/property_tree/xml_parser.hpp>

#include "coconut-tools/utils/pointee.hpp"

using namespace coconut_tools::configuration::parsers;

void XMLParser::doParse(std::istream& is, boost::property_tree::ptree* treePtr) const {
    boost::property_tree::ptree& tree = utils::pointee(treePtr);
    boost::property_tree::xml_parser::read_xml(is, tree);
}
