#include <boost/test/auto_unit_test.hpp>

#include <iostream>
#include <sstream>
#include <functional>

#include "coconut-tools/utils/raii-helper.hpp"

#include "coconut-tools/configuration/readers/HierarchicalConfigurationReader.hpp"
#include "coconut-tools/configuration/parsers/XMLParser.hpp"

#include "coconut-tools/logger/LoggerFactory.hpp"
#include "coconut-tools/logger/SystemLogger.hpp"
#include "coconut-tools/logger/macros.hpp"

#include "coconut-tools/logger.hpp"

#include "coconut-tools/logger/appender/DebugWindowAppender.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

namespace {

BOOST_AUTO_TEST_SUITE(LoggerFunctionalTestSuite);

BOOST_AUTO_TEST_CASE(DefaultConfigurationPrintsInfoToStdlog) {
	Logger& logger = *SystemLogger::instance();
	
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
		logger.log(Level::ERROR, Context("category", "file", 123, "function")) << "Log on level error with full context";
		{
			CT_LOGGER_LOCAL_CATEGORY("category");
			logger.log(Level::CRITICAL, CT_LOGGER_CONTEXT) << "Log on level critical with context from macro";
		}

		// Example of API logging using level specific functions
		logger.trace() << "Trace level hidden";
		logger.debug() << "Debug level hidden";
		logger.info() << "Log on level info with implicit context";
		logger.warning(Context()) << "Log on level info with default context";
		logger.error(Context("category", "file", 123, "function")) << "Log on level error with full context";
		{
			CT_LOGGER_LOCAL_CATEGORY("category");
			logger.critical(CT_LOGGER_CONTEXT) << "Log on level critical with context from macro";
		}
	}

	const std::string EXPECTED =
			"Log on level info with implicit context\n"
			"Log on level info with default context\n"
			"Log on level error with full context\n"
			"Log on level critical with context from macro\n"
			;

	BOOST_CHECK_EQUAL(output.str(), EXPECTED + EXPECTED);
}

BOOST_AUTO_TEST_CASE(LoggerFactoryProducesConfiguredLoggers) {
	auto configurationData = coconut_tools::configuration::hierarchical::HierarchicalConfiguration::create();

	std::istringstream iss(
		"<root-logger>"
		"  <level>error</level>"
		"  <appender>appender-id</appender>"
		"</root-logger>"
		"<appenders>"
		"  <appender>"
		"    <id>appender-id</id>"
		"    <type>coconut_tools::logger::appender::ConsoleAppender</type>"
		"    <layout>layout-id</layout>"
		"  </appender>"
		"</appenders>"
		"<layouts>"
		"  <layout>"
		"    <id>layout-id</id>"
		"    <type>coconut_tools::logger::layout::EmptyLayout</type>"
		"  </layout>"
		"</layouts>"
		);

	coconut_tools::configuration::readers::HierarchicalConfigurationReader().read(
		coconut_tools::configuration::parsers::XMLParser(),
		iss,
		configurationData.get()
		);

	logger::configuration::LoggerConfigurationSharedPtr config(
		std::make_shared<logger::configuration::LoggerConfiguration>(configurationData));

	LoggerFactory loggerFactory(config);

	std::ostringstream output;

	{
		auto clogBuf = std::clog.rdbuf(output.rdbuf());
		utils::RaiiHelper clogReset(
			[&]() { std::clog.rdbuf(clogBuf); }
		);

		Logger& logger = *loggerFactory.create("id");

		// Example of API logging using level specific functions
		logger.trace() << "Trace level hidden";
		logger.debug() << "Debug level hidden";
		logger.info() << "Info level hidden";
		logger.warning() << "Warning level hidden";
		logger.error() << "Log on level error with implicit context";
		logger.critical() << "Log on level critical with implicit context";
	}

	const std::string EXPECTED =
		"Log on level error with implicit context\n"
		"Log on level critical with implicit context\n"
		;

	BOOST_CHECK_EQUAL(output.str(), EXPECTED);
}

BOOST_AUTO_TEST_SUITE_END(/* LoggerFunctionalTestSuite */);

} // anonymous namespace
