#ifndef COCONUT_TOOLS_TEST_GMOCKFIXTURE_HPP_
#define COCONUT_TOOLS_TEST_GMOCKFIXTURE_HPP_

#include <boost/test/unit_test.hpp>

#include <gmock/gmock.h>

namespace coconut_tools {
namespace test {

class GMockFixture {

    class BoostTestAdapter : public testing::EmptyTestEventListener {

        void OnTestStart(const testing::TestInfo&) {
        }

        void OnTestEnd(const testing::TestInfo&) {
        }

        void OnTestPartResult(const testing::TestPartResult& testPartResult) {
            if (testPartResult.failed()) {
                std::ostringstream err;
                err << "Mock test failed (file: "
                    << (testPartResult.file_name() ? testPartResult.file_name() : "")
                    << ", line: " << testPartResult.line_number()
                    << "): " << testPartResult.summary();
                BOOST_ERROR(err.str());
            }
        }

    };

public:

    GMockFixture() {
        testing::GTEST_FLAG(throw_on_failure) = false;
        testing::InitGoogleMock(&boost::unit_test::framework::master_test_suite().argc,
                boost::unit_test::framework::master_test_suite().argv);
        testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
        delete listeners.Release(listeners.default_result_printer());
        listeners.Append(new BoostTestAdapter);
    }

};

} // namespace test
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_TEST_GMOCKFIXTURE_HPP_ */
