#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_LOCKING_POLICY_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_LOCKING_POLICY_HPP_

#include "locking-policy/SharedMutexLockingPolicy.hpp"
#include "locking-policy/UniqueMutexLockingPolicy.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace factory {

using locking_policy::SharedMutexLockingPolicy;
using locking_policy::UniqueMutexLockingPolicy;

} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_LOCKING_POLICY_HPP_ */
