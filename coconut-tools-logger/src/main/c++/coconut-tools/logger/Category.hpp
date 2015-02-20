#ifndef COCONUTTOOLS_LOGGER_CATEGORY_HPP_
#define COCONUTTOOLS_LOGGER_CATEGORY_HPP_

#include <string>

namespace coconut_tools {
namespace logger {

typedef std::string Category;

}  // namespace logger
}  // namespace coconut_tools

#define CT_LOGGER_CATEGORY(name) \
	const Category& loggerCategory() { \
		static Category category = #name; \
		return category; \
	}

#define CT_LOGGER_LOCAL_CATEGORY(name) \
	auto loggerCategory = []() { return #name; }

#endif /* COCONUTTOOLS_LOGGER_CATEGORY_HPP_ */
