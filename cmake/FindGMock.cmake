# - Find GMock
# Find the GMock includes and library
# This module defines
#  GMOCK_INCLUDE_DIR, where to find gmock.h, etc.
#  GMOCK_LIBRARIES, the libraries needed to use GMock.
#  GMOCK_FOUND, If false, do not try to use GMock.
# also defined, but not for general use are
#  GMOCK_LIBRARY, where to find the GMock library.

if(DEFINED GMOCK_ROOT)
  set(GMOCK_ALL_HINT ${GMOCK_ROOT})
  set(GMOCK_INCLUDE_HINT ${GMOCK_ROOT}/include)
endif()

if(DEFINED GTEST_ROOT)
  set(GTEST_ALL_HINT ${GTEST_ROOT})
  set(GTEST_INCLUDE_HINT ${GTEST_ROOT}/include)
endif()

find_path(GMOCK_ALL gmock-all.cc HINTS ${GMOCK_ALL_HINT})
find_path(GMOCK_INCLUDE_DIR gmock/gmock.h HINTS ${GMOCK_INCLUDE_HINT})
get_filename_component(GMOCK_DIR ${GMOCK_ALL} DIRECTORY)

find_path(GTEST_ALL gtest-all.cc HINTS ${GTEST_ALL_HINT})
find_path(GTEST_INCLUDE_DIR gtest/gtest.h HINTS ${GTEST_INCLUDE_HINT})
get_filename_component(GTEST_DIR ${GTEST_ALL} DIRECTORY)

set(GMOCK_CODE_FILES ${GTEST_ALL}/gtest-all.cc ${GMOCK_ALL}/gmock-all.cc)
set(GMOCK_INCLUDES ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} ${GTEST_DIR} ${GMOCK_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMock DEFAULT_MSG GMOCK_CODE_FILES GMOCK_INCLUDES)

mark_as_advanced(GMOCK_CODE_FILES GMOCK_INCLUDES)
