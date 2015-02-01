#ifndef COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_

#include <iosfwd>
#include <string>
#include <memory>

#include "coconut-tools/utils/smart-pointer-definitions.hpp"

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"
#include "coconut-tools/logger/layout/LayoutFactory.hpp"
#include "coconut-tools/logger/layout/Layout.hpp"
#include "coconut-tools/logger/Context.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class Appender {
public:

	typedef std::string Id;

    virtual ~Appender() {
    }

    void append(Level level, const Context& context, const std::string& message);

protected:

    virtual void doAppend(const std::string& message) = 0;

	Appender(const Id& id, layout::LayoutPtr layout) :
		layout_(layout) {
	}

	Appender(
		const Id& id,
		const logger::configuration::LoggerConfiguration& configuration,
		layout::LayoutFactory* layoutFactory
		);

private:

    layout::LayoutPtr layout_;

};

CT_SMART_POINTER_DEFINITONS(Appender);

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_ */
