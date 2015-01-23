#include "HierarchicalConfigurationReader.hpp"

#include <fstream>
#include <stack>
#include <functional>

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

    HierarchicalConfigurationSharedPtr subtree;

    RootsEntry(const std::string& node, HierarchicalConfigurationSharedPtr subtree) :
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
    if (roots.empty()) {
        throw UnpairedParserBeginEnds();
    }
    roots.top().subtree->add(child.node, child.subtree);
}

} // anonymous namespace

void HierarchicalConfigurationReader::read(
        const parsers::HierarchicalParser& parser,
        std::istream& is,
        HierarchicalConfiguration* configurationPtr
        ) const {
    HierarchicalConfiguration& configuration = utils::pointee(configurationPtr);

    Roots roots;
    roots.push(RootsEntry(std::string(), configuration.shared_from_this()));

    parser.parse(
            is,
            std::bind(&newChild, &roots, std::placeholders::_1, std::placeholders::_2),
            std::bind(&childrenEnd, &roots)
            );

    if (roots.size() != 1) {
        throw UnpairedParserBeginEnds();
    }

    roots.pop();
}

void HierarchicalConfigurationReader::read(
        const parsers::HierarchicalParser& parser,
        const boost::filesystem::path& path,
        HierarchicalConfiguration* configurationPtr
        ) const {
    HierarchicalConfiguration& configuration = utils::pointee(configurationPtr);

    Roots roots;
    roots.push(RootsEntry(std::string(), configuration.shared_from_this()));

    parser.parse(
            path,
            std::bind(&newChild, &roots, std::placeholders::_1, std::placeholders::_2),
            std::bind(&childrenEnd, &roots)
            );

    if (roots.size() != 1) {
        throw UnpairedParserBeginEnds();
    }

    roots.pop();
}
