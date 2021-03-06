#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include <sstream>
#include <iostream>

#include <boost/bind.hpp>

#include "coconut-tools/logger/appender/FileAppender.hpp"
#include "coconut-tools/logger/layout/EmptyLayout.hpp"
#include "coconut-tools/logger/log-file/LogFile.hpp"

#include "coconut-tools/test-utils/GMockFixture.hpp"
#include "coconut-tools/test-utils/test-utils.hpp"

#include "coconut-tools/utils/raii-helper.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

namespace {

class MockLogFile : public log_file::LogFile {
public:

	MockLogFile(const boost::filesystem::path& path) :
		log_file::LogFile(path, true) {
	}

	MOCK_METHOD1(write, void (const std::string& message));

};

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);
BOOST_AUTO_TEST_SUITE(AppenderTestSuite);
BOOST_FIXTURE_TEST_SUITE(FileAppenderTestSuite, test_utils::GMockFixture);

BOOST_FIXTURE_TEST_CASE(WritesToFile, test_utils::ResourcesDirFixture) {
	const std::string testString("test string");

	layout::LayoutSharedPtr layout(new layout::EmptyLayout);
	log_file::LogFileSharedPtr logFile(new MockLogFile(resourcesDir() / "log-file.txt"));
	FileAppender appender(Level::TRACE, layout, logFile);

	EXPECT_CALL(
			dynamic_cast<MockLogFile&>(*logFile),
			write(layout->format(Level(Level::INFO), Context(), testString))
			);

	appender.append(Level::INFO, Context(), testString);
}

BOOST_AUTO_TEST_SUITE_END(/* FileAppenderTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* AppenderTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LoggerTestSuite */);

} // anonymous namespace
