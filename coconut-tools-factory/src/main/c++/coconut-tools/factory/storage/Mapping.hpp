#ifndef COCONUT_TOOLS_FACTORY_STORAGE_MAPPING_HPP_
#define COCONUT_TOOLS_FACTORY_STORAGE_MAPPING_HPP_

#include <memory>
#include <unordered_map>

#include <boost/call_traits.hpp>

namespace coconut_tools {
namespace factory {
namespace storage {

template <class IdentifierType, class StoredType>
class Mapping {
public:

	using Identifier = IdentifierType;

	using IdentifierParam = typename boost::call_traits<Identifier>::param_type;

	Instance store(const IdentifierParam identifier, std::unique_ptr<typename Instance::element_type>&& instance) {
		if (isStored(identifier)) {
			erase(identifier);
		}
		Instance permanent(instance.release());
		storage_.insert(std::make_pair(identifier, Stored(permanent)));
		return permanent;
	}

	void erase(const IdentifierParam identifier) {
		storage_.erase(identifier);
	}

	void clear() {
		storage_.clear();
	}

protected:

	using Stored = StoredType;

	Stored getStored(const IdentifierParam identifier) const {
		typename Storage::const_iterator it = storage_.find(identifier);
		if (it == storage_.end()) {
			return Stored();
		} else {
			return Stored(it->second);
		}
	}

private:

	using Storage = std::unordered_map<Identifier, Stored>;

	Storage storage_;

};

} // namespace storage
} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_STORAGE_MAPPING_HPP_ */
