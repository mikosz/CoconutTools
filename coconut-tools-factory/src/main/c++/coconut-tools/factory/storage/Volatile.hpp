#ifndef COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_
#define COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_

#include <memory>
#include <functional>

#include "detail/InstanceType.hpp"
#include "Mapping.hpp"

namespace coconut_tools {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType>
class Volatile :
	public Mapping<
		IdentifierType,
		std::weak_ptr<detail::InstanceTypeT<InstanceType>>
		>
{
private:

	using StoredType = std::weak_ptr<detail::InstanceTypeT<InstanceType>>;

	using Super = Mapping<
		IdentifierType,
		StoredType
		>;

public:

	using Instance = std::shared_ptr<detail::InstanceTypeT<InstanceType>>;

	using IdentifierParam = typename Super::IdentifierParam;

	using Creator = std::function<InstanceType()>;

	Instance get(const IdentifierParam identifier, Creator creator) const {
		auto stored = Super::getStored(identifier).lock();
		if (!stored) {
			auto permanent = PermanentType(creator());
			Super::store(identifier)
		}
	}

};

} // namespace storage
} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_ */
