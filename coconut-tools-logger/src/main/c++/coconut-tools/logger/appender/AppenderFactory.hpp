#ifndef COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_
#define COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_

#include "Appender.hpp"

#include "coconut-tools/design-pattern/factory.hpp"

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"
#include "coconut-tools/logger/layout/LayoutFactory.hpp"

#include "coconut-tools/concurrent/Lockable.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class AppenderFactory : concurrent::Lockable<AppenderFactory> {
public:

	typedef std::string AppenderTypeId;

	AppenderFactory(configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	template <class ConcreteAppenderType>
	void registerType(const AppenderTypeId& appenderTypeId) {
		typeFactory_.registerCreator(
			appenderTypeId,
			design_pattern::FunctorCreator<std::unique_ptr<Appender::Initialiser> >(
				[]() {
					return std::unique_ptr<Appender::Initialiser>(
							new Appender::Initialiser(Appender::Initialiser::createInitialisable<ConcreteAppenderType>())
							);
				}
				)
			);
	}

	void reloadConfiguration(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	AppenderSharedPtr create(const Appender::Id& appenderId);

	VolatileAppenderSharedPtr create(const Appender::Id& appenderId) volatile {
		return lock()->create(appenderId);
	}

	layout::LayoutFactory& layoutFactory() {
		return layoutFactory_;
	}

private:

	typedef design_pattern::factory::Factory<
		AppenderTypeId,
		std::unique_ptr<Appender::Initialiser>,
		design_pattern::NoStorage,
		design_pattern::FunctorCreator<std::unique_ptr<Appender::Initialiser> >,
		design_pattern::NoLockingPolicy,
		design_pattern::ExceptionThrowingErrorPolicy
		> AppenderTypeFactory;

	AppenderTypeFactory typeFactory_;

	design_pattern::PermanentStorage<Appender::Id, AppenderSharedPtr> instanceStorage_;

	configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration_;

	layout::LayoutFactory layoutFactory_;

};

}  // namespace appender
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_ */
