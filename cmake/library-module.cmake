function(library_module MODULE_NAME TEST_LIBRARIES)

  foreach(ARG ${ARGV})
    if (${ARG} STREQUAL "USE_GMOCK")
      set(USE_GMOCK 1)
    endif()
  endforeach()

  set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main/c++")
  file(GLOB_RECURSE SRCS "${SOURCE_DIR}/*.cpp")
  include_directories(${SOURCE_DIR})

  set(TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/test/c++")
  file(GLOB_RECURSE TEST_SRCS "${TEST_SOURCE_DIR}/*.cpp")

  set(FUNCTIONAL_TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/functional-test/c++")
  file(GLOB_RECURSE FUNCTIONAL_TEST_SRCS "${FUNCTIONAL_TEST_SOURCE_DIR}/*.cpp")
  
  if(SRCS)
    set(LIBRARY_PRESENT 1)
    add_library(${MODULE_NAME} SHARED ${SRCS})
    add_library(${MODULE_NAME}_static STATIC ${SRCS})
  endif()

  if(LIBRARY_PRESENT)
    set(TEST_LIBRARIES ${MODULE_NAME} ${TEST_LIBRARIES})
  endif(LIBRARY_PRESENT)

  if(TEST_SRCS)
    set(TEST_NAME ${MODULE_NAME}_unit-test)
    
    if(${USE_GMOCK})
      set(TEST_SRCS ${TEST_SRCS} ${GMOCK_CODE_FILES})
      foreach(GMOCK_INCLUDE ${GMOCK_INCLUDES})
        include_directories(${GMOCK_INCLUDE})
      endforeach(GMOCK_INCLUDE)
    endif(${USE_GMOCK})
    
    add_executable(${TEST_NAME} ${TEST_SRCS})
    target_link_libraries(${TEST_NAME} ${TEST_LIBRARIES})
    add_test(${MODULE_NAME} ${TEST_NAME})
  endif(TEST_SRCS)
  
  if(FUNCTIONAL_TEST_SRCS)
    set(FUNCTIONAL_TEST_NAME ${MODULE_NAME}_functional-test)
    add_executable(${FUNCTIONAL_TEST_NAME} ${FUNCTIONAL_TEST_SRCS})
    target_link_libraries(${FUNCTIONAL_TEST_NAME} ${TEST_LIBRARIES})
    add_test(${MODULE_NAME}-functional ${FUNCTIONAL_TEST_NAME})
  endif(FUNCTIONAL_TEST_SRCS)  
  
endfunction(library_module)

function(add_modules MODULES)

  foreach(MODULE ${MODULES})
    set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}/src/main/c++")
    if(EXISTS ${SOURCE_DIR})
      include_directories(${SOURCE_DIR})
    endif()
  endforeach()

  foreach(MODULE ${MODULES})
    add_subdirectory(${MODULE})
  endforeach()

endfunction(add_modules)
