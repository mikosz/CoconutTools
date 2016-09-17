#ifndef COCONUTTOOLS_CONCURRENT_LOCKTRAITS_HPP_
#define COCONUTTOOLS_CONCURRENT_LOCKTRAITS_HPP_

#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>

namespace coconut_tools {
namespace concurrent {

template <class MutexType>
class LockTraits {
};

template <>
class LockTraits<boost::mutex> {
public:

    using Mutex = boost::mutex;

    using UniqueLock = boost::unique_lock<Mutex>;

    using SharedLock = boost::unique_lock<Mutex>;

};

template <>
class LockTraits<boost::shared_mutex> {
public:

    using Mutex = boost::shared_mutex;

    using UniqueLock = boost::unique_lock<Mutex>;

    using SharedLock = boost::shared_lock<Mutex>;

};

template <>
class LockTraits<boost::recursive_mutex> {
public:

    using Mutex = boost::mutex;

    using UniqueLock = boost::unique_lock<Mutex>;

    using SharedLock = boost::unique_lock<Mutex>;

};

} // namespace concurrent
} // namespace CoconutTools

#endif /* COCONUTTOOLS_CONCURRENT_LOCKTRAITS_HPP_ */
