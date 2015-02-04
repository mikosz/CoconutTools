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

BOOST_AUTO_TEST_CASE(DifferentValueSelectorsYieldUnequal) {
	auto lhs = (NodeSpecifier() / "name")["selector-1"];
	auto rhs = (NodeSpecifier() / "name")["selector-2"];

	BOOST_CHECK_NE(lhs, rhs);
}

BOOST_AUTO_TEST_CASE(DifferentTypeSelectorsYieldUnequal) {
	auto lhs = (NodeSpecifier() / "name")["selector"];
	auto rhs = (NodeSpecifier() / "name").is("selector");

	BOOST_CHECK_NE(lhs, rhs);
}

BOOST_AUTO_TEST_CASE(SameSelectorsYieldEqual) {
	auto lhs = (NodeSpecifier() / "name")[NodeSpecifier("subNode").is("selector")];
	auto rhs = (NodeSpecifier() / "name")[NodeSpecifier("subNode").is("selector")];

	BOOST_CHECK_EQUAL(lhs, rhs);
}

BOOST_AUTO_TEST_SUITE_END(/* NodeSpecifierTestSuite */);
