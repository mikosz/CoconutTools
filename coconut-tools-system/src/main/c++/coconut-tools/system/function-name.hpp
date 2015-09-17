#ifndef COCONUT_TOOLS_SYSTEM_FUNCTIONNAME_HPP_
#define COCONUT_TOOLS_SYSTEM_FUNCTIONNAME_HPP_

#include "platform.hpp"

#if defined(CT_COMPILER_GCC) || defined(CT_COMPILER_CLANG)
#	define CT_FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(CT_COMPILER_VISUAL_CXX)
#	define CT_FUNCTION_NAME __FUNCSIG__
#else
#	error "Unsupported compiler"
#endif /* CT_COMPILER_* */

#endif /* COCONUT_TOOLS_SYSTEM_FUNCTIONNAME_HPP_ */
