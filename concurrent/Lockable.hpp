#ifndef COCONUTTOOLS_CONCURRENT_LOCKABLE_HPP_
#define COCONUTTOOLS_CONCURRENT_LOCKABLE_HPP_

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#include "LockingPtr.hpp"

namespace CoconutTools {
namespace concurrent {

// TODO: storage (copying) policies for lockable?
template <class T, class M = boost::mutex>
class Lockable {
public:

    typedef M Mutex;

    typedef boost::shared_lock<M> ReadLock;

    typedef boost::unique_lock<M> WriteLock;

    typedef LockingPtr<T, M, ReadLock> ReadLockingPtr;

    typedef LockingPtr<T, M, WriteLock> WriteLockingPtr;

    Mutex& mutex() const volatile {
        return const_cast<Mutex&>(mutex_);
    }

    template <class Lock>
    LockingPtr<T, M, Lock> lock() volatile {
        return LockingPtr<T, M, Lock>(static_cast<volatile T&>(*this), mutex());
    }

    template <class Lock>
    LockingPtr<T, M, Lock> lock() const volatile {
        return LockingPtr<T, M, Lock>(static_cast<const volatile T&>(*this), mutex());
    }

protected:

    Lockable() {
    }

    virtual ~Lockable() {
    }

private:

    mutable Mutex mutex_;

};

}  // namespace concurrent
}  // namespace CoconutTools {

#endif /* COCONUTTOOLS_CONCURRENT_LOCKABLE_HPP_ */
