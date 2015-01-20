#include "SystemError.hpp"

#include <sstream>

using namespace coconut_tools::system;

std::string SystemError::constructMessage(const std::string& message) {
    std::ostringstream oss;
    if (!message.empty()) {
        oss << message;
    } else {
        oss << "System error.";
    }
    oss << '\n' << "Errno: " << errno << "\nError: " << std::strerror(errno);

    return oss.str();
}
