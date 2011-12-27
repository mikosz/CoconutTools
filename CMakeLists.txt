cmake_minimum_required(VERSION 2.8)

project(CoconutTools)
set(CoconutTools_VERSION_MAJOR 0)
set(CoconutTools_VERSION_MINOR 1)

set(SOURCE_DIR "src/main/c++")
set(TEST_SOURCE_DIR "src/test/c++")
set(TARGET_DIR ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})

configure_file("src/main/cmake/version.h.in" "${TARGET_DIR}/include/version.h")

# Includes

include_directories("/usr/include" "src/main/c++/" "${TARGET_DIR}/include")

# Libraries

# Boost

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.46 COMPONENTS thread test_exec_monitor)
if(Boost_FOUND)
  include_directories(${BOOST_INCLUDE_DIRS})
endif(Boost_FOUND)

# Exceptions

add_library(CoconutTools_Exceptions SHARED
    "${SOURCE_DIR}/exceptions/Backtrace.cpp"
    "${SOURCE_DIR}/exceptions/gcc/Backtrace.cpp"
    )

# Logger

add_library(CoconutTools_Logger SHARED
    "${SOURCE_DIR}/logger/Logger.cpp"
    )

# Utils

add_library(CoconutTools_Utils SHARED
    "${SOURCE_DIR}/utils/Formatter.cpp"
    "${SOURCE_DIR}/utils/Null.cpp"
    )

# Tests

add_executable(unit-tests
    "${TEST_SOURCE_DIR}/unit-tests.cpp"
    "${TEST_SOURCE_DIR}/concurrent/Lockable.cpp"
    "${TEST_SOURCE_DIR}/concurrent/LockingPtr.cpp"
    "${TEST_SOURCE_DIR}/design-pattern/Factory.cpp"
    "${TEST_SOURCE_DIR}/logger/Logger.cpp"
    "${TEST_SOURCE_DIR}/utils/Formatter.cpp"
    "${TEST_SOURCE_DIR}/utils/raii-helper.cpp"
    )
    
target_link_libraries(unit-tests ${Boost_LIBRARIES})
target_link_libraries(unit-tests CoconutTools_Exceptions)
target_link_libraries(unit-tests CoconutTools_Utils)
 
add_custom_target(test ALL ./unit-tests DEPENDS unit-tests)
