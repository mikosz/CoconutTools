#include <boost/test/auto_unit_test.hpp>

#include <boost/filesystem/path.hpp>

#include "coconut-tools/utils/raii-helper.hpp"
#include "coconut-tools/logger/macros.hpp"
#include "coconut-tools/test-utils/test-utils.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

namespace /* anonymous */ {

class CategoryPrintingLayout : public layout::Layout {
public:

	std::string format(Level, const Context& context, const std::string&) override {
		return context.category;
	}

};

const utils::Null CATEGORY_PRINTING_LAYOUT_REGISTRAR =
	GlobalLoggerFactory::instance()->appenderFactory().layoutFactory().registerType<CategoryPrintingLayout>("CategoryPrintingLayout");

void createCategoryPrintingLoggerConfigurationFile(const boost::filesystem::path& path) {
	test_utils::writeToFile(
		path,
		"<root-logger>"
		"  <level>info</level>"
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
		"    <type>CategoryPrintingLayout</type>"
		"  </layout>"
		"</layouts>"
		);
}

std::string expressionFailsBoostTestCheck() {
	BOOST_FAIL("An unwanted expression was evaluated");
	return "";
}

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);
BOOST_AUTO_TEST_SUITE(MacrosTestSuite);

namespace external_context {

CT_LOGGER_CATEGORY("EXTERNAL");

namespace local_context {

CT_LOGGER_CATEGORY("LOCAL");

BOOST_FIXTURE_TEST_CASE(LogsUsingCategorySpecifiedInLocalContext, test_utils::ResourcesDirFixture) {
	createCategoryPrintingLoggerConfigurationFile(resourcesDir() / "coconut-tools-logger.cfg.xml");

	std::ostringstream output;

	{
		auto clogRdbuf = std::clog.rdbuf(output.rdbuf());
		utils::RaiiHelper clogReset(
			[&]() { std::clog.rdbuf(clogRdbuf); }
		);

		CT_LOG_INFO << "";

		BOOST_CHECK_EQUAL(output.str(),
			"LOCALes\n"
			);
	}
}

BOOST_AUTO_TEST_CASE(LogsUsingCategorySpecifiedInScopedContext) {
	CT_LOGGER_LOCAL_CATEGORY("INTERNAL");
}

} // namespace local_context
} // namespace external_context

BOOST_AUTO_TEST_CASE(ExpressionsInLoggingInstructionsAreNotEvaluatedIfLevelUnderLoggerLevel) {
	CT_LOGGER_LOCAL_CATEGORY(""); // TODO: w00t w00t w00t czy da sie zrobic, zeby nie podawac kategorii jak sie nie chce?

	BOOST_ASSERT((CT_LOGGER)->getLevel() == Level::INFO);

	std::ostringstream output;

	{
		auto clogRdbuf = std::clog.rdbuf(output.rdbuf());
		utils::RaiiHelper clogReset(
			[&]() { std::clog.rdbuf(clogRdbuf); }
		);

		CT_LOG_TRACE << expressionFailsBoostTestCheck();
		CT_LOG_DEBUG << expressionFailsBoostTestCheck();
		CT_LOG_INFO << "info";
		CT_LOG_WARNING << "warning";
		CT_LOG_ERROR << "error";
		CT_LOG_CRITICAL << "critical";

		BOOST_CHECK_EQUAL(output.str(),
			"info\n"
			"warning\n"
			"error\n"
			"critical\n"
			);
	}
}

BOOST_AUTO_TEST_SUITE_END(/* MacrosTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LoggerTestSuite */);

} // anonymous namespace
