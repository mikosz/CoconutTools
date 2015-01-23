#include "AppenderFactory.hpp"

#include "ConsoleAppender.hpp"
#include "DebugWindowAppender.hpp"
#include "FileAppender.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

namespace {

void registerBuiltins(AppenderFactory& factory) {
	factory.registerCreator(ConsoleAppender::CLASS_NAME, design_pattern::factory::NewCreator<Appender>::makeCreator<ConsoleAppender>());
	factory.registerCreator(DebugWindowAppender::CLASS_NAME, design_pattern::factory::NewCreator<Appender>::makeCreator<DebugWindowAppender>());
	factory.registerCreator(FileAppender::CLASS_NAME, design_pattern::factory::NewCreator<Appender>::makeCreator<FileAppender>());
}

} // anonymous namespace

AppenderFactory::AppenderFactory() {
	registerBuiltins(*this);
}
