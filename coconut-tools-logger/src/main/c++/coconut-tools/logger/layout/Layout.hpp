#ifndef COCONUTTOOLS_LOGGER_LAYOUT_LAYOUT_HPP_
#define COCONUTTOOLS_LOGGER_LAYOUT_LAYOUT_HPP_

#include <string>
#include <memory>

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"

#include "coconut-tools/utils/smart-pointer-definitions.hpp"
#include "coconut-tools/utils/Initialisable.hpp"

#include "../Context.hpp"

namespace coconut_tools {
namespace logger {
namespace layout {

class Layout :
	public utils::Initialisable<
		Layout,
		const std::string&,
		const logger::configuration::LoggerConfiguration&
	>
{
public:

	typedef std::string Id;

    virtual ~Layout() {
    }

    virtual std::string format(Level level, const Context& context, const std::string& message) = 0;

protected:

	Layout() {
	}

	void doInitialise(
		const Id& /*id*/,
		const logger::configuration::LoggerConfiguration& /*configuration*/
		) override {
	}

};

CT_SMART_POINTER_DEFINITONS(Layout);

} // namespace layout
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LAYOUT_LAYOUT_HPP_ */
