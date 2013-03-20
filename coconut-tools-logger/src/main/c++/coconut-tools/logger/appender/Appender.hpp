#ifndef COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_

#include <iosfwd>
#include <string>

#include "../Context.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class Appender {
public:

    virtual ~Appender() {
    }

    void append(const Context& context, const std::string& message);

protected:

    virtual std::ostream& stream() = 0;

};

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_ */
