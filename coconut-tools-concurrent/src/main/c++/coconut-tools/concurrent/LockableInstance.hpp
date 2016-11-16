#ifndef COCONUTTOOLS_CONCURRENT_LOCKABLEINSTANCE_HPP_
#define COCONUTTOOLS_CONCURRENT_LOCKABLEINSTANCE_HPP_

#include <mutex>

#include "LockingPtr.hpp"
#include "LockTraits.hpp"

namespace coconut_tools {
namespace concurrent {

// TODO: Lockable* needs redesign
template <class T, class M = std::mutex>
class LockableInstance {
public:

    using Mutex = M;

    using ReadLock = typename LockTraits<Mutex>::SharedLock;

    using WriteLock = typename LockTraits<Mutex>::UniqueLock;

    using ReadLocked = LockingPtr<const T, M, ReadLock>;

    using WriteLocked = LockingPtr<T, M, WriteLock>;

	template <class... Args>
	LockableInstance(Args&&... args) :
		object_(std::forward<Args>(args)...)
	{
	}

	Mutex& mutex() const volatile {
        return const_cast<Mutex&>(mutex_);
	}

    ReadLocked lock() const volatile {
        return ReadLocked(static_cast<const volatile T&>(object_), mutex());
    }

    WriteLocked lock() volatile {
        return WriteLocked(static_cast<volatile T&>(object_), mutex());
    }

private:

	mutable Mutex mutex_;

    T object_;

};

} // namespace concurrent
} // namespace CoconutTools

#endif /* COCONUTTOOLS_CONCURRENT_LOCKABLEINSTANCE_HPP_ */
