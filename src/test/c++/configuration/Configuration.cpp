#include <boost/test/auto_unit_test.hpp>

#include "configuration/Configuration.hpp"

using namespace coconut_tools::configuration;

namespace {

BOOST_AUTO_TEST_SUITE(ConfigurationTestSuite);

BOOST_AUTO_TEST_CASE(getsValues) {
    Configuration::Values values;
    values["key"] = "value";
    values["one"] = "1";
    values["half"] = "0.5";
    Configuration conf(values);

    BOOST_CHECK_EQUAL(conf.getRequired<std::string>("key"), "value");
    BOOST_CHECK_EQUAL(*conf.get<std::string>("key"), "value");
    BOOST_CHECK_EQUAL(conf.getRequired<int>("one"), 1);
    BOOST_CHECK_EQUAL(*conf.get<int>("one"), 1);
    BOOST_CHECK_EQUAL(conf.getRequired<float>("half"), 0.5);
    BOOST_CHECK_EQUAL(*conf.get<float>("half"), 0.5);
}

BOOST_AUTO_TEST_CASE(getsDefaultValues) {
    Configuration::Values values;
    Configuration conf(values);

    BOOST_CHECK(!conf.get<std::string>("key"));
    BOOST_CHECK_EQUAL(*conf.get<std::string>("key", boost::optional<std::string>("default")), "default");
}

BOOST_AUTO_TEST_CASE(checksForValuePresence) {
    Configuration::Values values;
    values["present"] = "value";
    Configuration conf(values);

    BOOST_CHECK(conf.has("present"));
    BOOST_CHECK(!conf.has("not present"));
}

BOOST_AUTO_TEST_CASE(setsAndUnsetsValues) {
    Configuration::Values values;
    values["key"] = "value";
    Configuration conf(values);

    conf.set("key", "modified value");
    BOOST_CHECK_EQUAL(conf.getRequired<std::string>("key"), "modified value");

    conf.set("key2", "");
    BOOST_CHECK(conf.has("key2"));

    conf.unset("key");
    BOOST_CHECK(!conf.has("key"));
    conf.unset("key2");
    BOOST_CHECK(!conf.has("key2"));
}

BOOST_AUTO_TEST_CASE(throwsOnMissingRequiredValues) {
    Configuration::Values values;
    Configuration conf(values);

    BOOST_CHECK_THROW(conf.getRequired<std::string>("key"), MissingRequiredValue);
}

BOOST_AUTO_TEST_CASE(throwsOnBadValueType) {
    Configuration::Values values;
    values["string"] = "string";
    Configuration conf(values);

    BOOST_CHECK_THROW(conf.getRequired<int>("string"), boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
