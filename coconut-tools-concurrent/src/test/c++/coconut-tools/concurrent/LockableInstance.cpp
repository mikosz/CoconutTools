#define BOOST_TEST_NO_LIB
#include <boost/test/auto_unit_test.hpp>

#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include "coconut-tools/concurrent/LockableInstance.hpp"

using namespace coconut_tools;
using namespace coconut_tools::concurrent;

// TODO: duplicated code from Lockable test - is that bad?

namespace /* anonymous */ {

const size_t FAST_THREAD_COUNT = 4;
const size_t FAST_THREAD_OPS = 100000;
const size_t FAST_THREAD_SLEEP_TIME_MS = 0;
const size_t SLOW_THREAD_COUNT = 2;
const size_t SLOW_THREAD_OPS = 100;
const size_t SLOW_THREAD_SLEEP_TIME_MS = 10;

class IntHolder {
public:

    IntHolder(int initValue = 0) :
        value_(initValue) {
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

template <class I>
void sleepyIncrement(volatile I& v, size_t ops, size_t sleepTimeMs) {
    for (size_t i = 0; i < ops; ++i) {
        typename I::WriteLocked ptr = v.lock();
        int value = ptr->value();
        if (sleepTimeMs) {
            boost::this_thread::sleep(boost::posix_time::milliseconds(sleepTimeMs));
        }
        ptr->value() = value + 1;
    }
}

template <class I>
void runTest(volatile I& i, int offset) {
    std::vector<std::shared_ptr<boost::thread> > threads;

    for (size_t s = 0; s < SLOW_THREAD_COUNT; ++s) {
        threads.push_back(
                std::shared_ptr<boost::thread>(new boost::thread(
                        std::bind(
                                &sleepyIncrement<I>, std::ref(i),
                                SLOW_THREAD_OPS, SLOW_THREAD_SLEEP_TIME_MS))));
    }

    for (size_t f = 0; f < FAST_THREAD_COUNT; ++f) {
        threads.push_back(
                std::shared_ptr<boost::thread>(new boost::thread(
                        std::bind(
                                &sleepyIncrement<I>, std::ref(i),
                                FAST_THREAD_OPS, FAST_THREAD_SLEEP_TIME_MS))));
    }

    BOOST_REQUIRE_EQUAL(threads.size(), FAST_THREAD_COUNT + SLOW_THREAD_COUNT);

    std::for_each(threads.begin(), threads.end(), std::bind(&boost::thread::join, std::placeholders::_1));

    BOOST_CHECK_EQUAL(i.lock()->value(),
            (FAST_THREAD_OPS * FAST_THREAD_COUNT) + (SLOW_THREAD_OPS * SLOW_THREAD_COUNT) + offset);
}

BOOST_AUTO_TEST_SUITE(LockableInstanceTestSuite);

BOOST_AUTO_TEST_CASE(boostSharedTest) {
    volatile LockableInstance<IntHolder, boost::shared_mutex> i;
    runTest(i, 0);
}

BOOST_AUTO_TEST_CASE(constructorTest) {
    volatile LockableInstance<IntHolder> i(1000);
    runTest(i, 1000);
}

BOOST_AUTO_TEST_SUITE_END(/* LockableInstanceTestSuite */);

} // anonymous namespace
