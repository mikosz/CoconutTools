#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/factory/storage/Permanent.hpp"

using namespace coconut_tools;
using namespace coconut_tools::factory;
using namespace coconut_tools::factory::storage;

namespace {

BOOST_AUTO_TEST_SUITE(FactoryTestSuite);
BOOST_AUTO_TEST_SUITE(TestSuite);
BOOST_AUTO_TEST_SUITE(PermanentTestSuite);

BOOST_AUTO_TEST_CASE(StoreReplacesExistingEntry) {
    using Permanent = Permanent<std::string, int>;
    Permanent storage;

    int* instance = new int;
    int* newInstance = new int;

    auto stored = storage.store("instance", std::unique_ptr<int>(instance));
    auto newStored = storage.store("instance", std::unique_ptr<int>(newInstance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(newStored.get(), newInstance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), newInstance);
}

BOOST_AUTO_TEST_CASE(ReturnsStoredInstanceWhenExists) {
    using Permanent = Permanent<std::string, int>;
    Permanent storage;

    int* instance = new int;

    auto stored = storage.store("instance", std::unique_ptr<int>(instance));

    BOOST_CHECK_EQUAL(stored.get(), instance);
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(RetainsInstanceWhenUnused) {
    using Permanent = Permanent<std::string, int>;
    Permanent storage;

    int* instance = new int;

    storage.store("instance", std::unique_ptr<int>(instance));

    BOOST_CHECK(storage.get("instance"));
    BOOST_CHECK_EQUAL(storage.get("instance").get(), instance);
}

BOOST_AUTO_TEST_CASE(ErasesExistingInstances) {
    using Permanent = Permanent<std::string, int>;
    Permanent storage;

    int* instance = new int;

    storage.store("instance", std::unique_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(EraseIsNoOpOnNoExistingInstances) {
    using Permanent = Permanent<std::string, int>;
    Permanent storage;

    storage.erase("instance");

    BOOST_CHECK(!storage.get("instance"));
}

BOOST_AUTO_TEST_CASE(ClearErasesAll) {
	using Permanent = Permanent<std::string, int>;
	Permanent storage;

	storage.store("instance", std::unique_ptr<int>(new int));
	storage.store("another", std::unique_ptr<int>(new int));

	storage.clear();

	BOOST_CHECK(!storage.get("instance"));
	BOOST_CHECK(!storage.get("another"));
}

BOOST_AUTO_TEST_CASE(IsStoredReturnsTrueIfInstancePresent) {
    using Permanent = Permanent<std::string, int>;
    Permanent storage;

    int* instance = new int;

    storage.store("instance", std::unique_ptr<int>(instance));

    BOOST_CHECK(storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(IsStoredReturnsFalseIfInstanceNotPresent) {
    using Permanent = Permanent<std::string, int>;
    Permanent storage;

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_CASE(IsStoredReturnsTrueIfInstanceRemoved) {
    using Permanent = Permanent<std::string, int>;
    Permanent storage;

    int* instance = new int;

    storage.store("instance", std::unique_ptr<int>(instance));
    storage.erase("instance");

    BOOST_CHECK(!storage.isStored("instance"));
}

BOOST_AUTO_TEST_SUITE_END(/* PermanentTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* StorageTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* FactoryTestSuite */);

} // anonymous namespace
