#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_HPP_

#include "storage/NoStorage.hpp"
#include "storage/PermanentStorage.hpp"
#include "storage/VolatileStorage.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace factory {

using storage::NoStorage;
using storage::PermanentStorage;
using storage::VolatileStorage;

} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_HPP_ */
