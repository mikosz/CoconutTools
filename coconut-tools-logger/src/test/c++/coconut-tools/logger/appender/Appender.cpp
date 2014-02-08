#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/logger/appender/Appender.hpp"
#include "coconut-tools/logger/layout/EmptyLayout.hpp"
#include "coconut-tools/test-utils/GMockFixture.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

namespace {

class ConcreteAppender : public Appender {
public:

	ConcreteAppender(layout::LayoutPtr layout) :
		Appender(layout) {
	}

	MOCK_METHOD1(doAppend, void (const std::string&));

};

class ConcreteLayout : public layout::Layout {
public:

	MOCK_METHOD3(format, std::string (Level, const Context&, const std::string&));

};

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);
BOOST_AUTO_TEST_SUITE(AppenderTestSuite);
BOOST_FIXTURE_TEST_SUITE(AppenderTestSuite, test_utils::GMockFixture);

BOOST_AUTO_TEST_CASE(CallsSubclassDoAppend) {
	const std::string testString("test string");

	layout::LayoutPtr layout(new layout::EmptyLayout);
	ConcreteAppender appender(layout);

	EXPECT_CALL(appender, doAppend(testString + '\n'));

	appender.append(Level::INFO, Context(), testString);
}

BOOST_AUTO_TEST_CASE(UsesProvidedLayout) {
	const std::string testString("test string");
	const std::string layoutApplicationResult("test string lain out");

	layout::LayoutPtr layout(new ConcreteLayout);
	ConcreteAppender appender(layout);

	EXPECT_CALL(
			dynamic_cast<ConcreteLayout&>(*layout),
			format(Level(Level::INFO), testing::_, testString)
			).WillOnce(testing::Return(layoutApplicationResult));
	EXPECT_CALL(appender, doAppend(layoutApplicationResult));

	appender.append(Level::INFO, Context(), testString);
}

BOOST_AUTO_TEST_SUITE_END(/* AppenderTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* AppenderTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LoggerTestSuite */);

} // anonymous namespace
