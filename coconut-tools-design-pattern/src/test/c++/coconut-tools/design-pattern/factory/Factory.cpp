#include <boost/test/auto_unit_test.hpp>

#include <string>

#include <boost/function.hpp>

#include <gmock/gmock.h>

#include "coconut-tools/design-pattern/factory/Factory.hpp"
#include "coconut-tools/design-pattern/factory/storage.hpp"
#include "coconut-tools/design-pattern/factory/locking-policy.hpp"
#include "coconut-tools/test-utils/GMockFixture.hpp"

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

    typedef testing::StrictMock<MockCreator<int> > Delegate;

    CopyableMockCreatorAdapter() :
        delegate_(new Delegate) {
    }

    boost::shared_ptr<Delegate> delegate() const {
        return delegate_;
    }

    std::auto_ptr<int> create() {
        return std::auto_ptr<int>(new int(delegate_->create()));
    }

private:

    boost::shared_ptr<Delegate> delegate_;

};

template <class, class>
class MockStorage {
public:

    MOCK_CONST_METHOD1(get, int(const std::string&));

    MOCK_CONST_METHOD1(isStored, bool(const std::string&));

    MOCK_METHOD2(store, int(const std::string&, int));

    MOCK_METHOD1(erase, void(const std::string&));

};

template <class, class>
class SingletonMockStorageAdapter {
public:

    typedef testing::StrictMock<MockStorage<std::string, int> > Delegate;

    typedef std::auto_ptr<int> Permanent;

    static void reset() {
        delegate_.reset();
    }

    static boost::shared_ptr<Delegate> delegate() {
        if (!delegate_) {
            delegate_.reset(new Delegate);
        }
        return delegate_;
    }

    std::auto_ptr<int> get(const std::string& id) {
        int value = delegate_->get(id);
        if (value) {
            return std::auto_ptr<int>(new int(value));
        } else {
            return std::auto_ptr<int>();
        }
    }

    std::auto_ptr<int> isStored(const std::string& id) {
        return std::auto_ptr<int>(new int(delegate_->isStored(id)));
    }

    std::auto_ptr<int> store(const std::string& id, std::auto_ptr<int> instance) {
        return std::auto_ptr<int>(new int(delegate_->store(id, *instance)));
    }

    void erase(const std::string& id) {
        delegate_->erase(id);
    }

private:

    static boost::shared_ptr<Delegate> delegate_;

};

template<>
boost::shared_ptr<SingletonMockStorageAdapter<std::string, int>::Delegate> SingletonMockStorageAdapter<std::string, int>::delegate_;

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

BOOST_AUTO_TEST_CASE(StoresCreatedInstances) {
    typedef SingletonMockStorageAdapter<std::string, int> Storage;

    Storage::reset();

    Factory<
        std::string,
        int,
        SingletonMockStorageAdapter,
        CopyableMockCreatorAdapter,
        UniqueMutexLockingPolicy,
        ExceptionThrowingErrorPolicy
        > f;

    Storage storage;
    {
        testing::InSequence inSequence;

        EXPECT_CALL(*Storage::delegate(), get(std::string("1"))).WillOnce(testing::Return(0));
        EXPECT_CALL(*Storage::delegate(), store(std::string("1"), testing::_)).WillOnce(testing::Return(1));
        EXPECT_CALL(*Storage::delegate(), get(std::string("1"))).WillOnce(testing::Return(1));

        EXPECT_CALL(*Storage::delegate(), get(std::string("2"))).WillOnce(testing::Return(0));
        EXPECT_CALL(*Storage::delegate(), store(std::string("2"), testing::_)).WillOnce(testing::Return(2));
        EXPECT_CALL(*Storage::delegate(), get(std::string("2"))).WillOnce(testing::Return(2));
    }

    CopyableMockCreatorAdapter<int> creator1;
    EXPECT_CALL(*creator1.delegate(), create()).WillOnce(testing::Return(1));

    CopyableMockCreatorAdapter<int> creator2;
    EXPECT_CALL(*creator2.delegate(), create()).WillOnce(testing::Return(2));

    f.registerCreator("1", creator1);
    f.registerCreator("2", creator2);

    BOOST_CHECK_EQUAL(*f.create("1"), 1);
    BOOST_CHECK_EQUAL(*f.create("1"), 1);
    BOOST_CHECK_EQUAL(*f.create("2"), 2);
    BOOST_CHECK_EQUAL(*f.create("2"), 2);

    Storage::reset();
}

BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* DesignPatternTestSuite */);

} // anonymous namespace
