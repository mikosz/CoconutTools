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

struct RootsEntry {

    std::string node;

    HierarchicalConfigurationPtr subtree;

    RootsEntry(const std::string& node, HierarchicalConfigurationPtr subtree) :
        node(node),
        subtree(subtree)
    {
    }

};

typedef std::stack<RootsEntry> Roots;

void newChild(Roots* rootsPtr, const std::string& node, const std::string& text) {
    Roots& roots = utils::pointee(rootsPtr);
    roots.push(RootsEntry(node, HierarchicalConfiguration::create(text)));
}

void childrenEnd(Roots* rootsPtr) {
    Roots& roots = utils::pointee(rootsPtr);
    RootsEntry child = roots.top();
    roots.pop();
    roots.top().subtree->add(child.node, child.subtree);
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
            boost::bind(&newChild, &roots, _1, _2),
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
            boost::bind(&newChild, &roots, _1, _2),
            boost::bind(&childrenEnd, &roots)
            );

    if (!roots.empty()) {
        throw UnpairedParserBeginEnds();
    }
}
