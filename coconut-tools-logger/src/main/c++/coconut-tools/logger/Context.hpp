#ifndef COCONUTTOOLS_LOGGER_CONTEXT_HPP_
#define COCONUTTOOLS_LOGGER_CONTEXT_HPP_

#include <string>

#include "coconut-tools/system/platform.hpp"

#include "Level.hpp"

namespace coconut_tools {
namespace logger {

struct Context {

	static const Context DEFAULT;

    Context() :
        line(0)
    {
    }

    Context(const std::string& file, size_t line, const std::string& function) :
        file(file),
        line(line),
        function(function)
    {
    }

    std::string file;

    size_t line;

    std::string function;

};

}  // namespace logger
}  // namespace coconut_tools

#if defined(COMPILER_GCC)
#	define LOGGER_CONTEXT() coconut_tools::logger::Context(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#elif defined(COMPILER_VISUAL_CXX)
#	define LOGGER_CONTEXT() coconut_tools::logger::Context(__FILE__, __LINE__, __FUNCSIG__)
#else
#	error "Unsupported compiler"
#endif

#endif /* COCONUTTOOLS_LOGGER_CONTEXT_HPP_ */