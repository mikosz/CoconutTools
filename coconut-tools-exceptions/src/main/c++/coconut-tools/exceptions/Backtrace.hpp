#ifndef COCONUT_TOOLS_EXCEPTIONS_BACKTRACE_HPP_
#define COCONUT_TOOLS_EXCEPTIONS_BACKTRACE_HPP_

#include <iosfwd>


#if defined(__GNUC__) && !defined(NO_BACKTRACE)
#include "gcc/Backtrace.hpp"
#define BACKTRACE_H_FOUND
namespace coconut_tools { namespace exceptions { using gcc::Backtrace; } }
#endif

#ifndef BACKTRACE_H_FOUND
#include "no-backtrace/Backtrace.hpp"
#endif

namespace coconut_tools {
namespace exceptions {

std::ostream& operator<< (std::ostream& os, const Backtrace& backtrace);

} // namespace exceptions
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_EXCEPTIONS_BACKTRACE_HPP_ */
