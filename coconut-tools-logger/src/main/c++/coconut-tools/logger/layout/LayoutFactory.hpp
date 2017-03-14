#ifndef COCONUT_TOOLS_LOGGER_LAYOUT_LAYOUTFACTORY_HPP_
#define COCONUT_TOOLS_LOGGER_LAYOUT_LAYOUTFACTORY_HPP_

#include <string>
#include <functional>

#include "Layout.hpp"

#include "coconut-tools/concurrent/fake.hpp"

#include "coconut-tools/policy/creation/Functor.hpp"
#include "coconut-tools/policy/creation/New.hpp"

#include "coconut-tools/factory.hpp"

#include "coconut-tools/utils/Null.hpp"

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"

namespace coconut_tools {
namespace logger {
namespace layout {

class LayoutFactory :
	public Factory<
		std::string,
		factory::CreatorRegistry<std::string, policy::creation::New<Layout>, factory::error_policy::ExceptionThrowing>,
		factory::storage::Permanent,
		concurrent::FakeMutex
		>
{
public:

	using LayoutTypeId = std::string;

	LayoutFactory(configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	template <class ConcreteLayoutType>
	utils::Null registerType(const LayoutTypeId& layoutTypeId) {
		typeFactory_.registerCreator(
			layoutTypeId,
			policy::creation::Functor<FunctorType>(
				[]() {
					return std::unique_ptr<Layout::Initialiser>(
						new Layout::Initialiser(Layout::Initialiser::createInitialisable<ConcreteLayoutType>())
						);
				}
				)
			);

		return utils::Null::null;
	}

	void reloadConfiguration(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	LayoutSharedPtr create(const Layout::Id& layoutId);

private:

	using FunctorType = std::function<std::unique_ptr<Layout::Initialiser>()>;

	using LayoutTypeFactory = Factory<
		LayoutTypeId,
		factory::CreatorRegistry<
			LayoutTypeId,
			policy::creation::Functor<FunctorType>,
			factory::error_policy::ExceptionThrowing
			>,
		factory::storage::None,
		concurrent::FakeMutex
		>;

	LayoutTypeFactory typeFactory_;

	factory::storage::Permanent<Layout::Id, Layout> instanceStorage_;

	configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration_;

};

}  // namespace layout
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_LOGGER_LAYOUT_LAYOUTFACTORY_HPP_ */
