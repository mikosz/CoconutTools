function(executable_module MODULE_NAME TEST_LIBRARIES DEPENDENCY_LIBRARIES)

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

  if(${MSVC})
    set(VERTEX_SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main/hlsl/vertex")
	file(GLOB_RECURSE VERTEX_SHADER_SRCS "${VERTEX_SHADER_DIR}/*.hlsl")
	foreach(VERTEX_SHADER ${VERTEX_SHADER_SRCS})
	  set_source_files_properties(
		${VERTEX_SHADER}
		PROPERTIES VS_SHADER_TYPE Vertex VS_SHADER_MODEL 5.0
		VS_SHADER_ENTRYPOINT main
		)
	  set(SRCS ${SRCS} ${VERTEX_SHADER})
	endforeach(VERTEX_SHADER)
		
	set(PIXEL_SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main/hlsl/pixel")
	file(GLOB_RECURSE PIXEL_SHADER_SRCS "${PIXEL_SHADER_DIR}/*.hlsl")
	foreach(PIXEL_SHADER ${PIXEL_SHADER_SRCS})
	  set_source_files_properties(
		${PIXEL_SHADER}
		PROPERTIES VS_SHADER_TYPE Pixel VS_SHADER_MODEL 5.0
		VS_SHADER_ENTRYPOINT main
		)
	  set(SRCS ${SRCS} ${PIXEL_SHADER})
	endforeach(PIXEL_SHADER)
  endif(${MSVC})
  
  if(SRCS)
    add_executable(${MODULE_NAME} ${SRCS} ${HEADERS})
	install(TARGETS ${MODULE_NAME} DESTINATION bin)
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

endfunction(executable_module)