#include <sstream>
#include <iostream>

#include <boost/test/auto_unit_test.hpp>
#include <boost/bind.hpp>

#include "logger/Logger.hpp"
#include "logger/macros.hpp"
#include "utils/raii-helper.hpp"

using namespace CoconutTools;

namespace {

template <class L>
void basicTest() {
    std::ostringstream output;

    {
        utils::RaiiHelper cerrReset(
                boost::bind(&std::ostream::rdbuf, boost::ref(std::cerr), std::cerr.rdbuf(output.rdbuf())));

        L logger(logger::Level::INFO);
        logger.log(logger::Context(logger::Level::CRITICAL)) << "critical";
        logger.log(logger::Context(logger::Level::ERROR)) << "error";
        logger.log(logger::Context(logger::Level::WARNING)) << "warning";
        logger.log(logger::Context(logger::Level::INFO)) << "info";
        logger.log(logger::Context(logger::Level::DEBUG)) << "debug";
        logger.log(logger::Context(logger::Level::TRACE)) << "trace";
    }

    BOOST_CHECK_EQUAL(output.str(), "critical\nerror\nwarning\ninfo\n");
}

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);

BOOST_AUTO_TEST_CASE(basicSTTest) {
    basicTest<logger::Logger>();
}

BOOST_AUTO_TEST_CASE(basicMTTest) {
    basicTest<volatile logger::Logger>();
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
