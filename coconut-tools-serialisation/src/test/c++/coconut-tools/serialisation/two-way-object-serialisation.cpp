#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include <sstream>
#include <unordered_map>

#include "coconut-tools/serialisation/BinarySerialiser.hpp"
#include "coconut-tools/serialisation/BinaryDeserialiser.hpp"
#include "coconut-tools/serialisation/JSONSerialiser.hpp"
// #include "coconut-tools/serialisation/JSONDeserialiser.hpp"
#include "coconut-tools/serialisation/make-serialisable-macro.hpp"
#include "coconut-tools/serialisation/common-serialisers.hpp"

using namespace coconut_tools;
using namespace coconut_tools::serialisation;

namespace /* anonymous */ {

struct SubStruct {
	int i;

	SubStruct()
	{
	}

	SubStruct(int i) :
		i(i)
	{
	}

	bool operator==(const SubStruct& rhs) const {
		return i == rhs.i;
	}
};

struct BasicTypeStruct {
	int i;
	float f;
	std::string s;
	bool b;
	std::vector<SubStruct> v;
};

CCN_MAKE_SERIALISABLE(SerialiserType, s, SubStruct, ss) {
	s(SerialiserType::Label("i"), ss.i);
}

CCN_MAKE_SERIALISABLE(SerialiserType, s, BasicTypeStruct, bts) {
	s(SerialiserType::Label("int"), bts.i);
	s(SerialiserType::Label("float"), bts.f);
	s(SerialiserType::Label("string"), bts.s);
	s(SerialiserType::Label("bool"), bts.b);

	std::vector<SubStruct> v(2);
	s(SerialiserType::Label("sub-objects"), bts.v);
}

BOOST_AUTO_TEST_SUITE(SerialisationTwoWaySerialisationTestSuite);

BOOST_AUTO_TEST_CASE(SerialiseAndDeserialiseToBinary) { // TODO: make templated test for JSON versions too (when JSON deserialisation works)
	std::stringstream ss;

	BasicTypeStruct toSerialise;
	toSerialise.i = 42;
	toSerialise.f = 4.2f;
	toSerialise.s = "fourty two";
	toSerialise.b = false;
	toSerialise.v = {
		SubStruct(0),
		SubStruct(1)
		};

	{
		BinarySerialiser serialiser(ss);
		serialiser << toSerialise;
	}

	BasicTypeStruct deserialised;

	{
		BinaryDeserialiser deserialiser(ss);
		deserialiser >> deserialised;
	}

	BOOST_CHECK_EQUAL(toSerialise.i, deserialised.i);
	BOOST_CHECK_EQUAL(toSerialise.f, deserialised.f);
	BOOST_CHECK_EQUAL(toSerialise.s, deserialised.s);
	BOOST_CHECK_EQUAL(toSerialise.b, deserialised.b);
	BOOST_CHECK(toSerialise.v == deserialised.v);
}

BOOST_AUTO_TEST_CASE(SerialisesUnorderedMaps) { // TODO: see above
	auto map = std::unordered_map<std::string, int>();
	map.emplace("one", 1);
	map.emplace("forty-two", 42);

	std::stringstream ss;

	{
		BinarySerialiser serialiser(ss);
		serialiser << map;
	}

	auto deserialised = decltype(map)();
	
	{
		BinaryDeserialiser deserialiser(ss);
		deserialiser >> deserialised;
	}

	BOOST_CHECK(map == deserialised);
}

BOOST_AUTO_TEST_SUITE_END(/* SerialisationTwoWaySerialisationTestSuite */);

} // anonymous namespace
