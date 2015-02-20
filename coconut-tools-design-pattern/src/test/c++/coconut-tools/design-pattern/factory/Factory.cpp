#include <boost/test/auto_unit_test.hpp>

#include <string>
#include <memory>

#include <gmock/gmock.h>

#include "coconut-tools/design-pattern/factory/Factory.hpp"
#include "coconut-tools/design-pattern/factory/storage.hpp"
#include "coconut-tools/design-pattern/factory/error-policy.hpp"
#include "coconut-tools/design-pattern/locking-policy.hpp"

#include "coconut-tools/test-utils/GMockFixture.hpp"

namespace {

using namespace coconut_tools;
using namespace coconut_tools::design_pattern;
using namespace coconut_tools::design_pattern::factory;

class MockCreator {
public:

    MOCK_METHOD0(create, int ());

};

class CopyableMockCreatorAdapter {
public:

    typedef testing::StrictMock<MockCreator> Delegate;

    CopyableMockCreatorAdapter() :
        delegate_(new Delegate) {
    }

    std::shared_ptr<Delegate> delegate() const {
        return delegate_;
    }

    std::unique_ptr<int> create() {
        return std::unique_ptr<int>(new int(delegate_->create()));
    }

private:

    std::shared_ptr<Delegate> delegate_;

};

class MockStorage {
public:

    MOCK_CONST_METHOD1(get, int (const std::string&));

    MOCK_CONST_METHOD1(isStored, bool (const std::string&));

    MOCK_METHOD2(store, int (const std::string&, int));

    MOCK_METHOD1(erase, void (const std::string&));

};

template <class, class>
class SingletonMockStorageAdapter {
public:

    typedef testing::StrictMock<MockStorage> Delegate;

    typedef std::unique_ptr<int> Permanent;

    ~SingletonMockStorageAdapter() {
        reset();
    }

    static void reset() {
        delegate_.reset();
    }

    static std::shared_ptr<Delegate> delegate() {
        if (!delegate_) {
            delegate_.reset(new Delegate);
        }
        return delegate_;
    }

    std::unique_ptr<int> get(const std::string& id) {
        int value = delegate()->get(id);
        if (value) {
            return std::unique_ptr<int>(new int(value));
        } else {
            return std::unique_ptr<int>();
        }
    }

    bool isStored(const std::string& id) {
        return delegate()->isStored(id);
    }

    std::unique_ptr<int> store(const std::string& id, std::unique_ptr<int> instance) {
        return std::unique_ptr<int>(new int(delegate()->store(id, *instance)));
    }

    void erase(const std::string& id) {
        delegate()->erase(id);
    }

private:

    static std::shared_ptr<Delegate> delegate_;

};

template<class T1, class T2>
std::shared_ptr<typename SingletonMockStorageAdapter<T1, T2>::Delegate> SingletonMockStorageAdapter<T1, T2>::delegate_;

class MockErrorPolicy {
public:

    MOCK_METHOD1(alreadyRegistered, void (const std::string&));

    MOCK_METHOD1(noSuchType, void (const std::string&));

};

template <class>
class StaticFunctionMockErrorPolicyAdapter {
public:

    typedef testing::StrictMock<MockErrorPolicy> Delegate;

    static void reset() {
        delegate_.reset();
    }

    static std::shared_ptr<Delegate> delegate() {
        if (!delegate_) {
            delegate_.reset(new Delegate);
        }
        return delegate_;
    }

    static void alreadyRegistered(const std::string& id) {
        delegate_->alreadyRegistered(id);
    }

    static void noSuchType(const std::string& id) {
        delegate_->noSuchType(id);
    }

private:

    static std::shared_ptr<Delegate> delegate_;

};

template<class T>
std::shared_ptr<typename StaticFunctionMockErrorPolicyAdapter<T>::Delegate> StaticFunctionMockErrorPolicyAdapter<T>::delegate_;

BOOST_AUTO_TEST_SUITE(DesignPatternTestSuite);
BOOST_FIXTURE_TEST_SUITE(FactoryTestSuite, test_utils::GMockFixture);

BOOST_AUTO_TEST_CASE(CallsCreatorsTest) {
    Factory<
        std::string,
        std::unique_ptr<int>,
        NoStorage,
        CopyableMockCreatorAdapter,
        UniqueMutexLockingPolicy,
        ExceptionThrowingErrorPolicy
        > f;

    CopyableMockCreatorAdapter creator1;
    EXPECT_CALL(*creator1.delegate(), create()).WillOnce(testing::Return(1));

    CopyableMockCreatorAdapter creator2;
    EXPECT_CALL(*creator2.delegate(), create()).WillOnce(testing::Return(2));

    f.registerCreator("1", creator1);
    f.registerCreator("2", creator2);

    BOOST_CHECK_EQUAL(*f.create("1"), 1);
    BOOST_CHECK_EQUAL(*f.create("2"), 2);
}

BOOST_AUTO_TEST_CASE(StoresCreatedInstances) {
    typedef SingletonMockStorageAdapter<std::string, std::unique_ptr<int> > Storage;

    Storage::reset();

    Factory<
        std::string,
        std::unique_ptr<int>,
        SingletonMockStorageAdapter,
        CopyableMockCreatorAdapter,
        UniqueMutexLockingPolicy,
        ExceptionThrowingErrorPolicy
        > f;

    // Storage storage;
    {
        testing::InSequence inSequence;

        EXPECT_CALL(*Storage::delegate(), isStored(std::string("1"))).WillOnce(testing::Return(false));
        EXPECT_CALL(*Storage::delegate(), store(std::string("1"), testing::_)).WillOnce(testing::Return(1));
		EXPECT_CALL(*Storage::delegate(), isStored(std::string("1"))).WillOnce(testing::Return(true));
        EXPECT_CALL(*Storage::delegate(), get(std::string("1"))).WillOnce(testing::Return(1));

		EXPECT_CALL(*Storage::delegate(), isStored(std::string("2"))).WillOnce(testing::Return(false));
		EXPECT_CALL(*Storage::delegate(), store(std::string("2"), testing::_)).WillOnce(testing::Return(2));
		EXPECT_CALL(*Storage::delegate(), isStored(std::string("2"))).WillOnce(testing::Return(true));
		EXPECT_CALL(*Storage::delegate(), get(std::string("2"))).WillOnce(testing::Return(2));
    }

    CopyableMockCreatorAdapter creator1;
    EXPECT_CALL(*creator1.delegate(), create()).WillOnce(testing::Return(1));

    CopyableMockCreatorAdapter creator2;
    EXPECT_CALL(*creator2.delegate(), create()).WillOnce(testing::Return(2));

    f.registerCreator("1", creator1);
    f.registerCreator("2", creator2);

	auto one1 = f.create("1");
	auto one2 = f.create("1");
	auto two1 = f.create("2");
	auto two2 = f.create("2");

	BOOST_REQUIRE(one1);
	BOOST_REQUIRE(one2);
	BOOST_REQUIRE(two1);
	BOOST_REQUIRE(two1);

    BOOST_CHECK_EQUAL(*one1, 1);
	BOOST_CHECK_EQUAL(*one2, 1);
	BOOST_CHECK_EQUAL(*two1, 2);
	BOOST_CHECK_EQUAL(*two2, 2);
}

BOOST_AUTO_TEST_CASE(CallsNoSuchTypeIfCreatingAndCreatorNotRegistered) {
    typedef StaticFunctionMockErrorPolicyAdapter<std::string> ErrorPolicy;

    ErrorPolicy::reset();

    Factory<
        std::string,
        std::unique_ptr<int>,
        NoStorage,
        CopyableMockCreatorAdapter,
        UniqueMutexLockingPolicy,
        StaticFunctionMockErrorPolicyAdapter
        > f;

    EXPECT_CALL(*ErrorPolicy::delegate(), noSuchType(std::string("1")));

    f.create("1");

    ErrorPolicy::reset();
}

BOOST_AUTO_TEST_CASE(CallsNoSuchTypeIfUnregisteringAndCreatorNotRegistered) {
    typedef StaticFunctionMockErrorPolicyAdapter<std::string> ErrorPolicy;

    ErrorPolicy::reset();

    Factory<
        std::string,
        int,
        NoStorage,
        CopyableMockCreatorAdapter,
        UniqueMutexLockingPolicy,
        StaticFunctionMockErrorPolicyAdapter
        > f;

    EXPECT_CALL(*ErrorPolicy::delegate(), noSuchType(std::string("1")));

    f.unregisterCreator("1");

    ErrorPolicy::reset();
}

BOOST_AUTO_TEST_CASE(CallsCreatorAlreadyRegisteredIfRegisteringAndCreatorRegistered) {
    typedef StaticFunctionMockErrorPolicyAdapter<std::string> ErrorPolicy;

    ErrorPolicy::reset();

    Factory<
        std::string,
        int,
        NoStorage,
        CopyableMockCreatorAdapter,
        UniqueMutexLockingPolicy,
        StaticFunctionMockErrorPolicyAdapter
        > f;

    EXPECT_CALL(*ErrorPolicy::delegate(), alreadyRegistered(std::string("1")));

    CopyableMockCreatorAdapter creator;

    f.registerCreator("1", creator);
    f.registerCreator("1", creator);

    ErrorPolicy::reset();
}

BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* DesignPatternTestSuite */);

} // anonymous namespace
