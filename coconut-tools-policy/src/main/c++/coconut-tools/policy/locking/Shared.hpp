#ifndef COCONUT_TOOLS_POLICY_LOCKING_SHARED_HPP_
#define COCONUT_TOOLS_POLICY_LOCKING_SHARED_HPP_

#include <boost/thread/shared_mutex.hpp>

#include "coconut-tools/concurrent/LockingPtr.hpp"
#include "coconut-tools/utils/pointee.hpp"

namespace coconut_tools {
namespace policy {
namespace locking {

class Shared {
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

} // namespace locking
} // namespace policy
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_POLICY_LOCKING_SHARED_HPP_ */
