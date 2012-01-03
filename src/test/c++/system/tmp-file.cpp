#include <boost/test/auto_unit_test.hpp>

#include <sstream>

#include <boost/filesystem.hpp>

#include "system/tmp-file.hpp"
#include "../test-utils.hpp"

using namespace coconut_tools::system;

namespace {

BOOST_AUTO_TEST_SUITE(TmpFileTestSuite);

BOOST_AUTO_TEST_CASE(CreatesTmpFiles) {
    const boost::filesystem::path PATH1("prefix0suffix");
    const boost::filesystem::path PATH2("prefix1suffix");

    if (boost::filesystem::exists(PATH1) || boost::filesystem::exists(PATH2)) {
        BOOST_FAIL("For this test to succeed it is required that neither prefix0suffix nor prefix1suffix exist");
    }
    BOOST_CHECK_EQUAL(createTmpFile("prefix", "suffix"), PATH1);
    BOOST_CHECK(!boost::filesystem::is_directory(PATH1));
    BOOST_CHECK_EQUAL(createTmpFile("prefix", "suffix"), boost::filesystem::path(PATH2));
    BOOST_CHECK(!boost::filesystem::is_directory(PATH2));
    boost::filesystem::remove(PATH1);
    boost::filesystem::remove(PATH2);
}

BOOST_AUTO_TEST_CASE(CreatesTmpDirectories) {
    const boost::filesystem::path PATH1("prefix0suffix");
    const boost::filesystem::path PATH2("prefix1suffix");

    if (boost::filesystem::exists(PATH1) || boost::filesystem::exists(PATH2)) {
        BOOST_FAIL("For this test to succeed it is required that neither prefix0suffix nor prefix1suffix exist");
    }
    BOOST_CHECK_EQUAL(createTmpDir("prefix", "suffix"), PATH1);
    BOOST_CHECK(boost::filesystem::is_directory(PATH1));
    BOOST_CHECK_EQUAL(createTmpDir("prefix", "suffix"), boost::filesystem::path(PATH2));
    BOOST_CHECK(boost::filesystem::is_directory(PATH2));
    boost::filesystem::remove(PATH1);
    boost::filesystem::remove(PATH2);
}

BOOST_AUTO_TEST_CASE(CreatesTmpDirectoryWhenFileExists) {
    const boost::filesystem::path PATH1("prefix0suffix");
    const boost::filesystem::path PATH2("prefix1suffix");

    if (boost::filesystem::exists(PATH1) || boost::filesystem::exists(PATH2)) {
        BOOST_FAIL("For this test to succeed it is required that neither prefix0suffix nor prefix1suffix exist");
    }

    coconut_tools::test::writeToFile(PATH1, "");
    BOOST_CHECK_EQUAL(createTmpDir("prefix", "suffix"), boost::filesystem::path(PATH2));
    BOOST_CHECK(boost::filesystem::is_directory(PATH2));
    boost::filesystem::remove(PATH1);
    boost::filesystem::remove(PATH2);
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
