#ifndef COCONUT_TOOLS_LOGGER_LAYOUT_LAYOUTFACTORY_HPP_
#define COCONUT_TOOLS_LOGGER_LAYOUT_LAYOUTFACTORY_HPP_

#include <string>

#include "Layout.hpp"

#include "coconut-tools/design-pattern/factory.hpp"
#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"
#include "coconut-tools/utils/Null.hpp"

namespace coconut_tools {
namespace logger {
namespace layout {

class LayoutFactory :
		public design_pattern::factory::Factory<
			std::string,
			LayoutSharedPtr,
			design_pattern::Permanent,
			design_pattern::NewCreator<Layout>,
			design_pattern::NoLockingPolicy,
			design_pattern::ExceptionThrowingErrorPolicy
			>
{
public:

	typedef std::string LayoutTypeId;

	LayoutFactory(configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	template <class ConcreteLayoutType>
	utils::Null registerType(const LayoutTypeId& layoutTypeId) {
		typeFactory_.registerCreator(
			layoutTypeId,
			design_pattern::FunctorCreator<std::unique_ptr<Layout::Initialiser> >(
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

	typedef design_pattern::factory::Factory<
		LayoutTypeId,
		std::unique_ptr<Layout::Initialiser>,
		design_pattern::None,
		design_pattern::FunctorCreator<std::unique_ptr<Layout::Initialiser> >,
		design_pattern::NoLockingPolicy,
		design_pattern::ExceptionThrowingErrorPolicy
	> LayoutTypeFactory;

	LayoutTypeFactory typeFactory_;

	design_pattern::Permanent<Layout::Id, LayoutSharedPtr> instanceStorage_;

	configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration_;

};

}  // namespace layout
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_LOGGER_LAYOUT_LAYOUTFACTORY_HPP_ */
