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

# Logger

set(LOGGER_OBJS
  "logger/Logger.cpp"
)

add_library(CoconutTools_Logger SHARED "${SOURCE_DIR}/${LOGGER_OBJS}")

# Tests

set(TEST_OBJS
  "unit-tests.cpp"
  "logger/Logger.cpp"
)

foreach(TEST_OBJ ${TEST_OBJS})
  set(ABSOLUTE_TEST_OBJS ${TEST_SOURCE_DIR}/${TEST_OBJ} ${ABSOLUTE_TEST_OBJS})
endforeach(TEST_OBJ ${TEST_OBJS})

add_executable(unit-tests ${ABSOLUTE_TEST_OBJS})
target_link_libraries(unit-tests ${Boost_LIBRARIES}) 
add_custom_target(test ALL ./unit-tests DEPENDS unit-tests)
