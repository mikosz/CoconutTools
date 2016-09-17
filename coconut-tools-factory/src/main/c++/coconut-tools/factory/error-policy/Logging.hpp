#ifndef COCONUT_TOOLS_FACTORY_ERROR_POLICY_LOGGING_HPP_
#define COCONUT_TOOLS_FACTORY_ERROR_POLICY_LOGGING_HPP_

#include <sstream>

#include <boost/call_traits.hpp>

namespace coconut_tools {
namespace factory {
namespace error_policy {

template <class IdentifierType>
class Logging {
public:

    using Identifier = IdentifierType;

    using IdentifierParam = typename boost::call_traits<Identifier>::param_type;

    static void alreadyRegistered(const IdentifierParam) {
		std::ostringstream oss;
		oss << "Attempting to register creator \"" << IdentifierParam << "\" which had already been registered";
		log_(oss.str());
    }

    static void noSuchType(const IdentifierParam) {
		std::ostringstream oss;
		oss << "Attempting access unkown creator \"" << IdentifierParam << "\"";
		log_(oss.str());
    }

private:

	friend void log_(const std::string& errorMessage);

};

}  // namespace error_policy
}  // namespace factory
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_ERROR_POLICY_LOGGING_HPP_ */
