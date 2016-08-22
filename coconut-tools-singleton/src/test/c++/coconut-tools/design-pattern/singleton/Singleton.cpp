#include <boost/test/auto_unit_test.hpp>

#include <memory>

#include "coconut-tools/design-pattern/singleton/Singleton.hpp"
#include "coconut-tools/design-pattern/locking-policy.hpp"

namespace {

using namespace coconut_tools;
using namespace coconut_tools::design_pattern;
using namespace coconut_tools::design_pattern::singleton;

BOOST_AUTO_TEST_SUITE(DesignPatternTestSuite);
BOOST_AUTO_TEST_SUITE(SingletonTestSuite);
BOOST_AUTO_TEST_SUITE(SingletonTestSuite);

class SingletonClass : public Singleton<SingletonClass, UniqueMutexLockingPolicy> {
};

BOOST_AUTO_TEST_CASE(CreatesSingletonInstance) {
	BOOST_CHECK_EQUAL(SingletonClass::instance().get(), SingletonClass::instance().get());
}

class ReplacedSingletonClass : public Singleton<ReplacedSingletonClass, UniqueMutexLockingPolicy> {
};

BOOST_AUTO_TEST_CASE(ReplacesExistingInstance) {
	ReplacedSingletonClass* constructed = new ReplacedSingletonClass;
	ReplacedSingletonClass* instance = ReplacedSingletonClass::instance().get();

	BOOST_CHECK_NE(constructed, instance);

	ReplacedSingletonClass::setInstance(std::unique_ptr<ReplacedSingletonClass>(constructed));

	BOOST_CHECK_EQUAL(constructed, ReplacedSingletonClass::instance().get());
	BOOST_CHECK_NE(instance, ReplacedSingletonClass::instance().get());
}

class ProvidedSingletonClass : public Singleton<ProvidedSingletonClass, UniqueMutexLockingPolicy> {
};

BOOST_AUTO_TEST_CASE(UsesProvidedInstance) {
	ProvidedSingletonClass* constructed = new ProvidedSingletonClass;
	ProvidedSingletonClass::setInstance(std::unique_ptr<ProvidedSingletonClass>(constructed));

	BOOST_CHECK_EQUAL(constructed, ProvidedSingletonClass::instance().get());
}

BOOST_AUTO_TEST_SUITE_END(/* SingletonTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* SingletonTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* DesignPatternTestSuite */);

} // anonymous namespace
