#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/logger/layout/EmptyLayout.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::layout;

namespace {

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);
BOOST_AUTO_TEST_SUITE(LayoutTestSuite);
BOOST_AUTO_TEST_SUITE(EmptyLayoutTestSuite);

BOOST_AUTO_TEST_CASE(AddsANewlineAtEnd) {
	const std::string testString("test string");

	EmptyLayout layout;

	BOOST_CHECK_EQUAL(layout.format(Level::INFO, Context(), testString), testString + '\n');
}

BOOST_AUTO_TEST_SUITE_END(/* EmptyLayoutTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LayoutTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LoggerTestSuite */);

} // anonymous namespace
