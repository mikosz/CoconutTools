# - Find GMock
# Find the GMock includes and library
# This module defines
#  GMOCK_INCLUDE_DIR, where to find gmock.h, etc.
#  GMOCK_LIBRARIES, the libraries needed to use GMock.
#  GMOCK_FOUND, If false, do not try to use GMock.
# also defined, but not for general use are
#  GMOCK_LIBRARY, where to find the GMock library.

if(DEFINED GMOCK_ROOT)
  set(INCLUDE_HINT ${GMOCK_ROOT}/include)
  set(LIBRARY_HINT ${GMOCK_ROOT}/lib/.libs)
endif()

find_path(GMOCK_INCLUDE_DIR gmock/gmock.h HINTS ${INCLUDE_HINT})

set(GMOCK_NAMES ${GMOCK_NAMES} gmock)
find_library(GMOCK_LIBRARY NAMES ${GMOCK_NAMES} HINTS ${LIBRARY_HINT})

# handle the QUIETLY and REQUIRED arguments and set JPEG_FOUND to TRUE if
# all listed variables are TRUE
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMOCK DEFAULT_MSG GMOCK_LIBRARY GMOCK_INCLUDE_DIR)

if(GMOCK_FOUND)
  set(GMOCK_LIBRARIES ${GMOCK_LIBRARY})
endif()

mark_as_advanced(GMOCK_LIBRARY GMOCK_INCLUDE_DIR )
