#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_MAPPINGSTORAGE_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_MAPPINGSTORAGE_HPP_

#include <memory>

#include <boost/call_traits.hpp>
#include <boost/unordered_map.hpp>

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace storage {

template <class IdentifierType, class StoredType, class PermanentType>
class MappingStorage {
public:

    typedef IdentifierType Identifier;

    typedef typename boost::call_traits<Identifier>::param_type IdentifierParam;

    typedef typename StoredType::element_type Instance;

    typedef typename std::auto_ptr<Instance> InstanceParam;

    typedef StoredType Stored;

    typedef PermanentType Permanent;

    Permanent get(const IdentifierParam identifier) const {
        typename Storage::const_iterator it = storage_.find(identifier);
        if (it == storage_.end()) {
            return Permanent();
        } else {
            return Permanent(it->second);
        }
    }

    bool isStored(const IdentifierParam identifier) const {
        return storage_.count(identifier);
    }

    Permanent store(const IdentifierParam identifier, InstanceParam instance) {
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

    typedef boost::unordered_map<Identifier, Stored> Storage;

    boost::unordered_map<Identifier, Stored> storage_;

};

} // namespace storage
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_MAPPINGSTORAGE_HPP_ */
