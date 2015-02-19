#include <boost/test/auto_unit_test.hpp>

#include <sstream>
#include <iostream>
#include <functional>

#include "coconut-tools/logger/appender/ConsoleAppender.hpp"
#include "coconut-tools/logger/layout/EmptyLayout.hpp"
#include "coconut-tools/utils/raii-helper.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

namespace {

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);
BOOST_AUTO_TEST_SUITE(AppenderTestSuite);
BOOST_AUTO_TEST_SUITE(ConsoleAppenderTestSuite);

BOOST_AUTO_TEST_CASE(WritesToClog) {
	const std::string testString("test string");

    std::ostringstream output;

    {
		auto clogRdbuf = std::clog.rdbuf(output.rdbuf());
        utils::RaiiHelper clogReset(
			[&]() { std::clog.rdbuf(clogRdbuf); }
			);

        layout::LayoutSharedPtr layout(new layout::EmptyLayout);
    	ConsoleAppender appender(layout);

    	appender.append(Level::INFO, Context(), testString);

    	BOOST_CHECK_EQUAL(output.str(), layout->format(Level::INFO, Context(), testString));
    }
}

BOOST_AUTO_TEST_SUITE_END(/* ConsoleAppenderTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* AppenderTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LoggerTestSuite */);

} // anonymous namespace
