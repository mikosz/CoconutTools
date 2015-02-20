#include <boost/test/auto_unit_test.hpp>

#include "coconut-tools/logger/log-file/LogFileFactory.hpp"

#include "coconut-tools/test-utils/test-utils.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::log_file;

namespace {

BOOST_AUTO_TEST_SUITE(LoggerTestSuite);
BOOST_AUTO_TEST_SUITE(LogFileTestSuite);
BOOST_FIXTURE_TEST_SUITE(LogFileFactoryTestSuite, test_utils::ResourcesDirFixture);

BOOST_AUTO_TEST_CASE(ProducesSameFileWithOverwrite) {
	LogFileFactory factory;
	factory.registerLogFile("to-overwrite", resourcesDir() / "to-overwrite.txt", true);

	test_utils::writeToFile(resourcesDir() / "to-overwrite.txt", "original content\n");

	{
		LogFileSharedPtr logFile = factory.create("to-overwrite");
		logFile->write("new content\n");
	}

	{
		LogFileSharedPtr logFile = factory.create("to-overwrite");
		logFile->write("more new content\n");
	}

	BOOST_CHECK_EQUAL(
		test_utils::readFile(resourcesDir() / "to-overwrite.txt"),
		"new content\n"
		"more new content\n"
		);
}

BOOST_AUTO_TEST_CASE(ProducesSameFileWithAppend) {
	LogFileFactory factory;
	factory.registerLogFile("to-append", resourcesDir() / "to-append.txt", false);

	test_utils::writeToFile(resourcesDir() / "to-append.txt", "original content\n");

	{
		LogFileSharedPtr logFile = factory.create("to-append");
		logFile->write("new content\n");
	}

	{
		LogFileSharedPtr logFile = factory.create("to-append");
		logFile->write("more new content\n");
	}

	BOOST_CHECK_EQUAL(
		test_utils::readFile(resourcesDir() / "to-append.txt"),
		"original content\n"
		"new content\n"
		"more new content\n"
		);
}

BOOST_AUTO_TEST_SUITE_END(/* LogFileFactoryTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LogFileTestSuite */);
BOOST_AUTO_TEST_SUITE_END(/* LoggerTestSuite */);

} // anonymous namespace
