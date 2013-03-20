#include "HierarchicalConfigurationReader.hpp"

#include <fstream>
#include <stack>

#include <boost/bind.hpp>

#include "coconut-tools/configuration/HierarchicalConfiguration.hpp"
#include "coconut-tools/utils/pointee.hpp"
#include "coconut-tools/exceptions/LogicError.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::readers;

namespace {

class UnpairedParserBeginEnds : exceptions::LogicError {
public:

    UnpairedParserBeginEnds() :
        exceptions::LogicError("Expected paired newChild/childrenEnd calls from parser") {
    }

};

typedef std::stack<HierarchicalConfigurationPtr> Roots;

void newChild(Roots* rootsPtr, const std::string& name) {
    Roots& roots = utils::pointee(rootsPtr);
    roots.push(HierarchicalConfiguration::create(name));
}

void childrenEnd(Roots* rootsPtr) {
    Roots& roots = utils::pointee(rootsPtr);
    HierarchicalConfigurationPtr child = roots.top();
    roots.pop();
    roots.top()->add(child->text(), child);
}

} // anonymous namespace

void HierarchicalConfigurationReader::read(
        const parsers::HierarchicalParser& parser,
        std::istream& is,
        HierarchicalConfiguration* configurationParam
        ) const {
    Roots roots;

    parser.parse(
            is,
            boost::bind(&newChild, &roots, _1),
            boost::bind(&childrenEnd, &roots)
            );

    if (!roots.empty()) {
        throw UnpairedParserBeginEnds();
    }
}

void HierarchicalConfigurationReader::read(
        const parsers::HierarchicalParser& parser,
        const boost::filesystem::path& path,
        HierarchicalConfiguration* configurationParam
        ) const {
    Roots roots;

    parser.parse(
            path,
            boost::bind(&newChild, &roots, _1),
            boost::bind(&childrenEnd, &roots)
            );

    if (!roots.empty()) {
        throw UnpairedParserBeginEnds();
    }
}
