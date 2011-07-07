#ifndef COCONUTTOOLS_LOGGER_MACROS_HPP_
#define COCONUTTOOLS_LOGGER_MACROS_HPP_

#include "Context.hpp"

#define LOGGER_CONTEXT(level) CoconutTools::logger::Context(level, __FILE__, __LINE__, __FUNCTION__)

#endif /* COCONUTTOOLS_LOGGER_MACROS_HPP_ */
