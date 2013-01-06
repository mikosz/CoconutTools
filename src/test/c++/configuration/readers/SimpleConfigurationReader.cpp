#include <boost/test/auto_unit_test.hpp>

#include <string>
#include <sstream>

#include "configuration/readers/SimpleConfigurationReader.hpp"
#include "configuration/parsers/PropertiesParser.hpp"
#include "test-utils.hpp"
#include "GMockFixture.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::readers;

namespace {

class MockIntFloatConfiguration : public Configuration<int, float> {
public:

    MOCK_METHOD0(clear, void ());

    MOCK_CONST_METHOD0(empty, bool ());

    MOCK_CONST_METHOD1(count, size_t (int));

    MOCK_CONST_METHOD1(get, float (int));

    MOCK_CONST_METHOD2(getAll, void (int, Values*));

    MOCK_METHOD2(set, void (int, float));

    MOCK_METHOD2(add, void (int, float));

    MOCK_METHOD1(erase, void (int));

    MOCK_CONST_METHOD1(keys, void (Keys*));

};

BOOST_FIXTURE_TEST_SUITE(SimpleConfigurationReaderTestSuite, test::GMockFixture);

BOOST_AUTO_TEST_CASE(AddsKeyValuePairsParsedFromStream) {
    const std::string CONFIGURATION_CONTENTS =
            "42 = 3.14\n"
            "0 = 0.001\n"
            ;
    std::istringstream configurationStream(CONFIGURATION_CONTENTS);

    testing::StrictMock<MockIntFloatConfiguration> configuration;
    EXPECT_CALL(configuration, add(42, 3.14f)).Times(1);
    EXPECT_CALL(configuration, add(0, 0.001f)).Times(1);

    SimpleConfigurationReader<int, float> reader;
    reader.read(parsers::PropertiesParser(), configurationStream, &configuration);
}

BOOST_FIXTURE_TEST_CASE(AddsKeyValuePairsParsedFromFile, test::ResourcesDirFixture) {
    const std::string CONFIGURATION_CONTENTS =
            "42 = 3.14\n"
            "0 = 0.001\n"
            ;
    const boost::filesystem::path CONFIGURATION_PATH(CONFIGURATION_CONTENTS);
    test::writeToFile(CONFIGURATION_PATH, CONFIGURATION_CONTENTS);

    testing::StrictMock<MockIntFloatConfiguration> configuration;
    EXPECT_CALL(configuration, add(42, 3.14f)).Times(1);
    EXPECT_CALL(configuration, add(0, 0.001f)).Times(1);

    SimpleConfigurationReader<int, float> reader;
    reader.read(parsers::PropertiesParser(), CONFIGURATION_PATH, &configuration);
}

BOOST_AUTO_TEST_SUITE_END(/* SimpleConfigurationReaderTestSuite */)

} // anonymous namespace
