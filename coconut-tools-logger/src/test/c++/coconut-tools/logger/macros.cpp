#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/logger/macros.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

namespace /* anonymous */ {

std::string expressionFailsBoostTestCheck() {
	BOOST_CHECK(false);
	return "";
}

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);
BOOST_AUTO_TEST_SUITE(MacrosTestSuite);

namespace external_context {

CT_LOGGER_CATEGORY("EXTERNAL");

namespace local_context {

CT_LOGGER_CATEGORY("LOCAL");

BOOST_AUTO_TEST_CASE(LogsUsingCategorySpecifiedInLocalContext) {

}

BOOST_AUTO_TEST_CASE(LogsUsingCategorySpecifiedInScopedContext) {
	CT_LOGGER_LOCAL_CATEGORY("INTERNAL");
}

} // namespace local_context
} // namespace external_context

BOOST_AUTO_TEST_CASE(ExpressionsInLoggingInstructionsAreNotEvaluatedIfLevelUnderLoggerLevel) {
	CT_LOGGER_LOCAL_CATEGORY(""); // TODO: w00t w00t w00t czy da sie zrobic, zeby nie podawac kategorii jak sie nie chce?

	BOOST_ASSERT((CT_LOGGER)->getLevel() == Level::INFO);

	CT_LOG_TRACE << expressionFailsBoostTestCheck();
	CT_LOG_DEBUG << expressionFailsBoostTestCheck();
	CT_LOG_INFO << expressionFailsBoostTestCheck();
	CT_LOG_WARNING << "to musi byc sprawdzone";
	CT_LOG_ERROR << "";
	CT_LOG_CRITICAL << "";
}

BOOST_AUTO_TEST_SUITE_END(/* MacrosTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LoggerTestSuite */);

} // anonymous namespace
