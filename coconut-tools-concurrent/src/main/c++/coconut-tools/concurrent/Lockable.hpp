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

    using Mutex = M;

    using ReadLock = typename LockTraits<Mutex>::SharedLock;

    using WriteLock = typename LockTraits<Mutex>::UniqueLock;

    using ReadLocked = LockingPtr<const T, Mutex, ReadLock>;

    using WriteLocked = LockingPtr<T, Mutex, WriteLock>;

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

    Lockable() = default;

    virtual ~Lockable() = default;

private:

    mutable Mutex mutex_;

};

} // namespace concurrent
} // namespace CoconutTools

#endif /* COCONUTTOOLS_CONCURRENT_LOCKABLE_HPP_ */
