# - Find CoconutTools
# Find the CoconutTools includes and library
# This module defines
#  CoconutTools_INCLUDE_DIR, where to find CoconutTools.h, etc.
#  CoconutTools_LIBRARY_DIR, the library dir containing separate CoconutTools libs.
#  CoconutTools_FOUND, If false, do not try to use CoconutTools.
#  CoconutTools_<C>_LIBRARY, where to find the CoconutTools <C> library, where <C> is a
#    component name, such as LOGGER, SYSTEM etc

macro(_FIND_COMPONENT COMPONENT)
  find_library(
    CoconutTools_${COMPONENT}_LIBRARY_DEBUG
    "coconut-tools-${COMPONENT}.d"
    HINTS ${CoconutTools_LIBRARY_HINT}
    PATH_SUFFIXES lib
    )

  find_library(
    CoconutTools_${COMPONENT}_LIBRARY_RELEASE
    "coconut-tools-${COMPONENT}"
    HINTS ${CoconutTools_LIBRARY_HINT}
    PATH_SUFFIXES lib
    )

  set(
    CoconutTools_${COMPONENT}_LIBRARY
    debug ${CoconutTools_${COMPONENT}_LIBRARY_DEBUG}
    optimized ${CoconutTools_${COMPONENT}_LIBRARY_RELEASE}
    )
endmacro(_FIND_COMPONENT)

if(DEFINED CoconutTools_ROOT)
  set(CoconutTools_ALL_HINT ${CoconutTools_ROOT}/src)
  set(CoconutTools_INCLUDE_HINT ${CoconutTools_ROOT}/include)
  set(CoconutTools_LIBRARY_HINT ${CoconutTools_ROOT}/lib)
endif()

find_path(
  CoconutTools_INCLUDE_DIR
  "coconut-tools/version/version.hpp"
  HINTS ${CoconutTools_INCLUDE_HINT}
  PATH_SUFFIXES include
  )

_FIND_COMPONENT(CONFIGURATION)
_FIND_COMPONENT(EXCEPTIONS)
_FIND_COMPONENT(FACTORY)
_FIND_COMPONENT(LOGGER)
_FIND_COMPONENT(SERIALISATION)
_FIND_COMPONENT(SYSTEM)
_FIND_COMPONENT(UTILS)
  
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  CoconutTools
  DEFAULT_MSG
  CoconutTools_INCLUDE_DIR
  CoconutTools_CONFIGURATION_LIBRARY
  CoconutTools_EXCEPTIONS_LIBRARY
  CoconutTools_FACTORY_LIBRARY
  CoconutTools_LOGGER_LIBRARY
  CoconutTools_SERIALISATION_LIBRARY
  CoconutTools_SYSTEM_LIBRARY
  CoconutTools_UTILS_LIBRARY
  )

mark_as_advanced(CoconutTools_LIBRARY_DIR CoconutTools_INCLUDE_DIR)
