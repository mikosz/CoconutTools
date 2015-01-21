cmake_minimum_required(VERSION 2.8)

project(CoconutTools)

include("cmake.cfg")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include("library-module")

set(CoconutTools_VERSION_MAJOR 1)
set(CoconutTools_VERSION_MINOR 0)
set(CoconutTools_VERSION_BUGFIX 0)
set(CoconutTools_VERSION_EXTRA "-SNAPSHOT")
set("${CoconutTools_VERSION_MAJOR}.${CoconutTools_VERSION_MINOR}.${CoconutTools_VERSION_BUGFIX}${CoconutTools_VERSION_EXTRA}")

option(IS_DEBUG_BUILD "Is debug build" ON)

if(${IS_DEBUG_BUILD})
	set(CMAKE_BUILD_TYPE "Debug")
else()
	set(CMAKE_BUILD_TYPE "Release")
endif()

if(${CMAKE_COMPILER_IS_GNUCXX})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0")
elseif(${MSVC})
	
else()
	message(SEND_ERROR "Unrecognised compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

enable_testing()

# find boost
set(Boost_USE_STATIC_LIBS ON)
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
