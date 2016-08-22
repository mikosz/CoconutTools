#ifndef COCONUT_TOOLS_POLICY_LOCKING_UNIQUE_HPP_
#define COCONUT_TOOLS_POLICY_LOCKING_UNIQUE_HPP_

#include <boost/thread/mutex.hpp>

#include "coconut-tools/concurrent/LockingPtr.hpp"
#include "coconut-tools/utils/pointee.hpp"

namespace coconut_tools {
namespace policy {
namespace locking {

class Unique {
public:

    template <class T>
    concurrent::LockingPtr<T> lock(volatile T* objectPtr) volatile {
        volatile T& object = utils::pointee(objectPtr);
        return concurrent::LockingPtr<T>(object, const_cast<boost::mutex&>(mutex_));
    }

private:

    boost::mutex mutex_;

};

} // namespace locking
} // namespace policy
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_POLICY_LOCKING_UNIQUE_HPP_ */
