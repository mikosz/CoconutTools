#ifndef COCONUT_TOOLS_FACTORY_STORAGE_NONE_HPP_
#define COCONUT_TOOLS_FACTORY_STORAGE_NONE_HPP_

#include <memory>

#include <boost/call_traits.hpp>

#include "coconut-tools/exceptions/LogicError.hpp"

namespace coconut_tools {
namespace factory {
namespace storage {

class GetCalledOnNone : public exceptions::LogicError {
};

template <class IdentifierType, class InstanceType>
class None {
public:

    typedef IdentifierType Identifier;

    typedef typename boost::call_traits<Identifier>::param_type IdentifierParam;

    typedef InstanceType Instance;

    typedef Instance InstanceParam;

    typedef Instance Permanent;

    Permanent get(const IdentifierParam) const {
        throw GetCalledOnNone();
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
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_STORAGE_NONE_HPP_ */
