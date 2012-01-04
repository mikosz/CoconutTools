#include <boost/test/auto_unit_test.hpp>

#include "configuration/Configuration.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;

namespace {

BOOST_AUTO_TEST_SUITE(ConfigurationTestSuite);

BOOST_AUTO_TEST_CASE(getsValues) {
    Configuration::Values values;
    values.insert(std::make_pair("key", "value"));
    values.insert(std::make_pair("one", "1"));
    values.insert(std::make_pair("half", "0.5"));
    Configuration conf(values);

    BOOST_CHECK_EQUAL(conf.getRequiredValue<std::string>("key"), "value");
    BOOST_CHECK_EQUAL(*conf.getValue<std::string>("key"), "value");
    BOOST_CHECK_EQUAL(conf.getRequiredValue<int>("one"), 1);
    BOOST_CHECK_EQUAL(*conf.getValue<int>("one"), 1);
    BOOST_CHECK_EQUAL(conf.getRequiredValue<float>("half"), 0.5);
    BOOST_CHECK_EQUAL(*conf.getValue<float>("half"), 0.5);
}

BOOST_AUTO_TEST_CASE(getsDefaultValues) {
    Configuration::Values values;
    Configuration conf(values);

    BOOST_CHECK(!conf.getValue<std::string>("key"));
    BOOST_CHECK_EQUAL(*conf.getValue<std::string>("key", boost::optional<std::string>("default")), "default");
}

BOOST_AUTO_TEST_CASE(checksForValuePresence) {
    Configuration::Values values;
    values.insert(std::make_pair("present", "value"));
    Configuration conf(values);

    BOOST_CHECK(conf.has("present"));
    BOOST_CHECK(!conf.has("not present"));
}

BOOST_AUTO_TEST_CASE(setsAndUnsetsValues) {
    Configuration::Values values;
    values.insert(std::make_pair("key", "value"));
    Configuration conf(values);

    conf.replace("key", "modified value");
    BOOST_CHECK_EQUAL(conf.getRequiredValue<std::string>("key"), "modified value");

    conf.insert("key2", "");
    BOOST_CHECK(conf.has("key2"));

    conf.insert("key2", "");
    BOOST_CHECK_EQUAL(conf.count("key2"), 2);

    conf.remove("key");
    BOOST_CHECK(!conf.has("key"));
    conf.remove("key2");
    BOOST_CHECK(!conf.has("key2"));
}

BOOST_AUTO_TEST_CASE(throwsOnMissingRequiredValues) {
    Configuration::Values values;
    Configuration conf(values);

    BOOST_CHECK_THROW(conf.getRequiredValue<std::string>("key"), MissingRequiredValue);
}

BOOST_AUTO_TEST_CASE(throwsOnBadValueType) {
    Configuration::Values values;
    values.insert(std::make_pair("string", "string"));
    Configuration conf(values);

    BOOST_CHECK_THROW(conf.getRequiredValue<int>("string"), boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE(getsValuesRange) {
    Configuration::Values values;
    values.insert(std::make_pair("single key", "value"));
    values.insert(std::make_pair("multi key", "value 1"));
    values.insert(std::make_pair("multi key", "value 2"));
    values.insert(std::make_pair("multi key", "value 3"));
    Configuration conf(values);

    utils::Sequence<Configuration::Values::const_iterator> range = conf.getValues("single key");

    BOOST_REQUIRE(!range.atEnd());
    BOOST_CHECK_EQUAL(range.current()->second, "value");
    range.next();
    BOOST_CHECK(range.atEnd());

    range = conf.getValues("multi key");

    BOOST_REQUIRE(!range.atEnd());
    BOOST_CHECK_EQUAL(range.current()->second, "value 1");
    range.next();
    BOOST_REQUIRE(!range.atEnd());
    BOOST_CHECK_EQUAL(range.current()->second, "value 2");
    range.next();
    BOOST_REQUIRE(!range.atEnd());
    BOOST_CHECK_EQUAL(range.current()->second, "value 3");
    range.next();
    BOOST_CHECK(range.atEnd());
}

BOOST_AUTO_TEST_CASE(throwsOnMultipleValuesWhereSingleValueExpected) {
    Configuration::Values values;
    values.insert(std::make_pair("key", ""));
    values.insert(std::make_pair("key", ""));
    Configuration conf(values);

    BOOST_CHECK_THROW(conf.getRequiredValue<std::string>("key"), MultipleValuesWhereSingleValueRequired);
    BOOST_CHECK_THROW(conf.getValue<std::string>("key"), MultipleValuesWhereSingleValueRequired);
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
