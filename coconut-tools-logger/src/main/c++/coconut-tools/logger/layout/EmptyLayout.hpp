#ifndef COCONUTTOOLS_LOGGER_LAYOUT_EMPTYLAYOUT_HPP_
#define COCONUTTOOLS_LOGGER_LAYOUT_EMPTYLAYOUT_HPP_

#include "Layout.hpp"

namespace coconut_tools {
namespace logger {
namespace layout {

class EmptyLayout : public Layout {
public:

	static const std::string CLASS_NAME;

	std::string format(Level /* level */, const Context& /* context */, const std::string& message) {
		return message + '\n';
	}

};

} // namespace layout
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LAYOUT_EMPTYLAYOUT_HPP_ */
