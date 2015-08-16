#include <boost/test/auto_unit_test.hpp>

#include <sstream>

#include "coconut-tools/logger/print.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

namespace /* anonymous */ {

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);
BOOST_AUTO_TEST_SUITE(PrintTestSuite);

BOOST_AUTO_TEST_CASE(PrintsOutputStreamableValues) {
	std::ostringstream oss;
	print(oss, 42);

	BOOST_CHECK_EQUAL(oss.str(), "42");
}

BOOST_AUTO_TEST_CASE(PrintsCollectionsAsCommaDelimitedLists) {
	std::vector<int> v = { 1, 2, 3 };

	std::ostringstream oss;
	print(oss, v);

	BOOST_CHECK_EQUAL(oss.str(), "1, 2, 3");
}

BOOST_AUTO_TEST_CASE(PrintsEmptyCollectionsAsEmptyString) {
	std::vector<int> v;

	std::ostringstream oss;
	print(oss, v);

	BOOST_CHECK_EQUAL(oss.str(), "");
}

BOOST_AUTO_TEST_CASE(PrintsSingleValueCollectionsWithoutComma) {
	std::vector<int> v = { 1 };

	std::ostringstream oss;
	print(oss, v);

	BOOST_CHECK_EQUAL(oss.str(), "1");
}

BOOST_AUTO_TEST_CASE(PrintsCStyleArrays) {
	int a[] = { 1, 2, 3 };

	std::ostringstream oss;
	print(oss, a);

	BOOST_CHECK_EQUAL(oss.str(), "1, 2, 3");
}

BOOST_AUTO_TEST_CASE(PrintsCustomCollections) {
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END(/* PrintTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LoggerTestSuite */);

} // anonymous namespace
