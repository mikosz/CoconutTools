#include "Logging.hpp"

#include "coconut-tools/logger.hpp"

CT_LOGGING_CATEGORY("COCONUT_TOOLS.FACTORY");

void coconut_tools::factory::error_policy::log_(const std::string& message) {
	CT_LOG_ERROR << message;
}
