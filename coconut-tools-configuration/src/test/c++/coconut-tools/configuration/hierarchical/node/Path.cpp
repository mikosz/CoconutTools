#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/configuration/hierarchical/node/Path.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;
using namespace coconut_tools::configuration::hierarchical::node;

BOOST_AUTO_TEST_SUITE(SpecifierTestSuite);

BOOST_AUTO_TEST_CASE(EmptyStringYieldsEmptySpecifier) {
    Specifier nodeSpecifier("");
    BOOST_CHECK(!nodeSpecifier.hasChildren());
	BOOST_CHECK(nodeSpecifier.string().empty());
}

BOOST_AUTO_TEST_CASE(OperatorDivideAppendsSpecifier) {
	auto nodeSpecifier = Specifier() / "a" / "b" / "c";
	BOOST_CHECK_EQUAL(nodeSpecifier.root(), "a");
	BOOST_CHECK_EQUAL(nodeSpecifier.childPath().root(), "b");
	BOOST_CHECK_EQUAL(nodeSpecifier.childPath().childPath().root(), "c");
}

BOOST_AUTO_TEST_CASE(DifferentValueSelectorsYieldUnequal) {
	auto lhs = (Specifier() / "name")["selector-1"];
	auto rhs = (Specifier() / "name")["selector-2"];

	BOOST_CHECK_NE(lhs, rhs);
}

BOOST_AUTO_TEST_CASE(DifferentTypeSelectorsYieldUnequal) {
	auto lhs = (Specifier() / "name")["selector"];
	auto rhs = (Specifier() / "name").is("selector");

	BOOST_CHECK_NE(lhs, rhs);
}

BOOST_AUTO_TEST_CASE(SameSelectorsYieldEqual) {
	auto lhs = (Specifier() / "name")[Specifier("subNode").is("selector")];
	auto rhs = (Specifier() / "name")[Specifier("subNode").is("selector")];

	BOOST_CHECK_EQUAL(lhs, rhs);
}

BOOST_AUTO_TEST_SUITE_END(/* SpecifierTestSuite */);
