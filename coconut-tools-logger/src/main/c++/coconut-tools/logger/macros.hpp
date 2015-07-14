#ifndef COCONUTTOOLS_LOGGER_MACROS_HPP_
#define COCONUTTOOLS_LOGGER_MACROS_HPP_

#include "coconut-tools/system/platform.hpp"

#include "Category.hpp"
#include "Context.hpp"
#include "Level.hpp"
#include "GlobalLoggerFactory.hpp"

#define CT_LOGGER_CATEGORY(NAME) \
	const coconut_tools::logger::Category& loggerCategory(coconut_tools::logger::FakeParam) { \
		static coconut_tools::logger::Category category = (NAME); \
		return category; \
		}

#define CT_LOGGER_LOCAL_CATEGORY(NAME) \
	auto loggerCategory = [](coconut_tools::logger::FakeParam) { return (NAME); }

#if defined(CT_COMPILER_GCC) || defined(CT_COMPILER_CLANG)
#	define CT_LOGGER_CONTEXT coconut_tools::logger::Context(loggerCategory(coconut_tools::logger::FakeParam()), __FILE__, __LINE__, __PRETTY_FUNCTION__)
#elif defined(CT_COMPILER_VISUAL_CXX)
#	define CT_LOGGER_CONTEXT coconut_tools::logger::Context(loggerCategory(coconut_tools::logger::FakeParam()), __FILE__, __LINE__, __FUNCSIG__)
#else
#	error "Unsupported compiler"
#endif

#define CT_LOGGER coconut_tools::logger::GlobalLoggerFactory::instance()->create(loggerCategory(coconut_tools::logger::FakeParam()))

#define CT_LOG(LEVEL) \
	if ((LEVEL) < (CT_LOGGER)->getLevel()) { \
	} else (CT_LOGGER)->log((LEVEL), CT_LOGGER_CONTEXT)

#define CT_LOG_TRACE CT_LOG(coconut_tools::logger::Level::TRACE)
#define CT_LOG_DEBUG CT_LOG(coconut_tools::logger::Level::DEBUG)
#define CT_LOG_INFO CT_LOG(coconut_tools::logger::Level::INFO)
#define CT_LOG_WARNING CT_LOG(coconut_tools::logger::Level::WARNING)
#define CT_LOG_ERROR CT_LOG(coconut_tools::logger::Level::ERROR)
#define CT_LOG_CRITICAL CT_LOG(coconut_tools::logger::Level::CRITICAL)

#endif /* COCONUTTOOLS_LOGGER_MACROS_HPP_ */
