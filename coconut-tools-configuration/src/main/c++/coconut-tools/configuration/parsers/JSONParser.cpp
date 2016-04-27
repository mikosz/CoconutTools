#include "JSONParser.hpp"

#include "coconut-tools/system/platform.hpp"

#if defined(CT_COMPILER_VISUAL_CXX)
#	pragma warning(push)
#	pragma warning(disable: 4715) // boost json_parser emits "not all control paths return a value"
#endif /* CT_COMPILER_VISUAL_CXX */

#include <boost/property_tree/json_parser.hpp>

#if defined(CT_COMPILER_VISUAL_CXX)
#	pragma warning(pop)
#endif /* CT_COMPILER_VISUAL_CXX */

#include "coconut-tools/utils/pointee.hpp"

using namespace coconut_tools::configuration::parsers;

void JSONParser::doParse(std::istream& is, boost::property_tree::ptree* treePtr) const {
	boost::property_tree::ptree& tree = utils::pointee(treePtr);
	boost::property_tree::json_parser::read_json(is, tree);
}
