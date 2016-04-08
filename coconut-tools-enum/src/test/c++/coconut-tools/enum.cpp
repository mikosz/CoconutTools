#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/enum.hpp"

namespace /* anonymous */ {

CCN_ENUM(TestEnum,
	(VALUE0)
	(VALUE1)
	(VALUE2)
	);

CCN_ENUM_VALUES(TestEnumValues,
	(TRIANGLE)(3)
	(SQUARE)(4)
	);

BOOST_AUTO_TEST_SUITE(EnumTestSuite);

BOOST_AUTO_TEST_CASE(DefaultEnumValuesAreIncrementingIntegers) {
	BOOST_CHECK_EQUAL(static_cast<int>(TestEnum::VALUE0), 0);
	BOOST_CHECK_EQUAL(static_cast<int>(TestEnum::VALUE1), 1);
	BOOST_CHECK_EQUAL(static_cast<int>(TestEnum::VALUE2), 2);
}

BOOST_AUTO_TEST_CASE(ProvidedEnumValuesAreSet) {
	BOOST_CHECK_EQUAL(static_cast<int>(TestEnumValues::TRIANGLE), 3);
	BOOST_CHECK_EQUAL(static_cast<int>(TestEnumValues::SQUARE), 4);
}

BOOST_AUTO_TEST_CASE(EnumToStringYieldsName) {
	BOOST_CHECK_EQUAL(toString(TestEnum::VALUE0), "VALUE0");
	BOOST_CHECK_EQUAL(toString(TestEnum::VALUE1), "VALUE1");
	BOOST_CHECK_EQUAL(toString(TestEnum::VALUE2), "VALUE2");
	BOOST_CHECK_EQUAL(toString(TestEnumValues::TRIANGLE), "TRIANGLE");
	BOOST_CHECK_EQUAL(toString(TestEnumValues::SQUARE), "SQUARE");
}

BOOST_AUTO_TEST_CASE(EnumFromStringReadsName) {
	{
		TestEnum value;
		fromString(value, "VALUE0");
		BOOST_CHECK_EQUAL(value, TestEnum::VALUE0);
		fromString(value, "VALUE1");
		BOOST_CHECK_EQUAL(value, TestEnum::VALUE1);
		fromString(value, "VALUE2");
		BOOST_CHECK_EQUAL(value, TestEnum::VALUE2);
	}

	{
		TestEnumValues value;
		fromString(value, "TRIANGLE");
		BOOST_CHECK_EQUAL(value, TestEnumValues::TRIANGLE);
		fromString(value, "SQUARE");
		BOOST_CHECK_EQUAL(value, TestEnumValues::SQUARE);
	}
}

BOOST_AUTO_TEST_CASE(EnumFromStringThrowsOnBadName) {
	TestEnum value;
	BOOST_CHECK_THROW(fromString(value, "NOT_A_VALUE_STRING"), std::out_of_range); // TODO: use a custom exception
}

BOOST_AUTO_TEST_SUITE_END(/* EnumTestSuite */);

} // anonymous namespace