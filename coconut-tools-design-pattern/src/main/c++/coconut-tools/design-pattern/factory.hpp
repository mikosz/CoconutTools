#ifndef COCONUTTOOLS_DESIGN_PATTERN_FACTORY_HPP_
#define COCONUTTOOLS_DESIGN_PATTERN_FACTORY_HPP_

#include "factory/creator.hpp"
#include "factory/error-policy.hpp"
#include "factory/Factory.hpp"
#include "factory/locking-policy.hpp"
#include "factory/storage.hpp"

namespace coconut_tools {
namespace design_pattern {

using factory::Factory;

using factory::creator::FunctorCreator;
using factory::creator::NewCreator;

using factory::error_policy::CreatorAlreadyRegistered;
using factory::error_policy::NoSuchType;
using factory::error_policy::ExceptionThrowingErrorPolicy;

using factory::locking_policy::NoLockingPolicy;
using factory::locking_policy::SharedMutexLockingPolicy;
using factory::locking_policy::UniqueMutexLockingPolicy;

using factory::storage::NoStorage;
using factory::storage::PermanentStorage;
using factory::storage::VolatileStorage;

}  // namespace design_pattern
}  // namespace coconut_tools

#endif /* COCONUTTOOLS_DESIGN_PATTERN_FACTORY_HPP_ */
