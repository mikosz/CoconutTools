#include <boost/test/auto_unit_test.hpp>

#include <string>

#include <boost/function.hpp>

#include "design-pattern/Factory.hpp"

namespace {

using namespace coconut_tools;
using namespace coconut_tools::design_pattern;

class IntReturningFunctor {
public:

    typedef int return_value;

    IntReturningFunctor(int i) :
        i_(i) {
    }

    int operator() () const {
        return i_;
    }

private:

    int i_;

};

BOOST_AUTO_TEST_SUITE(FactoryTestSuite);

BOOST_AUTO_TEST_CASE(CallsCreatorsTest) {
    Factory<std::string, int, boost::function<int ()>, ExceptionThrowingErrorPolicy> f;
    f.registerCreator("1", IntReturningFunctor(1));
    f.registerCreator("2", IntReturningFunctor(2));
    BOOST_CHECK_EQUAL(f.create("1"), 1);
    BOOST_CHECK_EQUAL(f.create("2"), 2);
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
