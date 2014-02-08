#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_ERROR_POLICY_IGNORINGERRORPOLICY_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_ERROR_POLICY_IGNORINGERRORPOLICY_HPP_

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace error_policy {

template <class IdentifierType, class InstanceType>
class IgnoringErrorPolicy {
public:

    typedef IdentifierType Identifier;

    typedef typename boost::call_traits<Identifier>::param_type IdentifierParam;

    typedef InstanceType Instance;

    static void alreadyRegistered(const IdentifierParam) {
    }

    static void noSuchType(const IdentifierParam) {
    }

};

}  // namespace error_policy
}  // namespace factory
}  // namespace design_pattern
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_ERROR_POLICY_IGNORINGERRORPOLICY_HPP_ */
