#include <boost/test/auto_unit_test.hpp>

#include <sstream>
#include <map>

#include <boost/bind.hpp>

#include "coconut-tools/configuration/parsers/PropertiesParser.hpp"
#include "coconut-tools/configuration/parsers/ParseError.hpp"
#include "coconut-tools/utils/pointee.hpp"
#include "coconut-tools/test-utils/test-utils.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration::parsers;

namespace {

typedef std::vector<std::pair<std::string, std::string> > ParsedConfiguration;

void put(
        const std::string& key,
        const std::string& value,
        ParsedConfiguration* targetParam
        ) {
    ParsedConfiguration& target = utils::pointee(targetParam);
    target.push_back(std::make_pair(key, value));
}

BOOST_AUTO_TEST_SUITE(PropertiesParserTestSuite);

BOOST_AUTO_TEST_CASE(IgnoresEmptyLines) {
    const std::string CONFIGURATION_CONTENTS =
            "\n"
            "\t\t           \t\n"
            "\n"
            "        \t # comment # \n"
            ;
    std::istringstream configurationStream(CONFIGURATION_CONTENTS);

    ParsedConfiguration parsed;

    PropertiesParser parser;
    parser.parse(configurationStream, boost::bind(&put, _1, _2, &parsed));

    BOOST_CHECK(parsed.empty());
}

BOOST_AUTO_TEST_CASE(ReadsValues) {
    const std::string CONFIGURATION_CONTENTS =
            "key=value\n"
            "a key with\tspaces=a value with\tspaces\n"
            ;
    std::istringstream configurationStream(CONFIGURATION_CONTENTS);

    ParsedConfiguration parsed;

    PropertiesParser parser;
    parser.parse(configurationStream, boost::bind(&put, _1, _2, &parsed));

    ParsedConfiguration::const_iterator it = parsed.begin();
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

BOOST_AUTO_TEST_CASE(PrependsCategory) {
    const std::string CONFIGURATION_CONTENTS =
            "key=value\n"
            "[category]\n"
            "key in category=value in category\n"
            "[category 2]\n"
            "key in category 2=value in category 2\n"
            ;
    std::istringstream configurationStream(CONFIGURATION_CONTENTS);

    ParsedConfiguration parsed;

    PropertiesParser parser;
    parser.parse(configurationStream, boost::bind(&put, _1, _2, &parsed));

    ParsedConfiguration::const_iterator it = parsed.begin();
    BOOST_REQUIRE(it != parsed.end());
    BOOST_CHECK_EQUAL(it->first, "key");
    BOOST_CHECK_EQUAL(it->second, "value");
    ++it;
    BOOST_REQUIRE(it != parsed.end());
    BOOST_CHECK_EQUAL(it->first, "category.key in category");
    BOOST_CHECK_EQUAL(it->second, "value in category");
    ++it;
    BOOST_REQUIRE(it != parsed.end());
    BOOST_CHECK_EQUAL(it->first, "category 2.key in category 2");
    BOOST_CHECK_EQUAL(it->second, "value in category 2");
    ++it;
    BOOST_REQUIRE(it == parsed.end());

}

BOOST_AUTO_TEST_CASE(TrimsKeysValuesAndCategories) {
    const std::string CONFIGURATION_CONTENTS =
            "\t\t  [   \t category  \t ]   \n"
            "\t\t    key \t = \t\t\tvalue          \t\n"
            ;
    std::istringstream configurationStream(CONFIGURATION_CONTENTS);

    ParsedConfiguration parsed;

    PropertiesParser parser;
    parser.parse(configurationStream, boost::bind(&put, _1, _2, &parsed));

    ParsedConfiguration::const_iterator it = parsed.begin();
    BOOST_REQUIRE(it != parsed.end());
    BOOST_CHECK_EQUAL(it->first, "category.key");
    BOOST_CHECK_EQUAL(it->second, "value");
    ++it;
    BOOST_REQUIRE(it == parsed.end());
}

BOOST_AUTO_TEST_CASE(ThrowsWithEmptyPathOnInvalidStream) {
    const std::string CONFIGURATION_CONTENTS =
            "this is bad"
            ;
    std::istringstream configurationStream(CONFIGURATION_CONTENTS);

    ParsedConfiguration parsed;

    PropertiesParser parser;
    try {
        parser.parse(configurationStream, boost::bind(&put, _1, _2, &parsed));
        BOOST_FAIL("ParseError expected ");
    } catch (const ParseError& e) {
        BOOST_CHECK(e.path().empty());
        BOOST_CHECK_EQUAL(e.lineNo(), 1);
    }
}

BOOST_FIXTURE_TEST_CASE(ThrowsWithPathOnInvalidFile, test::ResourcesDirFixture) {
    const std::string CONFIGURATION_CONTENTS =
            "this is bad"
            ;
    const boost::filesystem::path CONFIGURATION_PATH(resourcesDir() / "conf");
    test::writeToFile(CONFIGURATION_PATH, CONFIGURATION_CONTENTS);

    ParsedConfiguration parsed;

    PropertiesParser parser;
    try {
        parser.parse(CONFIGURATION_PATH, boost::bind(&put, _1, _2, &parsed));
        BOOST_FAIL("ParseError expected ");
    } catch (const ParseError& e) {
        BOOST_CHECK_EQUAL(e.path(), CONFIGURATION_PATH);
        BOOST_CHECK_EQUAL(e.lineNo(), 1);
    }
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
