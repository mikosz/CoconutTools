#ifndef COCONUTTOOLS_CONCURRENT_ILOCKABLE_HPP_
#define COCONUTTOOLS_CONCURRENT_ILOCKABLE_HPP_

namespace coconut_tools {
namespace concurrent {

template <class ReadLockedType, class WriteLockedType>
class ILockable { // TODO: rename? We don't normally use "I" for interfaces, but "Lockable" is used already
public:

    using ReadLocked = ReadLockedType;

    using WriteLocked = WriteLockedType;

    virtual ReadLocked lock() const volatile = 0;

	virtual WriteLocked lock() volatile = 0;

    ReadLocked readLock() const volatile {
        return lock();
    }

    WriteLocked writeLock() volatile {
        return lock();
    }

protected:

    ILockable() = default;

    virtual ~ILockable() = default;

	ILockable(const ILockable& other) = default;

	ILockable& operator=(const ILockable& other) = default;

};

} // namespace concurrent
} // namespace CoconutTools

#endif /* COCONUTTOOLS_CONCURRENT_ILOCKABLE_HPP_ */
