#include <boost/test/auto_unit_test.hpp>

#include <iostream>
#include <sstream>
#include <functional>

#include "coconut-tools/utils/raii-helper.hpp"
#include "coconut-tools/logger.hpp"

#include "coconut-tools/logger/appender/DebugWindowAppender.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

namespace {

BOOST_AUTO_TEST_SUITE(LoggerFunctionalTestSuite);

BOOST_AUTO_TEST_CASE(DefaultConfigurationPrintsInfoToStdlog) {
	Logger& logger = LoggerFactory().getSystemLogger();
	
	std::ostringstream output;

	{
		auto clogBuf = std::clog.rdbuf(output.rdbuf());
		utils::RaiiHelper clogReset(
			[&]() { std::clog.rdbuf(clogBuf); }
			);

		// Example of API logging using the log function
		logger.log(Level::TRACE) << "Trace level hidden";
		logger.log(Level::DEBUG) << "Debug level hidden";
		logger.log(Level::INFO) << "Log on level info with implicit context";
		logger.log(Level::WARNING, Context()) << "Log on level info with default context";
		logger.log(Level::ERROR, Context("file", 123, "function")) << "Log on level error with full context";
		logger.log(Level::CRITICAL, LOGGER_CONTEXT()) << "Log on level critical with context from macro";

		// Example of API logging using level specific functions
		logger.trace() << "Trace level hidden";
		logger.debug() << "Debug level hidden";
		logger.info() << "Log on level info with implicit context";
		logger.warning(Context()) << "Log on level info with default context";
		logger.error(Context("file", 123, "function")) << "Log on level error with full context";
		logger.critical(LOGGER_CONTEXT()) << "Log on level critical with context from macro";
	}

	const std::string EXPECTED =
			"Log on level info with implicit context\n"
			"Log on level info with default context\n"
			"Log on level error with full context\n"
			"Log on level critical with context from macro\n"
			;

	BOOST_CHECK_EQUAL(output.str(), EXPECTED + EXPECTED);
}

BOOST_AUTO_TEST_SUITE_END(/* LoggerFunctionalTestSuite */);

} // anonymous namespace