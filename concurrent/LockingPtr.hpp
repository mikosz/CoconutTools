#ifndef COCONUTTOOLS_CONCURRENT_LOCKINGPTR_HPP_
#define COCONUTTOOLS_CONCURRENT_LOCKINGPTR_HPP_

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

namespace CoconutTools {
namespace concurrent {

template <class T, class M = boost::mutex, class L = boost::unique_lock<M> >
class LockingPtr {
public:

    typedef T Value;

    typedef M Mutex;

    typedef L Lock;

    LockingPtr(volatile Value& object, Mutex& mutex) :
        object_(const_cast<Value&>(object)),
        lock_(mutex) {
    }

    LockingPtr(const LockingPtr& rhs) :
        object_(rhs.object_),
        lock_(*rhs.lock_.mutex()) {
    }

    Value& operator*() {
        return object_;
    }

    Value* operator->() {
        return &object_;
    }

    Lock& lock() {
        return lock_;
    }

private:

    Value& object_;

    Lock lock_;

};

}  // namespace concurrent
}  // namespace CoconutTools {

#endif /* COCONUTTOOLS_CONCURRENT_LOCKINGPTR_HPP_ */
