#ifndef COCONUT_TOOLS_SYSTEM_PLATFORM_HPP_
#define COCONUT_TOOLS_SYSTEM_PLATFORM_HPP_

namespace coconut_tools {
namespace system {

enum class Platform {
	WINDOWS,
	LINUX,
};

#if defined(_WIN32)
#	define PLATFORM_WINDOWS
const Platform PLATFORM = Platform::WINDOWS;
#elif defined(__linux__)
#	define PLATFORM_LINUX
const Platform PLATFORM = Platform::LINUX;
#else
#	error "Failed to discover the system platform"
#endif

enum class Compiler {
	VISUAL_CXX,
	GCC,
	CLANG,
};

#if defined(_MSC_VER)
#	define COMPILER_VISUAL_CXX
const Compiler COMPILER = Compiler::VISUAL_CXX;
#elif defined(__GCC__)
#	define COMPILER_GCC
const Compiler COMPILER = Compiler::GCC;
#elif defined(__clang__)
#	define COMPILER_CLANG
const Compiler COMPILER = Compiler::CLANG;
#endif

}  // namespace system
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_SYSTEM_PLATFORM_HPP_ */
