#ifndef COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_

#include <iosfwd>
#include <string>
#include <memory>

#include "coconut-tools/utils/smart-pointer-definitions.hpp"
#include "coconut-tools/utils/Initialisable.hpp"

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"
#include "coconut-tools/logger/layout/LayoutFactory.hpp"
#include "coconut-tools/logger/layout/Layout.hpp"
#include "coconut-tools/logger/Context.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class Appender :
	public utils::Initialisable<
		Appender,
		const std::string&,
		const logger::configuration::LoggerConfiguration&,
		layout::LayoutFactory*
		>
{
public:

	typedef std::string Id;

    virtual ~Appender() {
    }

    void append(Level level, const Context& context, const std::string& message);

protected:

    virtual void doAppend(const std::string& message) = 0;

	Appender() {
	}

	Appender(Level level, layout::LayoutSharedPtr layout) :
		level_(level),
		layout_(layout)
	{
	}

	Appender(
		const Id& id,
		const logger::configuration::LoggerConfiguration& configuration,
		layout::LayoutFactory* layoutFactory
		);

	void doInitialise(
		const Id& id,
		const logger::configuration::LoggerConfiguration& configuration,
		layout::LayoutFactory* layoutFactory
		) override;

private:

	Level level_;

    layout::LayoutSharedPtr layout_;

};

CT_SMART_POINTER_DEFINITONS(Appender);

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_ */
