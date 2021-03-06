#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include <algorithm>
#include <sstream>
#include <fstream>

#include <coconut-tools/test-utils/test-utils.hpp>

#include "coconut-tools/serialisation/JSONDeserialiser.hpp"

using namespace coconut_tools;
using namespace coconut_tools::serialisation;

namespace /* anonymous */ {

std::istream* testIs = nullptr;

struct SubStruct {
	int i;
};

struct BasicTypeStruct {
	int i;
	float f;
	std::string s;
	std::vector<SubStruct> ss;
};

void serialise(Deserialiser& s, SubStruct& ss) {
	s >> Deserialiser::Label("int") >> ss.i;
}

void serialise(Deserialiser& s, BasicTypeStruct& bts) {
	s >> Deserialiser::Label("int") >> bts.i;
	s >> Deserialiser::Label("float") >> bts.f;
	s >> Deserialiser::Label("string") >> bts.s;

	std::vector<SubStruct> v(2);
	s >> Deserialiser::Label("sub-objects") >> bts.ss;
}

struct BadStruct {
};

void serialise(Deserialiser& /*s*/, const BadStruct&) {
	assert(testIs != nullptr);
	testIs->setstate(std::ios::badbit);
}

struct FailStruct {
};

void serialise(Deserialiser& /*s*/, const FailStruct&) {
	assert(testIs != nullptr);
	testIs->setstate(std::ios::failbit);
}

BOOST_AUTO_TEST_SUITE(SerialisationJSONDeserialiserTestSuite);

BOOST_FIXTURE_TEST_CASE(ThrowsIfBadPath, coconut_tools::test_utils::ResourcesDirFixture) {
	std::ifstream ifs((resourcesDir() / "no-such-dir" / "file.json").c_str());

	BOOST_CHECK_THROW(JSONDeserialiser s(ifs), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(ThrowsIfFailedRead) {
	const std::string data = "{}";

	std::istringstream iss(data);
	testIs = &iss;

	JSONDeserialiser s(iss);

	auto bs = BadStruct();
	BOOST_CHECK_THROW(s >> bs, std::runtime_error);

	iss.clear();

	auto fs = FailStruct();
	BOOST_CHECK_THROW(s >> fs, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(DeserialisesDataFromJSON) {
	const std::string data =
		"{\n"
		"  \"int\": 123,\n"
		"  \"float\": 1.3,\n"
		"  \"string\": \"value\",\n"
		"  \"sub-objects\": [\n"
		"    { \"int\": 42 },\n"
		"    { \"int\": 42 }\n"
		"  ]\n"
		"}\n"
		;

	std::istringstream iss(data);
	JSONDeserialiser s(iss);

	BasicTypeStruct bts;
	s >> bts;

	BOOST_CHECK_EQUAL(bts.i, 123);
	BOOST_CHECK_EQUAL(bts.f, 1.3f);
	BOOST_CHECK_EQUAL(bts.s, "value");
	BOOST_ASSERT(bts.ss.size() == 2);
	BOOST_CHECK_EQUAL(bts.ss[0].i, 42);
	BOOST_CHECK_EQUAL(bts.ss[1].i, 42);
}

BOOST_AUTO_TEST_CASE(ThrowsOnNonexistingLabel) {
	const std::string data =
		"{\n"
		"  \"int\": 123\n"
		"}\n"
		;

	std::istringstream iss(data);
	JSONDeserialiser s(iss);

	BasicTypeStruct bts;

	BOOST_CHECK_THROW(s >> bts, std::runtime_error); // TODO: custom exception
}

BOOST_AUTO_TEST_SUITE_END(/* SerialisationJSONDeserialiserTestSuite */);

} // anonymous namespace
