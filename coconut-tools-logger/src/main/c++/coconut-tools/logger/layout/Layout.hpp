#ifndef COCONUTTOOLS_LOGGER_LAYOUT_LAYOUT_HPP_
#define COCONUTTOOLS_LOGGER_LAYOUT_LAYOUT_HPP_

#include <string>

#include <boost/shared_ptr.hpp>

#include "../Context.hpp"

namespace coconut_tools {
namespace logger {
namespace layout {

class Layout {
public:

    virtual ~Layout() {
    }

    virtual std::string format(Level level, const Context& context, const std::string& message) = 0;

};

typedef boost::shared_ptr<Layout> LayoutPtr;

} // namespace layout
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LAYOUT_LAYOUT_HPP_ */
