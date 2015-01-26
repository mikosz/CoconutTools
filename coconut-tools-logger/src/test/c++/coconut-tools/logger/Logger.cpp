#include <boost/test/auto_unit_test.hpp>

#include <sstream>
#include <iostream>
#include <functional>

#include <boost/mpl/list.hpp>

#include "coconut-tools/logger/Logger.hpp"
#include "coconut-tools/logger/macros.hpp"
#include "coconut-tools/logger/appender/ConsoleAppender.hpp"
#include "coconut-tools/logger/layout/EmptyLayout.hpp"
#include "coconut-tools/utils/raii-helper.hpp"

namespace {

using namespace coconut_tools;
using namespace coconut_tools::logger;

typedef boost::mpl::list</*Logger,*/ volatile Logger> LoggerTypes;

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);

BOOST_AUTO_TEST_CASE_TEMPLATE(LogsOnRequiredLevelsTest, L, LoggerTypes) {
    std::ostringstream output;

    {
    	auto clogRdbuf = std::clog.rdbuf(output.rdbuf());
        utils::RaiiHelper clogReset([&]() { std::clog.rdbuf(clogRdbuf); });

        L logger(logger::Level::INFO);

        layout::LayoutPtr layout(new layout::EmptyLayout);
        logger.addAppender(appender::AppenderPtr(new appender::ConsoleAppender(layout)));

        logger.log(logger::Level::CRITICAL) << "critical";
        logger.log(logger::Level::ERROR) << "error";
        logger.log(logger::Level::WARNING) << "warning";
        logger.log(logger::Level::INFO) << "info";
        logger.log(logger::Level::DEBUG) << "debug";
        logger.log(logger::Level::TRACE) << "trace";

        logger.critical() << "critical";
        logger.error() << "error";
        logger.warning() << "warning";
        logger.info() << "info";
        logger.debug() << "debug";
        logger.trace() << "trace";
    }

    const std::string EXPECTED =
    	"critical\n"
    	"error\n"
    	"warning\n"
    	"info\n"
		;

    BOOST_CHECK_EQUAL(output.str(), EXPECTED + EXPECTED);
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
