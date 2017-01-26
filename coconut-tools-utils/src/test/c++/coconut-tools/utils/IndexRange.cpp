#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include <boost/range/adaptor/reversed.hpp>

#include "coconut-tools/utils/IndexRange.hpp"

using namespace coconut_tools;

namespace /* anonymous */ {

BOOST_AUTO_TEST_SUITE(IndexRangeTestSuite);

BOOST_AUTO_TEST_CASE(RangeBasedForIteratesOverIndices) {
	size_t index = 42;
	for (auto i : IndexRange(42, 50)) {
		BOOST_CHECK_EQUAL(index, i);
		++index;
	}
	BOOST_CHECK_EQUAL(index, 50);
}

BOOST_AUTO_TEST_CASE(RangeAdaptorReversedIteratesReversed) {
	size_t index = 49;
	for (auto i : IndexRange(42, 50) | boost::adaptors::reversed) {
		BOOST_CHECK_EQUAL(index, i);
		--index;
	}
	BOOST_CHECK_EQUAL(index, 41);
};

BOOST_AUTO_TEST_SUITE_END(/* IndexRangeTestSuite */);

} // anonymous namespace
