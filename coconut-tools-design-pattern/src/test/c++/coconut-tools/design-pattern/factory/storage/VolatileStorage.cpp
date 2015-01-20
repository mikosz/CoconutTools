#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/design-pattern/factory/storage/VolatileStorage.hpp"

using namespace coconut_tools;
using namespace coconut_tools::design_pattern::factory;
using namespace coconut_tools::design_pattern::factory::storage;

namespace {

BOOST_AUTO_TEST_SUITE(DesignPatternTestSuite);
BOOST_AUTO_TEST_SUITE(FactoryTestSuite);
BOOST_AUTO_TEST_SUITE(StorageTestSuite);
BOOST_AUTO_TEST_SUITE(VolatileStorageTestSuite);

BOOST_AUTO_TEST_CASE(StoreReplacesExistingEntry) {
    typedef VolatileStorage<std::string, int> VolatileStorage;
    VolatileStorage storage;

    int* instance = new int;
    int* newInstance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::unique_ptr<int>(instance));
    VolatileStorage::Permanent newStored = storage.store("instance", std::unique_ptr<int>(newInstance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(newStored.get(), newInstance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), newInstance);
}

BOOST_AUTO_TEST_CASE(ReturnsStoredInstanceWhenExists) {
    typedef VolatileStorage<std::string, int> VolatileStorage;
    VolatileStorage storage;

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::unique_ptr<int>(instance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(InvalidatesInstanceWhenUnused) {
    typedef VolatileStorage<std::string, int> VolatileStorage;
    VolatileStorage storage;

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::unique_ptr<int>(instance));

    stored.reset();

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ErasesExistingInstances) {
    typedef VolatileStorage<std::string, int> VolatileStorage;
    VolatileStorage storage;

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::unique_ptr<int>(instance));

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(EraseIsNoOpOnNoExistingInstances) {
    typedef VolatileStorage<std::string, int> VolatileStorage;
    VolatileStorage storage;

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(IsStoredReturnsTrueIfInstancePresent) {
    typedef VolatileStorage<std::string, int> VolatileStorage;
    VolatileStorage storage;

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::unique_ptr<int>(instance));

    BOOST_CHECK(storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(IsStoredReturnsFalseIfInstanceNotPresent) {
    typedef VolatileStorage<std::string, int> VolatileStorage;
    VolatileStorage storage;

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(IsStoredReturnsTrueIfInstanceRemoved) {
    typedef VolatileStorage<std::string, int> VolatileStorage;
    VolatileStorage storage;

    int* instance = new int;

    VolatileStorage::Permanent stored = storage.store("instance", std::unique_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_SUITE_END(/* VolatileStorageTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* StorageTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* DesignPatternTestSuite */);

} // anonymous namespace
