#include <vector>
#include <algorithm>

#include <boost/test/auto_unit_test.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "concurrent/LockingPtr.hpp"

using namespace CoconutTools;

namespace {

const size_t FAST_THREAD_COUNT = 4;
const size_t FAST_THREAD_OPS = 100000;
const size_t FAST_THREAD_SLEEP_TIME_MS = 0;
const size_t SLOW_THREAD_COUNT = 2;
const size_t SLOW_THREAD_OPS = 100;
const size_t SLOW_THREAD_SLEEP_TIME_MS = 10;

void sleepyIncrement(volatile int& v, boost::mutex& m, size_t ops, size_t sleepTimeMs) {
    for (size_t i = 0; i < ops; ++i) {
        concurrent::LockingPtr<int> ptr(v, m);
        int value = *ptr;
        if (sleepTimeMs) {
            boost::this_thread::sleep(boost::posix_time::milliseconds(sleepTimeMs));
        }
        *ptr = value + 1;
    }
}

BOOST_AUTO_TEST_SUITE(LockingPtrTestSuite);

BOOST_AUTO_TEST_CASE(basicTest) {
    volatile int i = 0;
    boost::mutex m;
    std::vector<boost::shared_ptr<boost::thread> > threads;

    for (size_t s = 0; s < SLOW_THREAD_COUNT; ++s) {
        threads.push_back(
                boost::shared_ptr<boost::thread>(new boost::thread(
                        boost::bind(
                                &sleepyIncrement, boost::ref(i), boost::ref(m),
                                SLOW_THREAD_OPS, SLOW_THREAD_SLEEP_TIME_MS))));
    }

    for (size_t f = 0; f < FAST_THREAD_COUNT; ++f) {
        threads.push_back(
                boost::shared_ptr<boost::thread>(new boost::thread(
                        boost::bind(
                                &sleepyIncrement, boost::ref(i), boost::ref(m),
                                FAST_THREAD_OPS, FAST_THREAD_SLEEP_TIME_MS))));
    }

    BOOST_REQUIRE_EQUAL(threads.size(), FAST_THREAD_COUNT + SLOW_THREAD_COUNT);

    std::for_each(threads.begin(), threads.end(), boost::bind(&boost::thread::join, _1));

    BOOST_CHECK_EQUAL(i, (FAST_THREAD_OPS * FAST_THREAD_COUNT) + (SLOW_THREAD_OPS * SLOW_THREAD_COUNT));
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
