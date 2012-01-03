#include <boost/test/auto_unit_test.hpp>

#include <sstream>
#include <ostream>
#include <map>

#include "configuration/parsers/PropertiesParser.hpp"
#include "../../test-utils.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration::parsers;

namespace {

BOOST_FIXTURE_TEST_SUITE(PropertiesParserTestSuite, test::ResourcesDirFixture);

BOOST_AUTO_TEST_CASE(IgnoresEmptyLines) {
    boost::filesystem::path conf = resourcesDir() / "conf";
    const std::string CONFIGURATION_CONTENTS =
            "\n"
            "\t\t           \t\n"
            "\n"
            "        \t # comment # \n"
            ;
    test::writeToFile(conf, CONFIGURATION_CONTENTS);

    PropertiesParser parser(conf);
    PropertiesParser::ParsedConfiguration parsed = parser.parse();

    BOOST_CHECK(parsed.begin() == parsed.end());
}

BOOST_AUTO_TEST_CASE(ReadsValues) {
    boost::filesystem::path conf = resourcesDir() / "conf";
    const std::string CONFIGURATION_CONTENTS =
            "key=value\n"
            "a key with\tspaces=a value with\tspaces\n"
            ;
    test::writeToFile(conf, CONFIGURATION_CONTENTS);

    PropertiesParser parser(conf);
    PropertiesParser::ParsedConfiguration parsed = parser.parse();

    PropertiesParser::ParsedConfiguration::ConstIterator it = parsed.begin();
    BOOST_REQUIRE(it != parsed.end());
    BOOST_CHECK_EQUAL(it->first, "key");
    BOOST_CHECK_EQUAL(it->second, "value");
    ++it;
    BOOST_REQUIRE(it != parsed.end());
    BOOST_CHECK_EQUAL(it->first, "a key with\tspaces");
    BOOST_CHECK_EQUAL(it->second, "a value with\tspaces");
    ++it;
    BOOST_REQUIRE(it == parsed.end());
}

BOOST_AUTO_TEST_CASE(TrimsKeysAndValues) {
    boost::filesystem::path conf = resourcesDir() / "conf";
    const std::string CONFIGURATION_CONTENTS =
            "\t\t    key \t = \t\t\tvalue          \t\n"
            ;
    test::writeToFile(conf, CONFIGURATION_CONTENTS);

    PropertiesParser parser(conf);
    PropertiesParser::ParsedConfiguration parsed = parser.parse();

    PropertiesParser::ParsedConfiguration::ConstIterator it = parsed.begin();
    BOOST_REQUIRE(it != parsed.end());
    BOOST_CHECK_EQUAL(it->first, "key");
    BOOST_CHECK_EQUAL(it->second, "value");
    ++it;
    BOOST_REQUIRE(it == parsed.end());
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
