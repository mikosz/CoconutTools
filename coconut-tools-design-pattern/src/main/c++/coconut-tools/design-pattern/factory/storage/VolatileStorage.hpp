#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_VOLATILESTORAGE_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_VOLATILESTORAGE_HPP_

#include <memory>

#include "MappingStorage.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType>
class VolatileStorage :
    public MappingStorage<
        IdentifierType,
        std::weak_ptr<typename InstanceType::element_type>,
        std::shared_ptr<typename InstanceType::element_type>
        >
{
private:

    typedef MappingStorage<
                IdentifierType,
				std::weak_ptr<typename InstanceType::element_type>,
				std::shared_ptr<typename InstanceType::element_type>
                >
            Super;

public:

    typedef typename Super::Instance Instance;

    typedef typename Super::Identifier Identifier;

    typedef typename Super::IdentifierParam IdentifierParam;

    typedef typename Super::Permanent Permanent;

    typedef typename Super::Stored Stored;

    Permanent get(const IdentifierParam identifier) const {
        Stored stored = Super::getStored(identifier);
        return stored.lock();
    }

};

} // namespace storage
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_VOLATILESTORAGE_HPP_ */
