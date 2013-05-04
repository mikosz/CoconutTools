#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/design-pattern/factory/storage/PermanentStorage.hpp"
#include "coconut-tools/design-pattern/factory/locking-policy.hpp"
#include "coconut-tools/test-utils/GMockFixture.hpp"

using namespace coconut_tools;
using namespace coconut_tools::design_pattern::factory;
using namespace coconut_tools::design_pattern::factory::storage;

namespace {

class MockLockingPolicy {
public:

    MOCK_METHOD1(lock, void (void*));

};

MockLockingPolicy mockLockingPolicy;

BOOST_AUTO_TEST_SUITE(DesignPatternTestSuite);
BOOST_AUTO_TEST_SUITE(FactoryTestSuite);
BOOST_AUTO_TEST_SUITE(StorageTestSuite);
BOOST_FIXTURE_TEST_SUITE(PermanentStorageTestSuite, test_utils::GMockFixture);

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageStoreReplacesExistingEntry) {
    typedef PermanentStorage<std::string, int, MockLockingPolicy> PermanentStorage;
    PermanentStorage storage(&mockLockingPolicy);

    int* instance = new int;
    int* newInstance = new int;

    PermanentStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));
    PermanentStorage::Permanent newStored = storage.store("instance", std::auto_ptr<int>(newInstance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(newStored.get(), newInstance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), newInstance);
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageStoreReplacesExistingEntry) {
    typedef PermanentStorage<std::string, int, UniqueMutexLockingPolicy> PermanentStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile PermanentStorage storage(&lockingPolicy);

    int* instance = new int;
    int* newInstance = new int;

    PermanentStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));
    PermanentStorage::Permanent newStored = storage.store("instance", std::auto_ptr<int>(newInstance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(newStored.get(), newInstance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), newInstance);
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageReturnsStoredInstanceWhenExists) {
    typedef PermanentStorage<std::string, int, MockLockingPolicy> PermanentStorage;
    PermanentStorage storage(&mockLockingPolicy);

    int* instance = new int;

    PermanentStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageReturnsStoredInstanceWhenExists) {
    typedef PermanentStorage<std::string, int, UniqueMutexLockingPolicy> PermanentStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile PermanentStorage storage(&lockingPolicy);

    int* instance = new int;

    PermanentStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageRetainsInstanceWhenUnused) {
    typedef PermanentStorage<std::string, int, MockLockingPolicy> PermanentStorage;
    PermanentStorage storage(&mockLockingPolicy);

    int* instance = new int;

    storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK(storage.get("instance"));
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageRetainsInstanceWhenUnused) {
    typedef PermanentStorage<std::string, int, UniqueMutexLockingPolicy> PermanentStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile PermanentStorage storage(&lockingPolicy);

    int* instance = new int;

    storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK(storage.get("instance"));
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageErasesExistingInstances) {
    typedef PermanentStorage<std::string, int, MockLockingPolicy> PermanentStorage;
    PermanentStorage storage(&mockLockingPolicy);

    int* instance = new int;

    storage.store("instance", std::auto_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageErasesExistingInstances) {
    typedef PermanentStorage<std::string, int, UniqueMutexLockingPolicy> PermanentStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile PermanentStorage storage(&lockingPolicy);

    int* instance = new int;

    storage.store("instance", std::auto_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageEraseIsNoOpOnNoExistingInstances) {
    typedef PermanentStorage<std::string, int, MockLockingPolicy> PermanentStorage;
    PermanentStorage storage(&mockLockingPolicy);

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageEraseIsNoOpOnNoExistingInstances) {
    typedef PermanentStorage<std::string, int, UniqueMutexLockingPolicy> PermanentStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile PermanentStorage storage(&lockingPolicy);

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageIsStoredReturnsTrueIfInstancePresent) {
    typedef PermanentStorage<std::string, int, MockLockingPolicy> PermanentStorage;
    PermanentStorage storage(&mockLockingPolicy);

    int* instance = new int;

    storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK(storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageIsStoredReturnsTrueIfInstancePresent) {
    typedef PermanentStorage<std::string, int, UniqueMutexLockingPolicy> PermanentStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile PermanentStorage storage(&lockingPolicy);

    int* instance = new int;

    storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK(storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageIsStoredReturnsFalseIfInstanceNotPresent) {
    typedef PermanentStorage<std::string, int, MockLockingPolicy> PermanentStorage;
    PermanentStorage storage(&mockLockingPolicy);

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageIsStoredReturnsFalseIfInstanceNotPresent) {
    typedef PermanentStorage<std::string, int, UniqueMutexLockingPolicy> PermanentStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile PermanentStorage storage(&lockingPolicy);

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageIsStoredReturnsTrueIfInstanceRemoved) {
    typedef PermanentStorage<std::string, int, MockLockingPolicy> PermanentStorage;
    PermanentStorage storage(&mockLockingPolicy);

    int* instance = new int;

    storage.store("instance", std::auto_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageIsStoredReturnsFalseIfInstanceRemoved) {
    typedef PermanentStorage<std::string, int, UniqueMutexLockingPolicy> PermanentStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile PermanentStorage storage(&lockingPolicy);

    int* instance = new int;

    storage.store("instance", std::auto_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_SUITE_END(/* PermanentStorageTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* StorageTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* DesignPatternTestSuite */);

} // anonymous namespace
