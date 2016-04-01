#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/enum.hpp"

namespace /* anonymous */ {

CCN_ENUM(TestEnum,
	(VALUE0)
	(VALUE1)
	(VALUE2)
	);

BOOST_AUTO_TEST_SUITE(EnumTestSuite);

BOOST_AUTO_TEST_CASE(EnumValuesAreIncrementingIntegers) {
	BOOST_CHECK_EQUAL(static_cast<int>(TestEnum::VALUE0), 0);
	BOOST_CHECK_EQUAL(static_cast<int>(TestEnum::VALUE1), 1);
	BOOST_CHECK_EQUAL(static_cast<int>(TestEnum::VALUE2), 2);
}

BOOST_AUTO_TEST_CASE(EnumToStringYieldsName) {
	BOOST_CHECK_EQUAL(toString(TestEnum::VALUE0), "VALUE0");
	BOOST_CHECK_EQUAL(toString(TestEnum::VALUE1), "VALUE1");
	BOOST_CHECK_EQUAL(toString(TestEnum::VALUE2), "VALUE2");
}

BOOST_AUTO_TEST_CASE(EnumFromStringReadsName) {
	BOOST_FAIL("Unimplemented");
}

BOOST_AUTO_TEST_CASE(EnumFromStringThrowsOnBadName) {
	BOOST_FAIL("Unimplemented");
}

BOOST_AUTO_TEST_SUITE_END(/* EnumTestSuite */);

} // anonymous namespace
