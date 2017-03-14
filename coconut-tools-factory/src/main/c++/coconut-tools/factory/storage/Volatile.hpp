#ifndef COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_
#define COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_

#include <memory>

#include "detail/InstanceType.hpp"
#include "Mapping.hpp"

namespace coconut_tools {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType>
class Volatile :
	public Mapping<
		IdentifierType,
		std::weak_ptr<detail::InstanceTypeT<InstanceType>>,
		std::shared_ptr<detail::InstanceTypeT<InstanceType>>
		>
{
private:

	using Super = Mapping<
		IdentifierType,
		std::weak_ptr<detail::InstanceTypeT<InstanceType>>,
		std::shared_ptr<detail::InstanceTypeT<InstanceType>>
		>;

public:

	using Instance = typename Super::Instance;

	using Identifier = typename Super::Identifier;

	using IdentifierParam = typename Super::IdentifierParam;

	using Stored = typename Super::Stored;

	Instance get(const IdentifierParam identifier) const {
		return Super::getStored(identifier).lock();
	}

};

} // namespace storage
} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_STORAGE_VOLATILE_HPP_ */
