#ifndef COCONUT_TOOLS_EXCEPTIONS_BACKTRACE_HPP_
#define COCONUT_TOOLS_EXCEPTIONS_BACKTRACE_HPP_

#include <iosfwd>

#include "coconut-tools/system/platform.hpp"

#if defined(CT_COMPILER_GCC) && !defined(CT_NO_BACKTRACE)
#	include "gcc/Backtrace.hpp"
namespace coconut_tools { namespace exceptions { using gcc::Backtrace; } }
#else
#	include "no-backtrace/Backtrace.hpp"
namespace coconut_tools { namespace exceptions { using no_backtrace::Backtrace; } }
#endif

namespace coconut_tools {
namespace exceptions {

std::ostream& operator<< (std::ostream& os, const Backtrace& backtrace);

} // namespace exceptions
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_EXCEPTIONS_BACKTRACE_HPP_ */
