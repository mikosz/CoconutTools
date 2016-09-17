#ifndef COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_
#define COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_

#include <memory>

#include "Mapping.hpp"

namespace coconut_tools {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType>
class Volatile :
    public Mapping<
        IdentifierType,
        std::weak_ptr<typename InstanceType::element_type>,
        std::shared_ptr<typename InstanceType::element_type>
        >
{
private:

    typedef Mapping<
                IdentifierType,
				std::weak_ptr<typename InstanceType::element_type>,
				std::shared_ptr<typename InstanceType::element_type>
                >
            Super;

public:

    using Instance = typename Super::Instance;

    using Identifier = typename Super::Identifier;

    using IdentifierParam = typename Super::IdentifierParam;

    using Stored = typename Super::Stored;

    Instance get(const IdentifierParam identifier) const {
        Stored stored = Super::getStored(identifier);
        return stored.lock();
    }

};

} // namespace storage
} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_ */
