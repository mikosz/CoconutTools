#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_NOSTORAGE_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_NOSTORAGE_HPP_

#include <memory>

#include <boost/call_traits.hpp>

#include "coconut-tools/exceptions/LogicError.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace storage {

class GetCalledOnNoStorage : public exceptions::LogicError {
};

template <class IdentifierType, class InstanceType>
class NoStorage {
public:

    typedef IdentifierType Identifier;

    typedef typename boost::call_traits<Identifier>::param_type IdentifierParam;

    typedef InstanceType Instance;

    typedef Instance InstanceParam;

    typedef Instance Permanent;

    Permanent get(const IdentifierParam) const {
        throw GetCalledOnNoStorage();
    }

    bool isStored(const IdentifierParam) const {
        return false;
    }

    Permanent store(const IdentifierParam, InstanceParam&& instance) {
        return std::move(instance);
    }

    void erase(const IdentifierParam) {
    }

};

} // namespace storage
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_NOSTORAGE_HPP_ */
