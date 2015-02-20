#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

#include <boost/test/auto_unit_test.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include "coconut-tools/concurrent/Lockable.hpp"

using namespace coconut_tools;

namespace {

const size_t FAST_THREAD_COUNT = 4;
const size_t FAST_THREAD_OPS = 100000;
const size_t FAST_THREAD_SLEEP_TIME_MS = 0;
const size_t SLOW_THREAD_COUNT = 2;
const size_t SLOW_THREAD_OPS = 100;
const size_t SLOW_THREAD_SLEEP_TIME_MS = 10;

template <class M>
class IntHolder : public concurrent::Lockable<IntHolder<M>, M> {
public:

    IntHolder() :
        value_(0) {
    }

    int& value() {
        return value_;
    }

    int value() const {
        return value_;
    }

private:

    int value_;

};

template <class I, class M>
void sleepyIncrement(volatile I& v, M& m, size_t ops, size_t sleepTimeMs) {
    for (size_t i = 0; i < ops; ++i) {
        typename I::WriteLocked ptr = v.lock();
        int value = ptr->value();
        if (sleepTimeMs) {
            boost::this_thread::sleep(boost::posix_time::milliseconds(sleepTimeMs));
        }
        ptr->value() = value + 1;
    }
}

template <class I, class M>
void runTest(volatile I& i, M& m) {
    std::vector<std::shared_ptr<boost::thread> > threads;

    for (size_t s = 0; s < SLOW_THREAD_COUNT; ++s) {
        threads.push_back(
                std::shared_ptr<boost::thread>(new boost::thread(
                        std::bind(
                                &sleepyIncrement<I, M>, std::ref(i), std::ref(m),
                                SLOW_THREAD_OPS, SLOW_THREAD_SLEEP_TIME_MS))));
    }

    for (size_t f = 0; f < FAST_THREAD_COUNT; ++f) {
        threads.push_back(
                std::shared_ptr<boost::thread>(new boost::thread(
                        std::bind(
                                &sleepyIncrement<I, M>, std::ref(i), std::ref(m),
                                FAST_THREAD_OPS, FAST_THREAD_SLEEP_TIME_MS))));
    }

    BOOST_REQUIRE_EQUAL(threads.size(), FAST_THREAD_COUNT + SLOW_THREAD_COUNT);

    std::for_each(threads.begin(), threads.end(), std::bind(&boost::thread::join, std::placeholders::_1));

    BOOST_CHECK_EQUAL(const_cast<I&>(i).value(),
            (FAST_THREAD_OPS * FAST_THREAD_COUNT) + (SLOW_THREAD_OPS * SLOW_THREAD_COUNT));
}

BOOST_AUTO_TEST_SUITE(LockingPtrTestSuite);

BOOST_AUTO_TEST_CASE(sharedTest) {
    volatile IntHolder<boost::shared_mutex> i;
    boost::shared_mutex m;
    runTest(i, m);
}

BOOST_AUTO_TEST_CASE(scopedTest) {
    volatile IntHolder<boost::mutex> i;
    boost::mutex m;
    runTest(i, m);
}

BOOST_AUTO_TEST_SUITE_END();

} // anonymous namespace
