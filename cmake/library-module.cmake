function(library_module MODULE_NAME TEST_LIBRARIES DEPENDENCY_LIBRARIES)

  foreach(ARG ${ARGV})
    if(${ARG} STREQUAL "USE_GMOCK")
      set(USE_GMOCK 1)
    endif()
  endforeach()

  set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main/c++")
  file(GLOB_RECURSE SRCS "${SOURCE_DIR}/*.cpp")
  file(GLOB_RECURSE INSTALL_HEADERS RELATIVE "${SOURCE_DIR}" "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.h")
  file(GLOB_RECURSE HEADERS "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.h")
  include_directories(${SOURCE_DIR})

  set(TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/test/c++")
  file(GLOB_RECURSE TEST_SRCS "${TEST_SOURCE_DIR}/*.cpp")
  file(GLOB_RECURSE TEST_HEADERS "${TEST_SOURCE_DIR}/*.hpp" "${TEST_SOURCE_DIR}/*.h")

  set(FUNCTIONAL_TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/functional-test/c++")
  file(GLOB_RECURSE FUNCTIONAL_TEST_SRCS "${FUNCTIONAL_TEST_SOURCE_DIR}/*.cpp")
  file(GLOB_RECURSE FUNCTIONAL_TEST_HEADERS "${FUNCTIONAL_TEST_SOURCE_DIR}/*.hpp" "${FUNCTIONAL_TEST_SOURCE_DIR}/*.h")

  set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main/resources")
  file(GLOB_RECURSE RESOURCES RELATIVE "${RESOURCES_DIR}" "${RESOURCES_DIR}/*")
  
  install(
    DIRECTORY "${SOURCE_DIR}/"
	DESTINATION include
	FILES_MATCHING PATTERN "*.hpp" PATTERN ".h"
	)
  
  if(SRCS)
    add_library(${MODULE_NAME} SHARED ${SRCS} ${HEADERS})
    add_library(${MODULE_NAME}_static STATIC ${SRCS} ${HEADERS})
	install(TARGETS ${MODULE_NAME} ${MODULE_NAME}_static DESTINATION lib)
	set_target_properties(${MODULE_NAME}_static PROPERTIES OUTPUT_NAME ${MODULE_NAME})
	target_link_libraries(${MODULE_NAME} ${DEPENDENCY_LIBRARIES})

    set(TEST_LIBRARIES ${MODULE_NAME} ${TEST_LIBRARIES})
  endif()

  if(TEST_SRCS)
    set(TEST_NAME ${MODULE_NAME}_unit-test)
    
    if(${USE_GMOCK})
      set(TEST_SRCS ${TEST_SRCS} ${GMOCK_CODE_FILES})
      foreach(GMOCK_INCLUDE ${GMOCK_INCLUDES})
        include_directories(${GMOCK_INCLUDE})
      endforeach(GMOCK_INCLUDE)
  	  if(${MSVC})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_VARIADIC_MAX=10" PARENT_SCOPE)
	  endif()
    endif(${USE_GMOCK})
    add_executable(${TEST_NAME} ${TEST_SRCS} ${TEST_HEADERS})
    target_link_libraries(${TEST_NAME} ${TEST_LIBRARIES} ${DEPENDENCY_LIBRARIES})
    add_test(${MODULE_NAME} ${TEST_NAME})

    if(${MSVC})
      set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
      set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
    endif()
  endif(TEST_SRCS)
  
  if(FUNCTIONAL_TEST_SRCS)
    set(FUNCTIONAL_TEST_NAME ${MODULE_NAME}_functional-test)
    add_executable(${FUNCTIONAL_TEST_NAME} ${FUNCTIONAL_TEST_SRCS} ${FUNCTIONAL_TEST_HEADERS})
    target_link_libraries(${FUNCTIONAL_TEST_NAME} ${TEST_LIBRARIES} ${DEPENDENCY_LIBRARIES})
    add_test(${MODULE_NAME}-functional ${FUNCTIONAL_TEST_NAME})
  endif(FUNCTIONAL_TEST_SRCS)  
  
  if(RESOURCES)
    add_custom_target(copy-resources)
    foreach(RESOURCE ${RESOURCES})
      add_custom_command(
	    TARGET copy-resources
	    POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E copy "${RESOURCES_DIR}/${RESOURCE}" "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE}"
	    )
	endforeach(RESOURCE)
	add_dependencies(${MODULE_NAME} copy-resources)
  endif(RESOURCES)
  
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
