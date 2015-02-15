#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/design-pattern/factory/storage/PermanentStorage.hpp"

using namespace coconut_tools;
using namespace coconut_tools::design_pattern::factory;
using namespace coconut_tools::design_pattern::factory::storage;

namespace {

BOOST_AUTO_TEST_SUITE(DesignPatternTestSuite);
BOOST_AUTO_TEST_SUITE(FactoryTestSuite);
BOOST_AUTO_TEST_SUITE(TestSuite);
BOOST_AUTO_TEST_SUITE(PermanentStorageTestSuite);

BOOST_AUTO_TEST_CASE(StoreReplacesExistingEntry) {
    typedef PermanentStorage<std::string, std::unique_ptr<int> > PermanentStorage;
    PermanentStorage storage;

    int* instance = new int;
    int* newInstance = new int;

    PermanentStorage::Permanent stored = storage.store("instance", std::unique_ptr<int>(instance));
    PermanentStorage::Permanent newStored = storage.store("instance", std::unique_ptr<int>(newInstance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(newStored.get(), newInstance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), newInstance);
}

BOOST_AUTO_TEST_CASE(ReturnsStoredInstanceWhenExists) {
    typedef PermanentStorage<std::string, std::unique_ptr<int> > PermanentStorage;
    PermanentStorage storage;

    int* instance = new int;

    PermanentStorage::Permanent stored = storage.store("instance", std::unique_ptr<int>(instance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(RetainsInstanceWhenUnused) {
    typedef PermanentStorage<std::string, std::unique_ptr<int> > PermanentStorage;
    PermanentStorage storage;

    int* instance = new int;

    storage.store("instance", std::unique_ptr<int>(instance));

    BOOST_CHECK(storage.get("instance"));
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(ErasesExistingInstances) {
    typedef PermanentStorage<std::string, std::unique_ptr<int> > PermanentStorage;
    PermanentStorage storage;

    int* instance = new int;

    storage.store("instance", std::unique_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(EraseIsNoOpOnNoExistingInstances) {
    typedef PermanentStorage<std::string, std::unique_ptr<int> > PermanentStorage;
    PermanentStorage storage;

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(IsStoredReturnsTrueIfInstancePresent) {
    typedef PermanentStorage<std::string, std::unique_ptr<int> > PermanentStorage;
    PermanentStorage storage;

    int* instance = new int;

    storage.store("instance", std::unique_ptr<int>(instance));

    BOOST_CHECK(storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(IsStoredReturnsFalseIfInstanceNotPresent) {
    typedef PermanentStorage<std::string, std::unique_ptr<int> > PermanentStorage;
    PermanentStorage storage;

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(IsStoredReturnsTrueIfInstanceRemoved) {
    typedef PermanentStorage<std::string, std::unique_ptr<int> > PermanentStorage;
    PermanentStorage storage;

    int* instance = new int;

    storage.store("instance", std::unique_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_SUITE_END(/* PermanentStorageTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* StorageTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* DesignPatternTestSuite */);

} // anonymous namespace
