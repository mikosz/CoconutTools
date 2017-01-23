#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/logger/log-file/LogFile.hpp"
#include "coconut-tools/test-utils/test-utils.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::log_file;

namespace {

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);
BOOST_AUTO_TEST_SUITE(LogFileTestSuite);
BOOST_FIXTURE_TEST_SUITE(LogFileTestSuite, test_utils::ResourcesDirFixture);

BOOST_AUTO_TEST_CASE(CreatesNewLogFileWhenNoneExists) {
	LogFile overwriteOn(resourcesDir() / "overwrite-on", true);
	BOOST_CHECK(boost::filesystem::exists(resourcesDir() / "overwrite-on"));

	LogFile overwriteOff(resourcesDir() / "overwrite-off", false);
	BOOST_CHECK(boost::filesystem::exists(resourcesDir() / "overwrite-off"));
}

BOOST_AUTO_TEST_CASE(OverwritesExistingLogFileIfRequested) {
	const boost::filesystem::path path(resourcesDir() / "log-file");

	test_utils::writeToFile(path, "existing output\n");

	{
		LogFile logFile(path, true);
		logFile.write("new output\n");
	}

	std::string result = test_utils::readFile(path);

	BOOST_CHECK_EQUAL(
			result,
			"new output\n"
			);
}

BOOST_AUTO_TEST_CASE(AppendsToExistingLogFileIfRequested) {
	const boost::filesystem::path path(resourcesDir() / "log-file");

	test_utils::writeToFile(path, "existing output\n");

	{
		LogFile logFile(path, false);
		logFile.write("new output\n");
	}

	std::string result = test_utils::readFile(path);

	BOOST_CHECK_EQUAL(
			result,
			"existing output\n"
			"new output\n"
			);
}

BOOST_AUTO_TEST_SUITE_END(/* LogFileTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LogFileTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LoggerTestSuite */);

} // anonymous namespace
