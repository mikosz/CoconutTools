#ifndef COCONUTTOOLS_CONCURRENT_LOCKTRAITS_HPP_
#define COCONUTTOOLS_CONCURRENT_LOCKTRAITS_HPP_

#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>

namespace CoconutTools {
namespace concurrent {

template <class MutexType>
class LockTraits {
};

template <>
class LockTraits<boost::mutex> {
public:

    typedef boost::mutex Mutex;

    typedef boost::unique_lock<Mutex> UniqueLock;

    typedef boost::unique_lock<Mutex> SharedLock;

};

template <>
class LockTraits<boost::shared_mutex> {
public:

    typedef boost::shared_mutex Mutex;

    typedef boost::unique_lock<Mutex> UniqueLock;

    typedef boost::shared_lock<Mutex> SharedLock;

};

template <>
class LockTraits<boost::recursive_mutex> {
public:

    typedef boost::mutex Mutex;

    typedef boost::unique_lock<Mutex> UniqueLock;

    typedef boost::unique_lock<Mutex> SharedLock;

};

}  // namespace concurrent
}  // namespace CoconutTools {

#endif /* COCONUTTOOLS_CONCURRENT_LOCKTRAITS_HPP_ */
