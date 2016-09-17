#include "Logging.hpp"

#include "coconut-tools/logger.hpp"

CT_LOGGER_CATEGORY("COCONUT_TOOLS.FACTORY.ERROR_POLICY");

namespace coconut_tools {
namespace factory {
namespace error_policy {

void log_(const std::string& message) {
	CT_LOG_ERROR << message;
}

}  // namespace error_policy
}  // namespace factory
}  // namespace coconut_tools
