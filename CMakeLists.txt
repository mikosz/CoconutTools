cmake_minimum_required(VERSION 2.8)

project(CoconutTools)

include("cmake.cfg")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include("library-module")

set(CoconutTools_VERSION_MAJOR 1)
set(CoconutTools_VERSION_MINOR 0)
set(CoconutTools_VERSION_BUGFIX 0)
set(CoconutTools_VERSION_EXTRA "-SNAPSHOT")
set("${CoconutTools_VERSION_MAJOR}.${CoconutTools_VERSION_MINOR}.${CoconutTools_VERSION_BUGFIX}${CoconutTools_VERSION_EXTRA}")

enable_testing()

set(CMAKE_CXX_FLAGS "-ggdb -O0")

# find boost
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system thread test_exec_monitor filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(GMock REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(MODULES
    "coconut-tools-concurrent"
    "coconut-tools-configuration"
    "coconut-tools-exceptions"
    "coconut-tools-system"
    "coconut-tools-test-utils"
    "coconut-tools-utils"
    )

add_modules("${MODULES}")
