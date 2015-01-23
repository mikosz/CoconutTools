#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_PERMANENTSTORAGE_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_PERMANENTSTORAGE_HPP_

#include <memory>

#include "MappingStorage.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType>
class PermanentStorage :
    public MappingStorage<
        IdentifierType,
        std::shared_ptr<InstanceType>,
        std::shared_ptr<InstanceType>
        >
{
};

} // namespace storage
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_PERMANENTSTORAGE_HPP_ */
