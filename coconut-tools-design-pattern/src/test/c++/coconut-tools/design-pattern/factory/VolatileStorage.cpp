#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/design-pattern/factory/storage/VolatileStorage.hpp"
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
BOOST_FIXTURE_TEST_SUITE(VolatileStorageTestSuite, test_utils::GMockFixture);

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageStoreReplacesExistingEntry) {
    typedef VolatileStorage<std::string, int, MockLockingPolicy> VolatileStorage;
    VolatileStorage storage(&mockLockingPolicy);

    int* instance = new int;
    int* newInstance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));
    VolatileStorage::Permanent newStored = storage.store("instance", std::auto_ptr<int>(newInstance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(newStored.get(), newInstance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), newInstance);
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageStoreReplacesExistingEntry) {
    typedef VolatileStorage<std::string, int, UniqueMutexLockingPolicy> VolatileStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile VolatileStorage storage(&lockingPolicy);

    int* instance = new int;
    int* newInstance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));
    VolatileStorage::Permanent newStored = storage.store("instance", std::auto_ptr<int>(newInstance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(newStored.get(), newInstance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), newInstance);
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageReturnsStoredInstanceWhenExists) {
    typedef VolatileStorage<std::string, int, MockLockingPolicy> VolatileStorage;
    VolatileStorage storage(&mockLockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageReturnsStoredInstanceWhenExists) {
    typedef VolatileStorage<std::string, int, UniqueMutexLockingPolicy> VolatileStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile VolatileStorage storage(&lockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageInvalidatesInstanceWhenUnused) {
    typedef VolatileStorage<std::string, int, MockLockingPolicy> VolatileStorage;
    VolatileStorage storage(&mockLockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    stored.reset();

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageInvalidatesInstanceWhenUnused) {
    typedef VolatileStorage<std::string, int, UniqueMutexLockingPolicy> VolatileStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile VolatileStorage storage(&lockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    stored.reset();

    BOOST_CHECK(!storage.get("instance").get());
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageErasesExistingInstances) {
    typedef VolatileStorage<std::string, int, MockLockingPolicy> VolatileStorage;
    VolatileStorage storage(&mockLockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageErasesExistingInstances) {
    typedef VolatileStorage<std::string, int, UniqueMutexLockingPolicy> VolatileStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile VolatileStorage storage(&lockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageEraseIsNoOpOnNoExistingInstances) {
    typedef VolatileStorage<std::string, int, MockLockingPolicy> VolatileStorage;
    VolatileStorage storage(&mockLockingPolicy);

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageEraseIsNoOpOnNoExistingInstances) {
    typedef VolatileStorage<std::string, int, UniqueMutexLockingPolicy> VolatileStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile VolatileStorage storage(&lockingPolicy);

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageIsStoredReturnsTrueIfInstancePresent) {
    typedef VolatileStorage<std::string, int, MockLockingPolicy> VolatileStorage;
    VolatileStorage storage(&mockLockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK(storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageIsStoredReturnsTrueIfInstancePresent) {
    typedef VolatileStorage<std::string, int, UniqueMutexLockingPolicy> VolatileStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile VolatileStorage storage(&lockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));

    BOOST_CHECK(storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageIsStoredReturnsFalseIfInstanceNotPresent) {
    typedef VolatileStorage<std::string, int, MockLockingPolicy> VolatileStorage;
    VolatileStorage storage(&mockLockingPolicy);

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageIsStoredReturnsFalseIfInstanceNotPresent) {
    typedef VolatileStorage<std::string, int, UniqueMutexLockingPolicy> VolatileStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile VolatileStorage storage(&lockingPolicy);

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadUnsafeStorageIsStoredReturnsTrueIfInstanceRemoved) {
    typedef VolatileStorage<std::string, int, MockLockingPolicy> VolatileStorage;
    VolatileStorage storage(&mockLockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(ThreadSafeStorageIsStoredReturnsFalseIfInstanceRemoved) {
    typedef VolatileStorage<std::string, int, UniqueMutexLockingPolicy> VolatileStorage;
    UniqueMutexLockingPolicy lockingPolicy;
    volatile VolatileStorage storage(&lockingPolicy);

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::auto_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_SUITE_END(/* VolatileStorageTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* StorageTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* DesignPatternTestSuite */);

} // anonymous namespace
