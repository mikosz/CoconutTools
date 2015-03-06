cmake_minimum_required(VERSION 3.0)

project(CoconutTools)

include("cmake.cfg")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include("library-module")

set(CoconutTools_VERSION_MAJOR 1)
set(CoconutTools_VERSION_MINOR 0)
set(CoconutTools_VERSION_BUGFIX 0)
set(CoconutTools_VERSION_EXTRA "-SNAPSHOT")
set(CoconutTools_VERSION
	"${CoconutTools_VERSION_MAJOR}.${CoconutTools_VERSION_MINOR}.${CoconutTools_VERSION_BUGFIX}${CoconutTools_VERSION_EXTRA}"
	)

option(COMPILER_IS_DEBUG_BUILD "Is debug build" ON)
option(COMPILER_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)
option(COMPILER_BOOST_USE_STATIC_LIBS "Use static boost libs" OFF)

if(${COMPILER_IS_DEBUG_BUILD})
	set(CMAKE_BUILD_TYPE "Debug")
else()
	set(CMAKE_BUILD_TYPE "Release")
endif()

if(${CMAKE_COMPILER_IS_GNUCXX})
	if(${COMPILER_WARNINGS_AS_ERRORS})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0")
elseif(${MSVC})
	if(${COMPILER_WARNINGS_AS_ERRORS})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_SCL_SECURE_NO_WARNINGS")
else()
	message(SEND_ERROR "Unrecognised compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

enable_testing()

# find boost
set(Boost_USE_STATIC_LIBS ${COMPILER_BOOST_USE_STATIC_LIBS})
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system thread test_exec_monitor filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# find gmock
find_package(GMock REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})

find_package(Threads REQUIRED)

set(MODULES
    "coconut-tools-concurrent"
    "coconut-tools-configuration"
    "coconut-tools-design-pattern"
    "coconut-tools-exceptions"
    "coconut-tools-logger"
    "coconut-tools-system"
    "coconut-tools-test-utils"
    "coconut-tools-utils"
    )

add_modules("${MODULES}")
