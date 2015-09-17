#ifndef COCONUTTOOLS_LOGGER_MACROS_HPP_
#define COCONUTTOOLS_LOGGER_MACROS_HPP_

#include "coconut-tools/system/function-name.hpp"

#include "Category.hpp"
#include "Context.hpp"
#include "Level.hpp"
#include "GlobalLoggerFactory.hpp"

#define CT_LOGGER_CATEGORY(NAME) \
	namespace /* anonymous */ { \
	const coconut_tools::logger::Category& loggerCategory(coconut_tools::logger::FakeParam) { \
		static coconut_tools::logger::Category category = (NAME); \
		return category; \
		} \
	} // anonymous namespace

#define CT_LOGGER_LOCAL_CATEGORY(NAME) \
	auto loggerCategory = [](coconut_tools::logger::FakeParam) { return (NAME); }

#define CT_LOGGER_CONTEXT coconut_tools::logger::Context(loggerCategory(coconut_tools::logger::FakeParam()), __FILE__, __LINE__, CT_FUNCTION_NAME)

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
