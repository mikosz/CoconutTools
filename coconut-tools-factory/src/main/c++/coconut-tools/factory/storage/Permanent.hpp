#ifndef COCONUT_TOOLS_FACTORY_STORAGE_PERMANENT_HPP_
#define COCONUT_TOOLS_FACTORY_STORAGE_PERMANENT_HPP_

#include <functional>
#include <memory>

#include "detail/InstanceType.hpp"
#include "detail/Mapping.hpp"

namespace coconut_tools {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType>
class Permanent :
	public detail::Mapping<
        IdentifierType,
        std::shared_ptr<detail::InstanceTypeT<InstanceType>>
        >
{
private:

	using StoredType = std::shared_ptr<detail::InstanceTypeT<InstanceType>>;

	using Super = Mapping<
		IdentifierType,
		StoredType
		>;

public:

	using Instance = std::shared_ptr<detail::InstanceTypeT<InstanceType>>;

	using IdentifierParam = typename Super::IdentifierParam;

	using Creator = std::function<InstanceType()>;

	Instance get(const IdentifierParam identifier, Creator creator) {
		auto permanent = Super::getStored(identifier);
		if (!permanent) {
			permanent = Super::store(identifier, creator());
		}
		return permanent;
	}

	bool isStored(const IdentifierParam identifier) const {
		return static_cast<bool>(Super::getStored(identifier));
	}

};

} // namespace storage
} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_STORAGE_PERMANENT_HPP_ */
