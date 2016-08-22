#ifndef COCONUT_TOOLS_POLICY_LOCKING_NONE_HPP_
#define COCONUT_TOOLS_POLICY_LOCKING_NONE_HPP_

namespace coconut_tools {
namespace policy {
namespace locking {

class None {
public:

    template <class T>
    T* lock(volatile T* objectPtr) volatile {
        return const_cast<T*>(objectPtr);
    }

};

} // namespace locking
} // namespace policy
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_POLICY_LOCKING_NONE_HPP_ */
