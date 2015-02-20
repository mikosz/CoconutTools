#ifndef COCONUTTOOLS_LOGGER_LAYOUT_EMPTYLAYOUT_HPP_
#define COCONUTTOOLS_LOGGER_LAYOUT_EMPTYLAYOUT_HPP_

#include "Layout.hpp"

namespace coconut_tools {
namespace logger {
namespace layout {

class EmptyLayout : public Layout {
public:

	static const std::string CLASS_NAME;

	EmptyLayout() {
	}

	std::string format(Level /* level */, const Context& /* context */, const std::string& message) {
		return message + '\n';
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

#endif /* COCONUTTOOLS_LOGGER_LAYOUT_EMPTYLAYOUT_HPP_ */
