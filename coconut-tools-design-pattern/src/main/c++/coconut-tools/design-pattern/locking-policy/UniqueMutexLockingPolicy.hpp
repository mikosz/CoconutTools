#ifndef COCONUT_TOOLS_DESIGN_PATTERN_UNIQUEMUTEXLOCKINGPOLICY_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_UNIQUEMUTEXLOCKINGPOLICY_HPP_

#include <boost/thread/mutex.hpp>

#include "coconut-tools/concurrent/LockingPtr.hpp"
#include "coconut-tools/utils/pointee.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace locking_policy {

class UniqueMutexLockingPolicy {
public:

    template <class T>
    concurrent::LockingPtr<T> lock(volatile T* objectPtr) volatile {
        volatile T& object = utils::pointee(objectPtr);
        return concurrent::LockingPtr<T>(object, const_cast<boost::mutex&>(mutex_));
    }

private:

    boost::mutex mutex_;

};

} // namespace locking_policy
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_UNIQUEMUTEXLOCKINGPOLICY_HPP_ */
