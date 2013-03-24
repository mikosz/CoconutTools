#include "PropertyTreeParser.hpp"

#include <boost/bind.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace coconut_tools::configuration::parsers;

namespace {

void addTreeNodes(
        const std::string& node,
        boost::property_tree::ptree tree,
        PropertyTreeParser::NewChildCallback newChildCallback,
        PropertyTreeParser::ChildrenEndCallback childrenEndCallback
        ) {
    if (!node.empty()) {
        std::string trimmedData = boost::trim_copy(tree.data());
        newChildCallback(node, trimmedData);
    }

    boost::property_tree::ptree::const_iterator it, end = tree.end();
    for (it = tree.begin(); it != end; ++it) {
        addTreeNodes(it->first, it->second, newChildCallback, childrenEndCallback);
    }

    if (!node.empty()) {
        childrenEndCallback();
    }
}

} // anonymous namespace

void PropertyTreeParser::parse(std::istream& is, NewChildCallback newChildCallback,
        ChildrenEndCallback childrenEndCallback) const {
    boost::property_tree::ptree tree;

    doParse(is, &tree);

    addTreeNodes(std::string(), tree, newChildCallback, childrenEndCallback);
}
