#ifndef COCONUTTOOLS_DESIGN_PATTERN_DESIGN_PATTERN_HPP_
#define COCONUTTOOLS_DESIGN_PATTERN_DESIGN_PATTERN_HPP_

#include "design-pattern/factory.hpp"

namespace coconut_tools {

using design_pattern::factory::Factory;

using design_pattern::factory::creator::FunctorCreator;
using design_pattern::factory::creator::NewCreator;

using design_pattern::factory::error_policy::CreatorAlreadyRegistered;
using design_pattern::factory::error_policy::NoSuchType;
using design_pattern::factory::error_policy::ExceptionThrowingErrorPolicy;

using design_pattern::factory::locking_policy::NoLockingPolicy;
using design_pattern::factory::locking_policy::SharedMutexLockingPolicy;
using design_pattern::factory::locking_policy::UniqueMutexLockingPolicy;

using design_pattern::factory::storage::NoStorage;
using design_pattern::factory::storage::PermanentStorage;
using design_pattern::factory::storage::VolatileStorage;

}  // namespace coconut_tools

#endif /* COCONUTTOOLS_DESIGN_PATTERN_DESIGN_PATTERN_HPP_ */
