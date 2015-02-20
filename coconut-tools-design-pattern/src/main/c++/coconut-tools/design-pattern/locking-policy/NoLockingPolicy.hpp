#ifndef COCONUT_TOOLS_DESIGN_PATTERN_NOLOCKINGPOLICY_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_NOLOCKINGPOLICY_HPP_

namespace coconut_tools {
namespace design_pattern {
namespace locking_policy {

class NoLockingPolicy {
public:

    template <class T>
    T* lock(volatile T* objectPtr) volatile {
        return const_cast<T*>(objectPtr);
    }

};

} // namespace locking_policy
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_NOLOCKINGPOLICY_HPP_ */
