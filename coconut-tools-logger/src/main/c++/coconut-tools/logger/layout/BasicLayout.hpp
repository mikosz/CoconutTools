#ifndef COCONUTTOOLS_LOGGER_LAYOUT_BASICLAYOUT_HPP_
#define COCONUTTOOLS_LOGGER_LAYOUT_BASICLAYOUT_HPP_

#include "Layout.hpp"

#include <sstream>

namespace coconut_tools {
namespace logger {
namespace layout {

class BasicLayout : public Layout {
public:

	static const std::string CLASS_NAME;

	BasicLayout() {
	}

	std::string format(Level level, const Context& context, const std::string& message) {
		std::ostringstream oss;
		oss << context.category << " [" << level << "] - " << message << '\n';
		return oss.str();
	}

private:

	friend class utils::Initialiser<
		Layout,
		const Id&,
		const logger::configuration::LoggerConfiguration&
	>;

};

} // namespace layout
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LAYOUT_BASICLAYOUT_HPP_ */
