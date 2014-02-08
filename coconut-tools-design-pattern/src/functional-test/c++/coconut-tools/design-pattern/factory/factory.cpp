#include <boost/test/auto_unit_test.hpp>

#include <boost/bind.hpp>

#include "coconut-tools/design-pattern/factory.hpp"

using namespace coconut_tools::design_pattern;

namespace {

class AbstractClass {
public:

	virtual ~AbstractClass() {
	}

	virtual const std::string& id() const = 0;

};

class ConcreteClass1 : public AbstractClass {
public:

	static const std::string ID;

	const std::string& id() const {
		return ID;
	}

};

const std::string ConcreteClass1::ID("ConcreteClass1");

class ConcreteClass2 : public AbstractClass {
public:

	static const std::string ID;

	const std::string& id() const {
		return ID;
	}

};

const std::string ConcreteClass2::ID("ConcreteClass2");

std::auto_ptr<int> createInt(int value) {
	return std::auto_ptr<int>(new int(value));
}

BOOST_AUTO_TEST_SUITE(DesignPatternTestSuite);
BOOST_AUTO_TEST_SUITE(FactoryFunctionalTestSuite);

BOOST_AUTO_TEST_CASE(RegisteredTypesCreatingFactory) {
	typedef Factory<
				std::string,
				AbstractClass,
				NoStorage,
				NewCreator,
				NoLockingPolicy,
				ExceptionThrowingErrorPolicy
			> Factory;

	Factory f;

	f.registerCreator(ConcreteClass1::ID, NewCreator<AbstractClass>::makeCreator<ConcreteClass1>());
	f.registerCreator(ConcreteClass2::ID, NewCreator<AbstractClass>::makeCreator<ConcreteClass2>());

	BOOST_CHECK_THROW(
			f.registerCreator(ConcreteClass1::ID, NewCreator<AbstractClass>::makeCreator<ConcreteClass1>()),
			CreatorAlreadyRegistered<std::string>);
	BOOST_CHECK_THROW(
			f.registerCreator(ConcreteClass2::ID, NewCreator<AbstractClass>::makeCreator<ConcreteClass2>()),
			CreatorAlreadyRegistered<std::string>);

	std::auto_ptr<AbstractClass> instance1 = f.create(ConcreteClass1::ID);
	std::auto_ptr<AbstractClass> instance2 = f.create(ConcreteClass2::ID);

	BOOST_CHECK_EQUAL(instance1->id(), ConcreteClass1::ID);
	BOOST_CHECK_EQUAL(instance2->id(), ConcreteClass2::ID);

	f.unregisterCreator(ConcreteClass1::ID);
	f.unregisterCreator(ConcreteClass2::ID);

	BOOST_CHECK_THROW(f.create(ConcreteClass1::ID), NoSuchType<std::string>);
	BOOST_CHECK_THROW(f.create(ConcreteClass2::ID), NoSuchType<std::string>);
}

BOOST_AUTO_TEST_CASE(RegisteredFunctorsCreatingFactory) {
	typedef Factory<
				int,
				int,
				NoStorage,
				FunctorCreator,
				NoLockingPolicy,
				ExceptionThrowingErrorPolicy
			> Factory;

	Factory f;

	f.registerCreator(1, FunctorCreator<int>(boost::bind(&createInt, 1)));
	f.registerCreator(2, FunctorCreator<int>(boost::bind(&createInt, 2)));

	BOOST_CHECK_THROW(
			f.registerCreator(1, FunctorCreator<int>(boost::bind(&createInt, 1))),
			CreatorAlreadyRegistered<int>);

	BOOST_CHECK_EQUAL(*f.create(1), 1);
	BOOST_CHECK_EQUAL(*f.create(2), 2);

	f.unregisterCreator(1);
	f.unregisterCreator(2);

	BOOST_CHECK_THROW(f.create(1), NoSuchType<int>);
	BOOST_CHECK_THROW(f.create(2), NoSuchType<int>);
}

BOOST_AUTO_TEST_CASE(CachingFactory) {
	typedef Factory<
				int,
				int,
				PermanentStorage,
				FunctorCreator,
				NoLockingPolicy,
				ExceptionThrowingErrorPolicy
			> Factory;

	Factory f;

	f.registerCreator(1, FunctorCreator<int>(boost::bind(&createInt, 1)));
	f.registerCreator(2, FunctorCreator<int>(boost::bind(&createInt, 2)));

	boost::shared_ptr<int> one = f.create(1);
	boost::shared_ptr<int> two = f.create(2);

	boost::shared_ptr<int> oneCopy = f.create(1);
	boost::shared_ptr<int> twoCopy = f.create(2);

	BOOST_CHECK_EQUAL(one.get(), oneCopy.get());
	BOOST_CHECK_EQUAL(two.get(), twoCopy.get());
	BOOST_CHECK(one.get() != two.get());
}

BOOST_AUTO_TEST_CASE(ThreadSafeFactory) {
	typedef volatile Factory<
				int,
				int,
				PermanentStorage,
				FunctorCreator,
				UniqueMutexLockingPolicy,
				ExceptionThrowingErrorPolicy
			> Factory;

	Factory f;

	f.registerCreator(1, FunctorCreator<int>(boost::bind(&createInt, 1)));
	f.registerCreator(2, FunctorCreator<int>(boost::bind(&createInt, 2)));

	boost::shared_ptr<int> one = f.create(1);
	boost::shared_ptr<int> two = f.create(2);

	boost::shared_ptr<int> oneCopy = f.create(1);
	boost::shared_ptr<int> twoCopy = f.create(2);

	BOOST_CHECK_EQUAL(one.get(), oneCopy.get());
	BOOST_CHECK_EQUAL(two.get(), twoCopy.get());
	BOOST_CHECK(one.get() != two.get());
}

BOOST_AUTO_TEST_SUITE_END(/* FactoryFunctionalTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* DesignPatternTestSuite */);

} // anonymous namespace
