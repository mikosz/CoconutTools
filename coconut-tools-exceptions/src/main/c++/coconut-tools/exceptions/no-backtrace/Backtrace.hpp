#ifndef COCONUT_TOOLS_EXCEPTIONS_NO_BACKTRACE_BACKTRACE_HPP_
#define COCONUT_TOOLS_EXCEPTIONS_NO_BACKTRACE_BACKTRACE_HPP_

#include <string>
#include <vector>
#include <iosfwd>

namespace coconut_tools {
namespace exceptions {
namespace no_backtrace {

class Backtrace {
public:

    std::ostream& print(std::ostream& os) const;

};

} // namespace no_backtrace
} // namespace exceptions
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_EXCEPTIONS_NO_BACKTRACE_BACKTRACE_HPP_ */
