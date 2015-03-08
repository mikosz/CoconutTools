# - Find CoconutTools
# Find the CoconutTools includes and library
# This module defines
#  CoconutTools_INCLUDE_DIR, where to find CoconutTools.h, etc.
#  CoconutTools_LIBRARY_DIR, the library dir containing separate CoconutTools libs.
#  CoconutTools_FOUND, If false, do not try to use CoconutTools.
# also defined, but not for general use are
#  CoconutTools_LIBRARY, where to find the CoconutTools library.

if(DEFINED CoconutTools_ROOT)
  set(CoconutTools_ALL_HINT ${CoconutTools_ROOT}/src)
  set(CoconutTools_INCLUDE_HINT ${CoconutTools_ROOT}/include)
endif()

find_path(
  CoconutTools_INCLUDE_DIR
  "coconut-tools/version/version.hpp"
  HINTS ${CoconutTools_INCLUDE_HINT}
  PATH_SUFFIXES include
  )

find_library(
  CoconutTools_LIBRARY_DIR
  "coconut-tools-utils"
  HINTS ${CoconutTools_LIBRARY_HINT}
  PATH_SUFFIXES lib
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  CoconutTools
  DEFAULT_MSG
  CoconutTools_LIBRARY_DIR CoconutTools_INCLUDE_DIR
  )

mark_as_advanced(CoconutTools_LIBRARY_DIR CoconutTools_INCLUDE_DIR)
