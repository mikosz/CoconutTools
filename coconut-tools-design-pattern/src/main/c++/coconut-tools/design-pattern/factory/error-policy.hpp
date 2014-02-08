#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_ERROR_POLICY_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_ERROR_POLICY_HPP_

#include "error-policy/ExceptionThrowingErrorPolicy.hpp"
#include "error-policy/IgnoringErrorPolicy.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace factory {

using error_policy::CreatorAlreadyRegistered;
using error_policy::NoSuchType;
using error_policy::ExceptionThrowingErrorPolicy;

using error_policy::IgnoringErrorPolicy;

} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_ERROR_POLICY_HPP_ */
