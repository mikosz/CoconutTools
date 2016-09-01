#ifndef COCONUT_TOOLS_FACTORY_STORAGE_PERMANENT_HPP_
#define COCONUT_TOOLS_FACTORY_STORAGE_PERMANENT_HPP_

#include <memory>

#include "Mapping.hpp"

namespace coconut_tools {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType>
class Permanent :
    public Mapping<
        IdentifierType,
        std::shared_ptr<typename InstanceType::element_type>,
        std::shared_ptr<typename InstanceType::element_type>
        >
{
};

} // namespace storage
} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_STORAGE_PERMANENT_HPP_ */
