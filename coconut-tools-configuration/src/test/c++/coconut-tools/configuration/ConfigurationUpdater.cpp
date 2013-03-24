#include <boost/test/auto_unit_test.hpp>

#include <string>

#include "coconut-tools/configuration/ConfigurationUpdater.hpp"
#include "coconut-tools/configuration/Configurable.hpp"
#include "coconut-tools/configuration/FlatConfiguration.hpp"
#include "coconut-tools/test-utils/GMockFixture.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using testing::_;

namespace {

class MockConfigurable : public Configurable<Configuration<std::string, std::string> > {
public:

    MockConfigurable(ConfigurationUpdater<Configuration>& configurationUpdater) :
            Configurable<Configuration>(configurationUpdater) {
    }

    MOCK_CONST_METHOD1(verify, void (const Configuration&));

    MOCK_METHOD1(update, void (const Configuration&));

};

class UnupdateableConfigurable : public Configurable<Configuration<std::string, std::string> > {
public:

    UnupdateableConfigurable(ConfigurationUpdater<Configuration>& configurationUpdater) :
        Configurable<Configuration>(configurationUpdater) {
    }

    void verify(const Configuration&) const {
        // FIXME: style: this can probably be implemented using EXPECT_CALL and MockConfigurable
        throw ConfigurationValueNotUpdateable("", "", "");
    }

    void update(const Configuration&) {
    }

};

BOOST_FIXTURE_TEST_SUITE(ConfigurationUpdaterTestSuite, test::GMockFixture);

BOOST_AUTO_TEST_CASE(UpdatesRegisteredConfigurables) {
    FlatConfiguration<std::string, std::string> conf;
    ConfigurationUpdater<Configuration<std::string, std::string> > updater;

    MockConfigurable configurable1(updater), configurable2(updater);
    EXPECT_CALL(configurable1, verify(_)).Times(2);
    EXPECT_CALL(configurable1, update(_)).Times(2);
    EXPECT_CALL(configurable2, verify(_)).Times(2);
    EXPECT_CALL(configurable2, update(_)).Times(2);

    {
        MockConfigurable configurable3(updater);
        EXPECT_CALL(configurable3, verify(_)).Times(1);
        EXPECT_CALL(configurable3, update(_)).Times(1);

        updater.update(conf);
    }

    updater.update(conf);
}

BOOST_AUTO_TEST_CASE(UpdatesAtomically) {
    FlatConfiguration<std::string, std::string>::Storage vals;
    FlatConfiguration<std::string, std::string> conf(vals);
    ConfigurationUpdater<Configuration<std::string, std::string> > updater;

    MockConfigurable configurable1(updater), configurable2(updater);
    EXPECT_CALL(configurable1, verify(_)).Times(testing::AtMost(1));
    EXPECT_CALL(configurable1, update(_)).Times(0);
    EXPECT_CALL(configurable2, verify(_)).Times(testing::AtMost(1));
    EXPECT_CALL(configurable2, update(_)).Times(0);


    UnupdateableConfigurable unupdateableConfigurable(updater);

    BOOST_CHECK_THROW(updater.update(conf), ConfigurationValueNotUpdateable);
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
