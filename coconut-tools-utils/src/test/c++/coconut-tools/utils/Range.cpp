#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/system/platform.hpp"

#if defined(CT_COMPILER_VISUAL_CXX)
#	pragma warning(push)
#	pragma warning(disable: 4172) // boost adaptor reversed emits "returning address of temporary"
#endif /* CT_COMPILER_VISUAL_CXX */

#include <boost/range/adaptor/reversed.hpp>

#if defined(CT_COMPILER_VISUAL_CXX)
#	pragma warning(pop)
#endif /* CT_COMPILER_VISUAL_CXX */

#include "coconut-tools/utils/Range.hpp"

using namespace coconut_tools;

namespace /* anonymous */ {

BOOST_AUTO_TEST_SUITE(IndexRangeTestSuite);

BOOST_AUTO_TEST_CASE(IterationForwardWorks) {
	auto range = IndexRange(0, 2);

	auto it = range.begin();
	auto end = range.end();

	BOOST_CHECK_EQUAL(*it, 0);
	++it;
	BOOST_CHECK_EQUAL(*it, 1);
	++it;
	BOOST_CHECK(it == end);
}

BOOST_AUTO_TEST_CASE(IterationBackwardWorks) {
	auto range = IndexRange(0, 2);

	auto it = range.rbegin();
	auto end = range.rend();

	BOOST_CHECK_EQUAL(*it, 1);
	++it;
	BOOST_CHECK_EQUAL(*it, 0);
	++it;
	BOOST_CHECK(it == end);
}

BOOST_AUTO_TEST_CASE(RangeBasedForIteratesOverIndices) {
	auto index = 42;
	for (auto i : IndexRange(42, 50)) {
		BOOST_CHECK_EQUAL(index, i);
		++index;
	}
	BOOST_CHECK_EQUAL(index, 50);
}

BOOST_AUTO_TEST_CASE(RangeAdaptorReversedIteratesReversed) {
	auto index = 49;
	for (auto i : IndexRange(42, 50) | boost::adaptors::reversed) {
		BOOST_CHECK_EQUAL(index, i);
		--index;
	}
	BOOST_CHECK_EQUAL(index, 41);
};

BOOST_AUTO_TEST_CASE(IteratesOverFloatsWithCustomStep, *boost::unit_test::tolerance(0.00001f)) {
	auto value = 3.14f;
	for (auto f : range(3.14f, 4.14f, 0.2f)) {
		BOOST_CHECK_EQUAL(value, f);
		value += 0.2f;
	}
	BOOST_TEST(value == 4.14f);
}

BOOST_AUTO_TEST_SUITE_END(/* IndexRangeTestSuite */);

} // anonymous namespace
