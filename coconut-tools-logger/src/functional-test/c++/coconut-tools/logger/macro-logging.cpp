#include <boost/test/auto_unit_test.hpp>

#include <sstream>

#include "coconut-tools/test-utils/test-utils.hpp"
#include "coconut-tools/utils/raii-helper.hpp"
#include "coconut-tools/logger.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

namespace {

BOOST_AUTO_TEST_SUITE(LoggerFunctionalTestSuite);

BOOST_AUTO_TEST_CASE(DefaultConfigurationPrintsInfoToStdlog) {
	std::ostringstream output;

	{
		auto clogBuf = std::clog.rdbuf(output.rdbuf());
		utils::RaiiHelper clogReset(
			[&]() { std::clog.rdbuf(clogBuf); }
		);

		CT_LOGGER_LOCAL_CATEGORY("MACRO_LOGGING.DefaultConfigurationPrintsInfoToStdlog");

		CT_LOG_TRACE << "Won't be logged";
		CT_LOG_DEBUG << "Won't be logged";
		CT_LOG_INFO << "Will log info";
		CT_LOG_WARNING << "Will log warning";
		CT_LOG_ERROR << "Will log error";
		CT_LOG_CRITICAL << "Will log critical";
	}

	const std::string EXPECTED =
		"Will log info\n"
		"Will log warning\n"
		"Will log error\n"
		"Will log critical\n"
		;

	BOOST_CHECK_EQUAL(output.str(), EXPECTED);
}

BOOST_FIXTURE_TEST_CASE(LoggerCategorySetsAppropriateLogger, test_utils::ResourcesDirFixture) {
	std::istringstream iss(
		"<root-logger>"
		"  <level>info</level>"
		"  <appenders>"
		"    <appender>appender-id</appender>"
		"  </appenders>"
		"</root-logger>"
		"<loggers>"
		"  <logger>"
		"    <id>SPECIFIC</id>"
		"    <level>debug</level>"
		"  </logger>"
		"</loggers>"
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

	const auto configurationPath = resourcesDir() / "configuration.xml";
	test_utils::writeToFile(configurationPath, iss.str());
	GlobalLoggerFactory::instance()->reloadConfiguration(configurationPath);
	utils::RaiiHelper resetConfiguration([]() { GlobalLoggerFactory::instance()->reloadConfiguration(); });

	std::ostringstream output;

	{
		auto clogBuf = std::clog.rdbuf(output.rdbuf());
		utils::RaiiHelper clogReset(
			[&]() { std::clog.rdbuf(clogBuf); }
		);

		CT_LOGGER_LOCAL_CATEGORY("GENERAL");

		CT_LOG_DEBUG << "This shan't be logged";

		{
			CT_LOGGER_LOCAL_CATEGORY("SPECIFIC");
			CT_LOG_DEBUG << "This shall be logged";
		}

		CT_LOG_DEBUG << "This shan't be logged also";
	}

	const std::string EXPECTED =
		"This shall be logged\n"
		;

	BOOST_CHECK_EQUAL(output.str(), EXPECTED);
}

namespace fully_fledged_logger_configuration_test {

CT_LOGGER_CATEGORY("COCONUT_TOOLS.LOGGER.FUNCTIONAL_TEST");

namespace some_verbose_module {

CT_LOGGER_CATEGORY("COCONUT_TOOLS.LOGGER.FUNCTIONAL_TEST.SOME_VERBOSE_MODULE");

void someFunction() {
	CT_LOG_TRACE << "Trace message in verbose module";
}

} // namespace some_verbose_module

BOOST_FIXTURE_TEST_CASE(FullyFledgedLoggerConfiguration, test_utils::ResourcesDirFixture) {
	std::istringstream iss(
		"<root-logger>"
		"  <level>info</level>"
		"  <appenders>"
		"    <appender>console</appender>"
		"  </appenders>"
		"</root-logger>"
		"<loggers>"
		"  <logger>"
		"    <id>COCONUT_TOOLS.LOGGER.FUNCTIONAL_TEST</id>"
		"    <level>debug</level>"
		"    <appenders>"
		"      <appender>file</appender>"
		"    </appenders>"
		"  </logger>"
		"  <logger>"
		"    <id>COCONUT_TOOLS.LOGGER.FUNCTIONAL_TEST.SOME_VERBOSE_MODULE</id>"
		"    <level>trace</level>"
		"  </logger>"
		"</loggers>"
		"<appenders>"
		"  <appender>"
		"    <id>console</id>"
		"    <level>info</level>"
		"    <type>coconut_tools::logger::appender::ConsoleAppender</type>"
		"    <layout>basic</layout>"
		"  </appender>"
		"  <appender>"
		"    <id>file</id>"
		"    <level>trace</level>"
		"    <type>coconut_tools::logger::appender::FileAppender</type>"
		"    <layout>detailed</layout>"
		"    <log-file>"
		"  </appender>"
		"</appenders>"
		"<layouts>"
		"  <layout>"
		"    <id>basic</id>"
		"    <type>coconut_tools::logger::layout::BasicLayout</type>"
		"  </layout>"
		"  <layout>"
		"    <id>detailed</id>"
		"    <type>coconut_tools::logger::layout::DetailedLayout</type>"
		"  </layout>"
		"</layouts>"
		);

	const auto configurationPath = resourcesDir() / "configuration.xml";
	test_utils::writeToFile(configurationPath, iss.str());
	GlobalLoggerFactory::instance()->reloadConfiguration(configurationPath);
	utils::RaiiHelper resetConfiguration([]() { GlobalLoggerFactory::instance()->reloadConfiguration(); });

	std::ostringstream consoleOutput;

	{
		auto clogBuf = std::clog.rdbuf(consoleOutput.rdbuf());
		utils::RaiiHelper clogReset(
			[&]() { std::clog.rdbuf(clogBuf); }
		);

		CT_LOG_DEBUG << "Debug not logged on console, but logged in file";
		CT_LOG_TRACE << "Trace not logged in COCONUT_TOOLS.LOGGER.FUNCTIONAL_TEST";
		CT_LOG_INFO << "Info logged everywhere";

		some_verbose_module::someFunction();
	}

	const std::string CONSOLE_EXPECTED =
		"COCONUT_TOOLS.LOGGER.FUNCTIONAL_TEST [INFO] - Info logged everywhere\n"
		"COCONUT_TOOLS.LOGGER.FUNCTIONAL_TEST.SOME_VERBOSE_MODULE [TRACE] - Trace message in verbose module\n"
		;

	BOOST_CHECK_EQUAL(consoleOutput.str(), CONSOLE_EXPECTED);
}

} // namespace fully_fledged_logger_configuration_test

BOOST_AUTO_TEST_SUITE_END(/* LoggerFunctionalTestSuite */);

} // anonymous namespace
