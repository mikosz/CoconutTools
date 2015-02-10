#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/configuration/hierarchical/node/Path.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;
using namespace coconut_tools::configuration::hierarchical::node;

BOOST_AUTO_TEST_SUITE(PathTestSuite);

BOOST_AUTO_TEST_CASE(EmptyStringYieldsEmptyPath) {
    Path nodePath("");
    BOOST_CHECK(nodePath.empty());
}

BOOST_AUTO_TEST_CASE(OperatorDivideAppendsPath) {
	auto nodePath = Path() / "a" / "b" / "c";
	BOOST_CHECK_EQUAL(nodePath.root(), "a");
	BOOST_CHECK_EQUAL(nodePath.childPath().root(), "b");
	BOOST_CHECK_EQUAL(nodePath.childPath().childPath().root(), "c");
}

BOOST_AUTO_TEST_CASE(DifferentValueSelectorsYieldUnequal) {
	auto lhs = (Path() / "name")["selector-1"];
	auto rhs = (Path() / "name")["selector-2"];

	BOOST_CHECK_NE(lhs, rhs);
}

BOOST_AUTO_TEST_CASE(DifferentTypeSelectorsYieldUnequal) {
	auto lhs = (Path() / "name")["selector"];
	auto rhs = (Path() / "name").is("selector");

	BOOST_CHECK_NE(lhs, rhs);
}

BOOST_AUTO_TEST_CASE(SameSelectorsYieldEqual) {
	auto lhs = (Path() / "name")[Path("subNode").is("selector")];
	auto rhs = (Path() / "name")[Path("subNode").is("selector")];

	BOOST_CHECK_EQUAL(lhs, rhs);
}

BOOST_AUTO_TEST_SUITE_END(/* PathTestSuite */);
