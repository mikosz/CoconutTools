#include <boost/test/auto_unit_test.hpp>

#include <string>

#include <boost/function.hpp>

#include <gmock/gmock.h>

#include "coconut-tools/design-pattern/factory/Factory.hpp"
#include "coconut-tools/design-pattern/factory/storage.hpp"
#include "coconut-tools/design-pattern/factory/locking-policy.hpp"
#include "coconut-tools/test-utils/GMockFixture.hpp"
#include "coconut-tools/utils/Null.hpp"

namespace {

using namespace coconut_tools;
using namespace coconut_tools::design_pattern;
using namespace coconut_tools::design_pattern::factory;

template <class>
class MockCreator {
public:

    MOCK_METHOD0(create, int());

};

template <class>
class CopyableMockCreatorAdapter {
public:

    CopyableMockCreatorAdapter() :
        delegate_(new MockCreator<utils::Null>) {
    }

    boost::shared_ptr<MockCreator<utils::Null> > delegate() const {
        return delegate_;
    }

    std::auto_ptr<int> create() {
        return std::auto_ptr<int>(new int(delegate_->create()));
    }

private:

    boost::shared_ptr<MockCreator<utils::Null> > delegate_;

};

BOOST_AUTO_TEST_SUITE(DesignPatternTestSuite);
BOOST_AUTO_TEST_SUITE(FactoryTestSuite);

BOOST_AUTO_TEST_CASE(CallsCreatorsTest) {
    Factory<
        std::string,
        int,
        NoStorage,
        CopyableMockCreatorAdapter,
        UniqueMutexLockingPolicy,
        ExceptionThrowingErrorPolicy
        > f;

    CopyableMockCreatorAdapter<int> creator1;
    EXPECT_CALL(*creator1.delegate(), create()).WillOnce(testing::Return(1));

    CopyableMockCreatorAdapter<int> creator2;
    EXPECT_CALL(*creator2.delegate(), create()).WillOnce(testing::Return(2));

    f.registerCreator("1", creator1);
    f.registerCreator("2", creator2);

    BOOST_CHECK_EQUAL(*f.create("1"), 1);
    BOOST_CHECK_EQUAL(*f.create("2"), 2);
}

BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* DesignPatternTestSuite */);

} // anonymous namespace
