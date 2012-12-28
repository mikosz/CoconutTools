#include <boost/test/auto_unit_test.hpp>

#include <algorithm>

#include <boost/mpl/list.hpp>
#include <boost/bind.hpp>

#include "configuration/Configuration.hpp"
#include "configuration/FlatConfiguration.hpp"
#include "configuration/StackedConfiguration.hpp"
#include "utils/pointee.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;

namespace {

typedef boost::mpl::list<
        FlatConfiguration<int, int>,
        StackedConfiguration<int, int>,
        FlatConfiguration<std::string, std::string>,
        StackedConfiguration<std::string, std::string>
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
                boost::bind(
                        &Configuration<int, int>::add, boost::ref(configuration), multipleEntriesKey(), _1)
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

private:

    std::pair<int, int> singleEntry_;

    int multipleEntriesKey_;

    std::vector<int> multipleEntries_;

};

template<>
class ConfigurationTestSetup<FlatConfiguration<int, int> > : public IntIntConfigurationTestSetup {
public:

    void init(FlatConfiguration<int, int>* configurationPtr) {
    }

};

template <>
class ConfigurationTestSetup<StackedConfiguration<int, int> > : public IntIntConfigurationTestSetup {
public:

    void init(StackedConfiguration<int, int>* configurationPtr) {
        StackedConfiguration<int, int>& configuration = utils::pointee(configurationPtr);
        configuration.push(Configuration<int, int>::Ptr(new FlatConfiguration<int, int>));
    }

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
                boost::bind(
                        &Configuration<std::string, std::string>::add,
                        boost::ref(configuration),
                        multipleEntriesKey(),
                        _1
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

private:

    std::pair<std::string, std::string> singleEntry_;

    std::string multipleEntriesKey_;

    std::vector<std::string> multipleEntries_;

};

template<>
class ConfigurationTestSetup<FlatConfiguration<std::string, std::string> > :
        public StringStringConfigurationTestSetup {
public:

    void init(FlatConfiguration<std::string, std::string>* configurationPtr) {
    }

};

template <>
class ConfigurationTestSetup<StackedConfiguration<std::string, std::string> > :
            public StringStringConfigurationTestSetup {
public:

    void init(StackedConfiguration<std::string, std::string>* configurationPtr) {
        StackedConfiguration<std::string, std::string>& configuration = utils::pointee(configurationPtr);
        configuration.push(
                Configuration<std::string, std::string>::Ptr(new FlatConfiguration<std::string, std::string>)
                );
    }

};

/**
 * This test suite should be executed for every concrete Configuration implementation.
 * Each test verifies whether the implementation accords with the contract.
 */
BOOST_AUTO_TEST_SUITE(ConfigurationTestSuite);

BOOST_AUTO_TEST_CASE_TEMPLATE(ClearYieldsEmptyConfiguration, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.setSingle(&configuration);
    setup.addMultiple(&configuration);

    configuration.clear();
    BOOST_CHECK(configuration.empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ClearWorksForEmptyConfiguration, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    configuration.clear();
    BOOST_CHECK(configuration.empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(EmptyYieldsTrueForEmptyConfiguration, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    BOOST_CHECK(configuration.empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(EmptyYieldsFalseForNonEmptyConfiguration, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.setSingle(&configuration);
    BOOST_CHECK(!configuration.empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(CountReturns0WhenKeyIsNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    BOOST_CHECK_EQUAL(configuration.count(setup.singleEntry().first), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(CountReturnsNumberOfOccurences, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.addMultiple(&configuration);
    BOOST_CHECK_EQUAL(configuration.count(setup.multipleEntriesKey()), setup.multipleEntries().size());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetReturnsStoredElement, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.setSingle(&configuration);
    BOOST_CHECK_EQUAL(configuration.get(setup.singleEntry().first), setup.singleEntry().second);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetThrowsWhenKeyNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    BOOST_CHECK_THROW(configuration.get(setup.singleEntry().first), MissingRequiredValue);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetThrowsWhenMultipleKeysPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.addMultiple(&configuration);
    BOOST_CHECK_THROW(configuration.get(setup.multipleEntriesKey()), MultipleValuesWhereSingleValueRequired);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetAllYieldsAllOccurences, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.addMultiple(&configuration);
    typename ConfigurationImpl::ValueRefs values;
    configuration.getAll(setup.multipleEntriesKey(), &values);

    BOOST_REQUIRE_EQUAL(values.size(), setup.multipleEntries().size());
    for (size_t i = 0; i < values.size(); ++i) {
        BOOST_CHECK_EQUAL(values[i].get(), setup.multipleEntries()[i]);
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetAllYieldsEmptyVectorWhenKeyNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    typename ConfigurationImpl::ValueRefs values;
    configuration.getAll(setup.multipleEntriesKey(), &values);
    BOOST_CHECK(values.empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SetAddsKeyWhenNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    configuration.set(setup.singleEntry().first, setup.singleEntry().second);
    BOOST_CHECK_EQUAL(configuration.get(setup.singleEntry().first), setup.singleEntry().second);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(SetReplacesAllOccurencesWithSingleInstance, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.addMultiple(&configuration);
    configuration.set(setup.multipleEntriesKey(), setup.singleEntry().second);
    BOOST_CHECK_EQUAL(configuration.get(setup.multipleEntriesKey()), setup.singleEntry().second);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddAddsKeyWhenNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    configuration.add(setup.singleEntry().first, setup.singleEntry().second);
    BOOST_CHECK_EQUAL(configuration.get(setup.singleEntry().first), setup.singleEntry().second);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddAddsANewInstanceOfKey, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    configuration.add(setup.multipleEntriesKey(), setup.multipleEntries()[0]);
    configuration.add(setup.multipleEntriesKey(), setup.multipleEntries()[1]);
    BOOST_CHECK_EQUAL(configuration.count(setup.multipleEntriesKey()), 2);

    typename ConfigurationImpl::ValueRefs values;
    configuration.getAll(setup.multipleEntriesKey(), &values);
    BOOST_REQUIRE_EQUAL(values.size(), 2);
    BOOST_CHECK_EQUAL(values[0].get(), setup.multipleEntries()[0]);
    BOOST_CHECK_EQUAL(values[1].get(), setup.multipleEntries()[1]);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(EraseRemovesAllKeyOccurences, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.setSingle(&configuration);
    setup.addMultiple(&configuration);
    configuration.erase(setup.multipleEntriesKey());
    BOOST_CHECK_EQUAL(configuration.count(setup.multipleEntriesKey()), 0);
    BOOST_CHECK_EQUAL(configuration.count(setup.singleEntry().first), 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(EraseIsVoidWhenKeyNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.addMultiple(&configuration);

    configuration.erase(setup.singleEntry().first);

    BOOST_CHECK_EQUAL(configuration.count(setup.singleEntry().first), 0);
    BOOST_CHECK_EQUAL(configuration.count(setup.multipleEntriesKey()), setup.multipleEntries().size());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(KeysReturnsAllKeys, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.setSingle(&configuration);
    setup.addMultiple(&configuration);

    typename ConfigurationImpl::KeyRefs keys;
    configuration.keys(&keys);

    BOOST_REQUIRE_EQUAL(keys.size(), 2);
    BOOST_CHECK_EQUAL(keys.count(boost::cref(setup.singleEntry().first)), 1);
    BOOST_CHECK_EQUAL(keys.count(boost::cref(setup.multipleEntriesKey())), 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(KeysYieldsEmptyWhenConfigurationEmpty, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);

    typename ConfigurationImpl::KeyRefs keys;
    configuration.keys(&keys);

    BOOST_CHECK(keys.empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetOptionalYieldsNullWhenKeyNotPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);

    BOOST_CHECK(!configuration.getOptional(setup.singleEntry().first));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetOptionalYieldsValueWhenKeyPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.setSingle(&configuration);

    BOOST_CHECK_EQUAL(*configuration.getOptional(setup.singleEntry().first), setup.singleEntry().second);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(GetOptionalThowsWhenMultipleKeysPresent, ConfigurationImpl, ConfigurationImpls) {
    ConfigurationImpl configuration;
    ConfigurationTestSetup<ConfigurationImpl> setup;
    setup.init(&configuration);
    setup.addMultiple(&configuration);

    BOOST_CHECK_THROW(
            configuration.getOptional(setup.multipleEntriesKey()),
            MultipleValuesWhereSingleValueRequired
            );
}

BOOST_AUTO_TEST_SUITE_END(/* ConfigurationTestSuite */);

} // anonymous namespace
