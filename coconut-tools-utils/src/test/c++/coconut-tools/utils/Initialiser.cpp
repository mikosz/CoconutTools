#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/utils/Initialiser.hpp"
#include "coconut-tools/utils/Initialisable.hpp"

using namespace coconut_tools;
using namespace coconut_tools::utils;

namespace /* anonymous */ {

class MockInitialisable : public utils::Initialisable<MockInitialisable> {
public:

	MockInitialisable() :
		initialised_(false)
	{
	}

	void doInitialise() override {
		initialised_ = true;
	}

	bool initialised() const {
		return initialised_;
	}

 private:

	bool initialised_;

};

class MockInitialisableIntString :
	public utils::Initialisable<MockInitialisableIntString, int, const std::string&>
{
public:

	MockInitialisableIntString() :
		initialised_(false)
	{
	}

	void doInitialise(int i, const std::string& s) override {
		initialised_ = true;
		i_ = i;
		s_ = s;
	}

	bool initialised() const {
		return initialised_;
	}

	int i() const {
		return i_;
	}

	const std::string& s() const {
		return s_;
	}

private:

	bool initialised_;

	int i_;

	std::string s_;

};


BOOST_AUTO_TEST_SUITE(InitialiserTestSuite);

BOOST_AUTO_TEST_CASE(CallsInitialiseWithoutArguments) {
	auto initialiser = MockInitialisable::Initialiser::createInitialisable<MockInitialisable>();
	auto initialised = initialiser.initialise();

	BOOST_CHECK(initialised->initialised());
}

BOOST_AUTO_TEST_CASE(CallsInitialiseWithArguments) {
	auto initialiser = MockInitialisableIntString::Initialiser::createInitialisable<MockInitialisableIntString>();
	auto initialised = initialiser.initialise(123, "some text");

	BOOST_CHECK(initialised->initialised());
	BOOST_CHECK_EQUAL(initialised->i(), 123);
	BOOST_CHECK_EQUAL(initialised->s(), "some text");
}

BOOST_AUTO_TEST_CASE(CantInitialisedAnInitialisedObject) {
	auto initialiser = MockInitialisable::Initialiser::createInitialisable<MockInitialisable>();
	initialiser.initialise();
	
	BOOST_CHECK_THROW(initialiser.initialise(), utils::ObjectAlreadyInitialised);
}

BOOST_AUTO_TEST_SUITE_END(/* InitialiserTestSuite */);

} // anonymous namespace
