#ifndef COCONUT_TOOLS_FACTORY_STORAGE_MAPPING_HPP_
#define COCONUT_TOOLS_FACTORY_STORAGE_MAPPING_HPP_

#include <memory>
#include <unordered_map>

#include <boost/call_traits.hpp>

namespace coconut_tools {
namespace factory {
namespace storage {

template <class IdentifierType, class StoredType, class PermanentType>
class Mapping {
public:

    using Identifier = IdentifierType;

    using IdentifierParam = typename boost::call_traits<Identifier>::param_type;

    using Instance = typename StoredType::element_type;

    using InstanceParam = typename std::unique_ptr<Instance>;

    using Stored = StoredType;

    using Permanent = PermanentType;

    Permanent get(const IdentifierParam identifier) const {
        typename Storage::const_iterator it = storage_.find(identifier);
        if (it == storage_.end()) {
            return Permanent();
        } else {
            return Permanent(it->second);
        }
    }

    bool isStored(const IdentifierParam identifier) const {
        return storage_.count(identifier) != 0;
    }

    Permanent store(const IdentifierParam identifier, InstanceParam&& instance) {
        if (isStored(identifier)) {
            erase(identifier);
        }
        Permanent permanent(instance.release());
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
