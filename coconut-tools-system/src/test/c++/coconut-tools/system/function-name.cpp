#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/system/function-name.hpp"

using namespace coconut_tools;
using namespace coconut_tools::system;

namespace {

std::string freeFunction(int /* parameter */) {
	return CT_FUNCTION_NAME;
}

class Class {
public:

	std::string classFunction(const char* /* parameter */) const {
		return CT_FUNCTION_NAME;
	}

};

BOOST_AUTO_TEST_SUITE(FunctionNameTestSuite);

BOOST_AUTO_TEST_CASE(TellsFunctionName) {
	BOOST_CHECK(freeFunction(42).find("freeFunction(int)") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(TellsClassFunctionName) {
	BOOST_CHECK(Class().classFunction("").find("Class::classFunction(const char *)") != std::string::npos);
}

BOOST_AUTO_TEST_SUITE_END(/* FunctionNameTestSuite */);

} // anonymous namespace
