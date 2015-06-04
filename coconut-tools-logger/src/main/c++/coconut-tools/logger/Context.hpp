#ifndef COCONUTTOOLS_LOGGER_CONTEXT_HPP_
#define COCONUTTOOLS_LOGGER_CONTEXT_HPP_

#include <string>

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

#endif /* COCONUTTOOLS_LOGGER_CONTEXT_HPP_ */
