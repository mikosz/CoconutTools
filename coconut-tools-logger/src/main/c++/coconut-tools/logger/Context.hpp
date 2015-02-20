#ifndef COCONUTTOOLS_LOGGER_CONTEXT_HPP_
#define COCONUTTOOLS_LOGGER_CONTEXT_HPP_

#include <string>

#include "coconut-tools/system/platform.hpp"

#include "Level.hpp"
#include "Category.hpp"

namespace coconut_tools {
namespace logger {

struct Context {

	static const Context DEFAULT;

    Context() :
        line(0)
    {
    }

    Context(const Category& category, const std::string& file, size_t line, const std::string& function) :
		category(category),
        file(file),
        line(line),
        function(function)
    {
    }

	Category category;

    std::string file;

    size_t line;

    std::string function;

};

}  // namespace logger
}  // namespace coconut_tools

#if defined(CT_COMPILER_GCC) || defined(CT_COMPILER_CLANG)
#	define CT_LOGGER_CONTEXT() coconut_tools::logger::Context(loggerCategory(), __FILE__, __LINE__, __PRETTY_FUNCTION__)
#elif defined(CT_COMPILER_VISUAL_CXX)
#	define CT_LOGGER_CONTEXT() coconut_tools::logger::Context(loggerCategory(), __FILE__, __LINE__, __FUNCSIG__)
#else
#	error "Unsupported compiler"
#endif

#endif /* COCONUTTOOLS_LOGGER_CONTEXT_HPP_ */
