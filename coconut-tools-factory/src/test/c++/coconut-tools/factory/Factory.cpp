#include <boost/test/auto_unit_test.hpp>

#include <string>
#include <memory>

#include <boost/thread/mutex.hpp>

#include <gmock/gmock.h>

#include "coconut-tools/factory/Factory.hpp"
#include "coconut-tools/factory/storage.hpp"
#include "coconut-tools/factory/error-policy.hpp"

#include "coconut-tools/test-utils/GMockFixture.hpp"

namespace {

using namespace coconut_tools;
using namespace coconut_tools::factory;

class MockCreator {
public:

	MOCK_METHOD1(doCreate, std::shared_ptr<int> (const std::string&));

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

    using Delegate = testing::StrictMock<MockStorage>;

    using Instance = std::shared_ptr<int>;

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

    Instance get(const std::string& id) {
        int value = delegate()->get(id);
        if (value) {
            return std::make_unique<int>(value);
        } else {
            return std::make_unique<int>();
        }
    }

    bool isStored(const std::string& id) {
        return delegate()->isStored(id);
    }

    Instance store(const std::string& id, std::shared_ptr<int> instance) {
        return std::make_shared<int>(delegate()->store(id, *instance));
    }

    void erase(const std::string& id) {
        delegate()->erase(id);
    }

private:

    static std::shared_ptr<Delegate> delegate_;

};

template<class T1, class T2>
std::shared_ptr<typename SingletonMockStorageAdapter<T1, T2>::Delegate> SingletonMockStorageAdapter<T1, T2>::delegate_;

BOOST_AUTO_TEST_SUITE(FactoryTestSuite);
BOOST_FIXTURE_TEST_SUITE(FactoryTestSuite, test_utils::GMockFixture);

BOOST_AUTO_TEST_CASE(CallsCreators) {
    Factory<
        std::string,
        std::shared_ptr<int>,
        storage::None,
        MockCreator,
        boost::mutex
        > f;

    EXPECT_CALL(f, doCreate("1")).WillOnce(testing::Return(std::make_shared<int>(1)));
    EXPECT_CALL(f, doCreate("2")).WillOnce(testing::Return(std::make_shared<int>(2)));

    BOOST_CHECK_EQUAL(*f.create("1"), 1);
    BOOST_CHECK_EQUAL(*f.create("2"), 2);
}

BOOST_AUTO_TEST_CASE(StoresCreatedInstances) {
    using Storage = SingletonMockStorageAdapter<std::string, int>;

    Storage::reset();

    Factory<
        std::string,
        int,
        SingletonMockStorageAdapter,
        MockCreator,
        boost::mutex
        > f;

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

    EXPECT_CALL(f, doCreate("1")).WillOnce(testing::Return(std::make_shared<int>(1)));
    EXPECT_CALL(f, doCreate("2")).WillOnce(testing::Return(std::make_shared<int>(2)));

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

BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);

} // anonymous namespace
