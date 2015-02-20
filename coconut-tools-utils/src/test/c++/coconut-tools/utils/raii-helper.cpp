#include <boost/test/auto_unit_test.hpp>

#include <sstream>
#include <iostream>
#include <stdexcept>
#include <functional>

#include "coconut-tools/utils/raii-helper.hpp"

using namespace coconut_tools;

namespace {

class DummyException : public std::exception {
};

void reset(bool& b, bool v) {
    b = v;
}

BOOST_AUTO_TEST_SUITE(RaiiHelperTestSuite);

BOOST_AUTO_TEST_CASE(basicTest) {
    bool b = false;

    {
        utils::RaiiHelper helper(std::bind(&reset, std::ref(b), true));
        BOOST_CHECK_EQUAL(b, false);
    }
    BOOST_CHECK_EQUAL(b, true);
}

BOOST_AUTO_TEST_CASE(resetTest) {
    bool b = false;

    {
        utils::RaiiHelper helper(std::bind(&reset, std::ref(b), true));
        BOOST_CHECK_EQUAL(b, false);
        helper.reset();
    }
    BOOST_CHECK_EQUAL(b, false);
}

BOOST_AUTO_TEST_CASE(exceptionTest) {
    bool b = false;

    try {
        utils::RaiiHelper helper(std::bind(&reset, std::ref(b), true));
        BOOST_CHECK_EQUAL(b, false);
        throw DummyException();
    } catch (const DummyException&) {
        BOOST_CHECK_EQUAL(b, true);
    }
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
