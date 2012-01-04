#include "configuration-exceptions.hpp"

#include <sstream>

using namespace coconut_tools::configuration;

std::string MissingRequiredValue::constructMessage(const std::string& key) {
    std::ostringstream oss;
    oss << "Missing required value in configuration for key \"" << key << "\"";
    return oss.str();
}

std::string MultipleValuesWhereSingleValueRequired::constructMessage(const std::string& key) {
    std::ostringstream oss;
    oss << "Multiple values found where single value was required for key \"" << key << "\"";
    return oss.str();
}
