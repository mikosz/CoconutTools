#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/test-utils/test-utils.hpp"
#include "coconut-tools/configuration/hierarchical/HierarchicalConfiguration.hpp"
#include "coconut-tools/configuration/parsers/XMLParser.hpp"
#include "coconut-tools/configuration/readers/HierarchicalConfigurationReader.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::readers;

using coconut_tools::configuration::hierarchical::HierarchicalConfiguration;
using coconut_tools::configuration::hierarchical::HierarchicalConfigurationSharedPtr;

namespace {

BOOST_AUTO_TEST_SUITE(CoconutToolsConfigurationTestSuite);
BOOST_AUTO_TEST_SUITE(ReadersTestSuite);
BOOST_AUTO_TEST_SUITE(HierarchicalConfigurationReaderTestSuite);

BOOST_AUTO_TEST_CASE(AddsKeyValuePairsParsedFromStream) {
    const std::string CONFIGURATION_CONTENTS =
            "<parent>\n"
            "  <key0>value 0.0</key0>\n"
            "  <key1>value 0.1</key1>\n"
            "</parent>\n"
            "<parent>\n"
            "  <key0>value 1.0</key0>\n"
            "  <key1>value 1.1</key1>\n"
            "</parent>\n"
            ;
    std::istringstream configurationStream(CONFIGURATION_CONTENTS);

    HierarchicalConfigurationSharedPtr configuration = HierarchicalConfiguration::create();

    HierarchicalConfigurationReader reader;
    reader.read(parsers::XMLParser(), configurationStream, configuration.get());

    HierarchicalConfiguration::Values nodes;
    configuration->getAll("parent", &nodes);

    BOOST_CHECK_EQUAL(nodes.size(), 2);
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::ostringstream value1, value2;
        value1 << "value " << i << ".0";
        value2 << "value " << i << ".1";

        BOOST_CHECK_EQUAL(nodes[i]->get("key0")->text(), value1.str());
        BOOST_CHECK_EQUAL(nodes[i]->get("key1")->text(), value2.str());
    }
}

BOOST_FIXTURE_TEST_CASE(AddsKeyValuePairsParsedFromFile, test_utils::ResourcesDirFixture) {
    const std::string CONFIGURATION_CONTENTS =
            "<parent>\n"
            "  <key0>value 0.0</key0>\n"
            "  <key1>value 0.1</key1>\n"
            "</parent>\n"
            "<parent>\n"
            "  <key0>value 1.0</key0>\n"
            "  <key1>value 1.1</key1>\n"
            "</parent>\n"
            ;
    const boost::filesystem::path CONFIGURATION_PATH(resourcesDir() / "configuration.xml");
    test_utils::writeToFile(CONFIGURATION_PATH, CONFIGURATION_CONTENTS);

    HierarchicalConfigurationSharedPtr configuration = HierarchicalConfiguration::create();

    HierarchicalConfigurationReader reader;
    reader.read(parsers::XMLParser(), CONFIGURATION_PATH, configuration.get());

    HierarchicalConfiguration::Values nodes;
    configuration->getAll("parent", &nodes);

    BOOST_CHECK_EQUAL(nodes.size(), 2);
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::ostringstream value1, value2;
        value1 << "value " << i << ".0";
        value2 << "value " << i << ".1";

        BOOST_CHECK_EQUAL(nodes[i]->get("key0")->text(), value1.str());
        BOOST_CHECK_EQUAL(nodes[i]->get("key1")->text(), value2.str());
    }
}

BOOST_AUTO_TEST_SUITE_END(/* HierarchicalConfigurationReaderTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* ReadersTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* CoconutToolsConfigurationTestSuite */);

} // anonymous namespace
