#ifndef COCONUTTOOLS_LOGGER_CONTEXT_HPP_
#define COCONUTTOOLS_LOGGER_CONTEXT_HPP_

#include <string>

#include "Level.hpp"

namespace coconut_tools {
namespace logger {

struct Context {

    Context(Level level) :
        level(level) {
    }

    Context(Level level, const std::string& file, size_t line, const std::string& function) :
        level(level),
        file(file),
        line(line),
        function(function) {
    }

    Level level;

    std::string file;

    size_t line;

    std::string function;

};

}  // namespace logger
}  // namespace CoconutTools

#endif /* COCONUTTOOLS_LOGGER_CONTEXT_HPP_ */
