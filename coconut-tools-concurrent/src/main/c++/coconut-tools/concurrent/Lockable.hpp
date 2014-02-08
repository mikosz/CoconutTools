#ifndef COCONUTTOOLS_CONCURRENT_LOCKABLE_HPP_
#define COCONUTTOOLS_CONCURRENT_LOCKABLE_HPP_

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#include "LockingPtr.hpp"
#include "LockTraits.hpp"

namespace coconut_tools {
namespace concurrent {

// TODO: storage (copying) policies for lockable?
template <class T, class M = boost::mutex>
class Lockable {
public:

    typedef M Mutex;

    typedef typename LockTraits<Mutex>::SharedLock ReadLock;

    typedef typename LockTraits<Mutex>::UniqueLock WriteLock;

    typedef LockingPtr<const T, Mutex, ReadLock> ReadLocked;

    typedef LockingPtr<T, Mutex, WriteLock> WriteLocked;

    Mutex& mutex() const volatile {
        return const_cast<Mutex&>(mutex_);
    }

    ReadLocked lock() const volatile {
        return ReadLocked(static_cast<const volatile T&>(*this), mutex());
    }

    WriteLocked lock() volatile {
        return WriteLocked(static_cast<volatile T&>(*this), mutex());
    }

    ReadLocked readLock() const volatile {
        return ReadLocked(static_cast<const volatile T&>(*this), mutex());
    }

    WriteLocked writeLock() volatile {
        return WriteLocked(static_cast<volatile T&>(*this), mutex());
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
