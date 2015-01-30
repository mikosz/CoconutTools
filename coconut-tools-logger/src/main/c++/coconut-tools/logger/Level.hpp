#ifndef COCONUTTOOLS_LOGGER_LEVEL_HPP_
#define COCONUTTOOLS_LOGGER_LEVEL_HPP_

#include <iosfwd>

#include <boost/algorithm/string/case_conv.hpp>

namespace coconut_tools {
namespace logger {

enum class Level {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

std::istream& operator>>(std::istream& is, Level& level);

}  // namespace logger
}  // namespace CoconutTools

#endif /* COCONUTTOOLS_LOGGER_LEVEL_HPP_ */
