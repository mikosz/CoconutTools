#ifndef COCONUTTOOLS_LOGGER_LAYOUT_LAYOUT_HPP_
#define COCONUTTOOLS_LOGGER_LAYOUT_LAYOUT_HPP_

#include <string>

#include "../Context.hpp"

namespace coconut_tools {
namespace logger {
namespace layout {

class Layout {
public:

    virtual ~Layout() {
    }

    virtual std::string format(const Context& context, const std::string& message) = 0;

};

} // namespace layout
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LAYOUT_LAYOUT_HPP_ */
