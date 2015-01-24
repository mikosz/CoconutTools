#include <boost/test/auto_unit_test.hpp>

#include <algorithm>
#include <functional>

#include <boost/mpl/list.hpp>

#include "coconut-tools/configuration/Configuration.hpp"
#include "coconut-tools/configuration/FlatConfiguration.hpp"
#include "coconut-tools/configuration/StackedConfiguration.hpp"
#include "coconut-tools/configuration/HierarchicalConfiguration.hpp"
#include "coconut-tools/utils/pointee.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;

namespace {

typedef boost::mpl::list<
        FlatConfiguration<int, int>,
        StackedConfiguration<int, int>,
        FlatConfiguration<std::string, std::string>,
        StackedConfiguration<std::string, std::string>,
        HierarchicalConfiguration
        >
        ConfigurationImpls;

template <class ConfigurationType>
class ConfigurationTestSetup {
};

class IntIntConfigurationTestSetup {
public:

    typedef int Key;

    typedef int Value;

    IntIntConfigurationTestSetup() :
        singleEntry_(1, 1),
        multipleEntriesKey_(2) {
        multipleEntries_.push_back(2);
        multipleEntries_.push_back(3);
        multipleEntries_.push_back(4);
    }

    void setSingle(Configuration<int, int>* configurationParam) const {
        Configuration<int, int>& configuration = utils::pointee(configurationParam);
        configuration.set(singleEntry_.first, singleEntry_.second);
    }

    void addMultiple(Configuration<int, int>* configurationParam) const {
        Configuration<int, int>& configuration = utils::pointee(configurationParam);
        std::for_each(
                multipleEntries_.begin(),
                multipleEntries_.end(),
                std::bind(
                        &Configuration<int, int>::add, std::ref(configuration), multipleEntriesKey(), std::placeholders::_1)
        );
    }

    const std::pair<int, int>& singleEntry() const {
        return singleEntry_;
    }

    int multipleEntriesKey() const {
        return multipleEntriesKey_;
    }

    const std::vector<int>& multipleEntries() const {
        return multipleEntries_;
    }

    void checkValuesEqual(int lhs, int rhs) const {
        BOOST_CHECK_EQUAL(lhs, rhs);
    }

private:

    std::pair<int, int> singleEntry_;

    int multipleEntriesKey_;

    std::vector<int> multipleEntries_;

};

template<>
class ConfigurationTestSetup<FlatConfiguration<int, int> > : public IntIntConfigurationTestSetup {
public:

    typedef FlatConfiguration<int, int> ConfigurationImpl;

    typedef std::shared_ptr<ConfigurationImpl> Ptr;

    Ptr create() {
        return Ptr(new ConfigurationImpl);
    }

};

template <>
class ConfigurationTestSetup<StackedConfiguration<int, int> > : public IntIntConfigurationTestSetup {
public:

    typedef StackedConfiguration<int, int> ConfigurationImpl;

    typedef std::shared_ptr<ConfigurationImpl> Ptr;

    Ptr create() {
        Ptr result(new ConfigurationImpl);
        result->push(Configuration<int, int>::Ptr(new FlatConfiguration<int, int>));
        return result;
    }

};

template <>
class ConfigurationTestSetup<HierarchicalConfiguration> {
public:

    typedef std::shared_ptr<HierarchicalConfiguration> Ptr;

    typedef hierarchical::NodeSpecifier Key;

    typedef std::shared_ptr<HierarchicalConfiguration> Value;

    ConfigurationTestSetup() :
        singleEntry_(Key("single"), HierarchicalConfiguration::create("value")),
        multipleEntriesKey_(Key("multiple")) {
        multipleEntries_.push_back(HierarchicalConfiguration::create("value 1"));
        multipleEntries_.push_back(HierarchicalConfiguration::create("value 2"));
        multipleEntries_.push_back(HierarchicalConfiguration::create("value 3"));
    }

    Ptr create() {
        return HierarchicalConfiguration::create();
    }

    void setSingle(Configuration<Key, Value>* configurationParam) const {
        Configuration<Key, Value>& configuration = utils::pointee(configurationParam);
        configuration.set(singleEntry_.first, singleEntry_.second);
    }

    void addMultiple(Configuration<Key, Value>* configurationParam) const {
        Configuration<Key, Value>& configuration = utils::pointee(configurationParam);
        std::for_each(
                multipleEntries_.begin(),
                multipleEntries_.end(),
                std::bind(
                        &Configuration<Key, Value>::add, std::ref(configuration), multipleEntriesKey(), std::placeholders::_1)
        );
    }

    const std::pair<Key, Value>& singleEntry() const {
        return singleEntry_;
    }

    Key multipleEntriesKey() const {
        return multipleEntriesKey_;
    }

    const std::vector<Value>& multipleEntries() const {
        return multipleEntries_;
    }

    void checkValuesEqual(Value lhs, Value rhs) const {
        BOOST_CHECK_EQUAL(*lhs, *rhs);
    }

private:

    std::pair<Key, Value> singleEntry_;

    Key multipleEntriesKey_;

    std::vector<Value> multipleEntries_;

};

class StringStringConfigurationTestSetup {
public:

    typedef std::string Key;

    typedef std::string Value;

    StringStringConfigurationTestSetup() :
        singleEntry_("one", "one"),
        multipleEntriesKey_("two") {
        multipleEntries_.push_back("two");
        multipleEntries_.push_back("three");
        multipleEntries_.push_back("four");
    }

    void setSingle(Configuration<std::string, std::string>* configurationParam) const {
        Configuration<std::string, std::string>& configuration = utils::pointee(configurationParam);
        configuration.set(singleEntry_.first, singleEntry_.second);
    }

    void addMultiple(Configuration<std::string, std::string>* configurationParam) const {
        Configuration<std::string, std::string>& configuration = utils::pointee(configurationParam);
        std::for_each(
                multipleEntries_.begin(),
                multipleEntries_.end(),
                std::bind(
                        &Configuration<std::string, std::string>::add,
                        std::ref(configuration),
                        multipleEntriesKey(),
                        std::placeholders::_1
                        )
        );
    }

    const std::pair<std::string, std::string>& singleEntry() const {
        return singleEntry_;
    }

    const std::string& multipleEntriesKey() const {
        return multipleEntriesKey_;
    }

    const std::vector<std::string>& multipleEntries() const {
        return multipleEntries_;
    }

    void checkValuesEqual(const std::string& lhs, const std::string& rhs) const {
        BOOST_CHECK_EQUAL(lhs, rhs);
    }

private:

    std::pair<std::string, std::string> singleEntry_;

    std::string multipleEntriesKey_;

    std::vector<std::string> multipleEntries_;

};

template<>
class ConfigurationTestSetup<FlatConfiguration<std::string, std::string> > :
        public StringStringConfigurationTestSetup {
public:

    typedef FlatConfiguration<std::string, std::string> ConfigurationImpl;

    typedef std::shared_ptr<ConfigurationImpl> Ptr;

    Ptr create() {
        return Ptr(new ConfigurationImpl);
    }

};

template <>
class ConfigurationTestSetup<StackedConfiguration<std::string, std::string> > :
            public StringStringConfigurationTestSetup {
public:

    typedef StackedConfiguration<std::string, std::string> ConfigurationImpl;

    typedef std::shared_ptr<ConfigurationImpl> Ptr;

    Ptr create() {
        Ptr result(new ConfigurationImpl);
        result->push(
                Configuration<std::string, std::string>::Ptr(
                        new FlatConfiguration<std::string, std::string>)
                        );
        return result;
    }

};

/**
 * This test suite should be executed for every concrete Configuration implementation.
 * Each test verifies whether the implementation accords with the contract.
 */
BOOST_AUTO_TEST_SUITE(ConfigurationTestSuite);

BOOST_AUTO_TEST_CASE_TEMPLATE(ClearYieldsEmptyConfiguration, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.setSingle(configuration.get());
    setup.addMultiple(configuration.get());

    configuration->clear();
    BOOST_CHECK(configuration->empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ClearWorksForEmptyConfiguration, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    configuration->clear();
    BOOST_CHECK(configuration->empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(EmptyYieldsTrueForEmptyConfiguration, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    BOOST_CHECK(configuration->empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(EmptyYieldsFalseForNonEmptyConfiguration, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.setSingle(configuration.get());
    BOOST_CHECK(!configuration->empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(CountReturns0WhenKeyIsNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    BOOST_CHECK_EQUAL(configuration->count(setup.singleEntry().first), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(CountReturnsNumberOfOccurences, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.addMultiple(configuration.get());
    BOOST_CHECK_EQUAL(configuration->count(setup.multipleEntriesKey()), setup.multipleEntries().size());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetReturnsStoredElement, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.setSingle(configuration.get());
    setup.checkValuesEqual(configuration->get(setup.singleEntry().first), setup.singleEntry().second);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetThrowsWhenKeyNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    BOOST_CHECK_THROW(configuration->get(setup.singleEntry().first), MissingRequiredValue);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetThrowsWhenMultipleKeysPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.addMultiple(configuration.get());
    BOOST_CHECK_THROW(configuration->get(setup.multipleEntriesKey()), MultipleValuesWhereSingleValueRequired);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetAllYieldsAllOccurences, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.addMultiple(configuration.get());
    typename ConfigurationImpl::Values values;
    configuration->getAll(setup.multipleEntriesKey(), &values);

    BOOST_REQUIRE_EQUAL(values.size(), setup.multipleEntries().size());
    for (size_t i = 0; i < values.size(); ++i) {
        setup.checkValuesEqual(values[i], setup.multipleEntries()[i]);
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetAllYieldsEmptyVectorWhenKeyNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    typename ConfigurationImpl::Values values;
    configuration->getAll(setup.multipleEntriesKey(), &values);
    BOOST_CHECK(values.empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SetAddsKeyWhenNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    configuration->set(setup.singleEntry().first, setup.singleEntry().second);
    setup.checkValuesEqual(configuration->get(setup.singleEntry().first), setup.singleEntry().second);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SetReplacesAllOccurencesWithSingleInstance, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.addMultiple(configuration.get());
    configuration->set(setup.multipleEntriesKey(), setup.singleEntry().second);
    setup.checkValuesEqual(configuration->get(setup.multipleEntriesKey()), setup.singleEntry().second);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddAddsKeyWhenNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    configuration->add(setup.singleEntry().first, setup.singleEntry().second);
    setup.checkValuesEqual(configuration->get(setup.singleEntry().first), setup.singleEntry().second);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddAddsANewInstanceOfKey, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    configuration->add(setup.multipleEntriesKey(), setup.multipleEntries()[0]);
    configuration->add(setup.multipleEntriesKey(), setup.multipleEntries()[1]);
    BOOST_CHECK_EQUAL(configuration->count(setup.multipleEntriesKey()), 2);

    typename ConfigurationImpl::Values values;
    configuration->getAll(setup.multipleEntriesKey(), &values);
    BOOST_REQUIRE_EQUAL(values.size(), 2);
    setup.checkValuesEqual(values[0], setup.multipleEntries()[0]);
    setup.checkValuesEqual(values[1], setup.multipleEntries()[1]);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(EraseRemovesAllKeyOccurences, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.setSingle(configuration.get());
    setup.addMultiple(configuration.get());
    configuration->erase(setup.multipleEntriesKey());
    BOOST_CHECK_EQUAL(configuration->count(setup.multipleEntriesKey()), 0);
    BOOST_CHECK_EQUAL(configuration->count(setup.singleEntry().first), 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(EraseIsVoidWhenKeyNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.addMultiple(configuration.get());

    configuration->erase(setup.singleEntry().first);

    BOOST_CHECK_EQUAL(configuration->count(setup.singleEntry().first), 0);
    BOOST_CHECK_EQUAL(configuration->count(setup.multipleEntriesKey()), setup.multipleEntries().size());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(KeysReturnsAllKeys, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.setSingle(configuration.get());
    setup.addMultiple(configuration.get());

    typename ConfigurationImpl::Keys keys;
    configuration->keys(&keys);

    BOOST_REQUIRE_EQUAL(keys.size(), 2);
    BOOST_CHECK_EQUAL(keys.count(std::cref(setup.singleEntry().first)), 1);
    BOOST_CHECK_EQUAL(keys.count(setup.multipleEntriesKey()), 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(KeysYieldsEmptyWhenConfigurationEmpty, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    typename ConfigurationImpl::Keys keys;
    configuration->keys(&keys);

    BOOST_CHECK(keys.empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetOptionalYieldsNullWhenKeyNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();


    BOOST_CHECK(!configuration->getOptional(setup.singleEntry().first));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetOptionalYieldsValueWhenKeyPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.setSingle(configuration.get());

    setup.checkValuesEqual(
            *configuration->getOptional(setup.singleEntry().first),
            setup.singleEntry().second
            );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetOptionalThowsWhenMultipleKeysPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationTestSetup<ConfigurationImpl> setup;
    std::shared_ptr<ConfigurationImpl> configuration = setup.create();

    setup.addMultiple(configuration.get());

    BOOST_CHECK_THROW(
            configuration->getOptional(setup.multipleEntriesKey()),
            MultipleValuesWhereSingleValueRequired
            );
}

BOOST_AUTO_TEST_SUITE_END(/* ConfigurationTestSuite */);

} // anonymous namespace
