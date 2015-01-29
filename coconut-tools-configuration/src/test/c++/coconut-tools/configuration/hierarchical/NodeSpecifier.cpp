#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/configuration/hierarchical/NodeSpecifier.hpp"

using namespace coconut_tools::configuration::hierarchical;

BOOST_AUTO_TEST_SUITE(NodeSpecifierTestSuite);

BOOST_AUTO_TEST_CASE(EmptyStringYieldsEmptyNodeSpecifier) {
    NodeSpecifier nodeSpecifier("");
    BOOST_CHECK(nodeSpecifier.empty());
}

BOOST_AUTO_TEST_CASE(OperatorDivideAppendsNodeSpecifier) {
	auto nodeSpecifier = NodeSpecifier() / "a" / "b" / "c";
	BOOST_CHECK_EQUAL(nodeSpecifier.root(), "a");
	BOOST_CHECK_EQUAL(nodeSpecifier.childPath().root(), "b");
	BOOST_CHECK_EQUAL(nodeSpecifier.childPath().childPath().root(), "c");
}

BOOST_AUTO_TEST_SUITE_END(/* NodeSpecifierTestSuite */);
