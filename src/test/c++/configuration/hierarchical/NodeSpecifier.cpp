#include <boost/test/auto_unit_test.hpp>

#include "configuration/hierarchical/NodeSpecifier.hpp"

using namespace coconut_tools::configuration::hierarchical;

BOOST_AUTO_TEST_SUITE(NodeSpecifierTestSuite);

BOOST_AUTO_TEST_CASE(EmptyStringYieldsEmptyNodeSpecifier) {
    NodeSpecifier nodeSpecifier("");
    BOOST_CHECK(nodeSpecifier.empty());
}

BOOST_AUTO_TEST_SUITE_END(/* NodeSpecifierTestSuite */);
