#ifndef COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_
#define COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_

#include <functional>

#include "Appender.hpp"

#include "coconut-tools/concurrent/fake.hpp"

#include "coconut-tools/factory.hpp"

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"
#include "coconut-tools/logger/layout/LayoutFactory.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class AppenderFactory {
public:

	typedef std::string AppenderTypeId;

	AppenderFactory(configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	template <class ConcreteAppenderType>
	void registerType(const AppenderTypeId& appenderTypeId) {
		typeFactory_.registerCreator(
			appenderTypeId,
			policy::creation::Functor<FunctorType>(
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

	layout::LayoutFactory& layoutFactory() {
		return layoutFactory_;
	}

private:

	using FunctorType = std::function<std::unique_ptr<Appender::Initialiser>()>;

	using AppenderTypeFactory = Factory<
		AppenderTypeId,
		std::unique_ptr<Appender::Initialiser>,
		factory::storage::None,
		factory::CreatorRegistry<AppenderTypeId, policy::creation::Functor<FunctorType>, factory::error_policy::ExceptionThrowing>,
		concurrent::FakeMutex
		>;

	AppenderTypeFactory typeFactory_;

	factory::storage::Permanent<Appender::Id, Appender> instanceStorage_;

	configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration_;

	layout::LayoutFactory layoutFactory_;

};

}  // namespace appender
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_ */
