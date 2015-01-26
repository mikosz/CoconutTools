#include "LayoutFactory.hpp"

#include "EmptyLayout.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::layout;

namespace {

void registerBuiltins(LayoutFactory& factory) {
	factory.registerCreator(EmptyLayout::CLASS_NAME, design_pattern::NewCreator<Layout>::makeCreator<EmptyLayout>());
}

} // anonymous namespace

LayoutFactory::LayoutFactory(configuration::ConstLoggerConfigurationPtr loggerConfiguration) :
	loggerConfiguration_(loggerConfiguration)
{
	registerBuiltins(*this);
}
