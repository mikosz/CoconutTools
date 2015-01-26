#ifndef COCONUT_TOOLS_DESIGN_PATTERN_SHAREDMUTEXLOCKINGPOLICY_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_SHAREDMUTEXLOCKINGPOLICY_HPP_

#include <boost/thread/shared_mutex.hpp>

#include "coconut-tools/concurrent/LockingPtr.hpp"
#include "coconut-tools/utils/pointee.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace locking_policy {

class SharedMutexLockingPolicy {
public:

    template <class T>
    concurrent::LockingPtr<T, boost::shared_mutex> lock(volatile T* objectPtr) volatile {
        volatile T& object = utils::pointee(objectPtr);
        return concurrent::LockingPtr<T, boost::shared_mutex>(object, const_cast<boost::shared_mutex&>(mutex_));
    }

    template <class T>
    concurrent::LockingPtr<T, boost::shared_mutex, boost::shared_lock<boost::shared_mutex> > lock(
            const volatile T* objectPtr) volatile {
        volatile T& object = utils::pointee(objectPtr);
        return concurrent::LockingPtr<T, boost::shared_mutex, boost::shared_lock<boost::shared_mutex> >(object,
                const_cast<const boost::shared_mutex&>(mutex_));
    }

private:

    boost::shared_mutex mutex_;

};

} // namespace locking_policy
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_SHAREDMUTEXLOCKINGPOLICY_HPP_ */
