#include <boost/test/auto_unit_test.hpp>

#include <gmock/gmock.h>

#include "configuration/readers/BasicReader.hpp"
#include "GMockFixture.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::readers;

namespace {

class MockParser : public Parser {
public:

    MOCK_CONST_METHOD0(parse, ParsedConfiguration());

};

BOOST_FIXTURE_TEST_SUITE(BasicReaderTestSuite, test::GMockFixture);

BOOST_AUTO_TEST_CASE(ReadsParsedValues) {
    MockParser parser;
    boost::shared_ptr<Parser::ParsedConfiguration::Values> vals(new Parser::ParsedConfiguration::Values);
    vals->push_back(std::make_pair("key", "value"));
    vals->push_back(std::make_pair("key2", "value2"));
    Parser::ParsedConfiguration parsed(vals);

    EXPECT_CALL(parser, parse()).
            WillRepeatedly(testing::Return(parsed));

    BasicReader::Values readValues;
    BasicReader reader(parser);
    reader.read(readValues);

    BOOST_CHECK_EQUAL(readValues.size(), 2);
    BOOST_REQUIRE(readValues.count("key"));
    BOOST_CHECK_EQUAL(readValues.find("key")->second, "value");
    BOOST_REQUIRE(readValues.count("key2"));
    BOOST_CHECK_EQUAL(readValues.find("key2")->second, "value2");
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
