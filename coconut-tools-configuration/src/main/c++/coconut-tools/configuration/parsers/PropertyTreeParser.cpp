#include "PropertyTreeParser.hpp"

#include <boost/bind.hpp>

using namespace coconut_tools::configuration::parsers;

namespace {

void addTreeNodes(
        boost::property_tree::ptree tree,
        PropertyTreeParser::NewChildCallback newChildCallback,
        PropertyTreeParser::ChildrenEndCallback childrenEndCallback
        ) {
    newChildCallback(tree.data());

    boost::property_tree::ptree::const_iterator it, end = tree.end();
    for (it = tree.begin(); it != end; ++it) {
        addTreeNodes(it->second, newChildCallback, childrenEndCallback);
    }

    childrenEndCallback();
}

} // anonymous namespace

void PropertyTreeParser::parse(std::istream& is, NewChildCallback newChildCallback,
        ChildrenEndCallback childrenEndCallback) const {
    boost::property_tree::ptree tree;

    doParse(is, &tree);

    addTreeNodes(tree, newChildCallback, childrenEndCallback);
}
