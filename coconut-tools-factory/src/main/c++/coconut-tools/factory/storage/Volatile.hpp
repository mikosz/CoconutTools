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
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_ */
