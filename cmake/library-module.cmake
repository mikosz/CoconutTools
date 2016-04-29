include(GenerateExportHeader)

function(library_module MODULE_NAME TEST_LIBRARIES DEPENDENCY_LIBRARIES)

  foreach(ARG ${ARGV})
    if(${ARG} STREQUAL "USE_GMOCK")
      set(DO_USE_GMOCK 1)
    endif()
  endforeach()

  set(STATIC_LIB 0)
  set(DYNAMIC_LIB 0)
  set(BOTH_LIBS 0)
  foreach(ARG ${ARGV})
    if(${ARG} STREQUAL "LINK_BOTH")
      set(STATIC_LIB 1)
      set(DYNAMIC_LIB 1)
      set(BOTH_LIBS 1)
      set(TEST_LINK_SUFFIX "_dynamic")
    elseif(${ARG} STREQUAL "LINK_STATIC")
      set(STATIC_LIB 1)
    elseif(${ARG} STREQUAL "LINK_DYNAMIC")
      set(DYNAMIC_LIB 1)
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
  
  if(${BOTH_LIBS})
    foreach(DEPENDENCY_LIBRARY ${DEPENDENCY_LIBRARIES})
      if(${DEPENDENCY_LIBRARY} MATCHES "^coconut-tools-")
        set(STATIC_DEPENDENCIES "${STATIC_DEPENDENCIES}" "${DEPENDENCY_LIBRARY}_static")
        set(DYNAMIC_DEPENDENCIES "${DYNAMIC_DEPENDENCIES}" "${DEPENDENCY_LIBRARY}_dynamic")
        set(TEST_DEPENDENCIES "${TEST_DEPENDENCIES}" "${DEPENDENCY_LIBRARY}${TEST_LINK_SUFFIX}")
      else()
        set(STATIC_DEPENDENCIES "${STATIC_DEPENDENCIES}" "${DEPENDENCY_LIBRARY}")
        set(DYNAMIC_DEPENDENCIES "${DYNAMIC_DEPENDENCIES}" "${DEPENDENCY_LIBRARY}")
        set(TEST_DEPENDENCIES "${TEST_DEPENDENCIES}" "${DEPENDENCY_LIBRARY}")
      endif()
    endforeach()

    foreach(TEST_LIBRARY ${TEST_LIBRARIES})
      if(${TEST_LIBRARY} MATCHES "^coconut-tools-")
        set(TEST_DEPENDENCIES "${TEST_DEPENDENCIES}" "${DEPENDENCY_LIBRARY}${TEST_LINK_SUFFIX}")
      else()
        set(TEST_DEPENDENCIES "${TEST_DEPENDENCIES}" "${DEPENDENCY_LIBRARY}")
      endif()
    endforeach()
  else()
    set(STATIC_DEPENDENCIES "${DEPENDENCY_LIBRARIES}")
    set(DYNAMIC_DEPENDENCIES "${DEPENDENCY_LIBRARIES}")
    set(TEST_DEPENDENCIES "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}")
  endif()
  
  if(SRCS)
    if(NOT ${STATIC_LIB} AND NOT ${DYNAMIC_LIB})
      message(FATAL_ERROR "LINK_STATIC, LINK_DYNAMIC or LINK_BOTH must be specified for library_module")
    endif()
    
    if(${STATIC_LIB})
      if(${DYNAMIC_LIB})
        set(SUFFIX "_static")
      endif()
      add_library(${MODULE_NAME}${SUFFIX} STATIC ${SRCS} ${HEADERS})
      install(TARGETS ${MODULE_NAME}${SUFFIX} DESTINATION lib)
      set_target_properties(${MODULE_NAME}${SUFFIX} PROPERTIES OUTPUT_NAME ${MODULE_NAME})
      target_link_libraries(${MODULE_NAME}${SUFFIX} ${STATIC_DEPENDENCIES})
    endif()
    
    if(${DYNAMIC_LIB})
      add_definitions(-DCT_DLL_EXPORTS)

      if(${STATIC_LIB})
        set(SUFFIX "_dynamic")
      endif()
      add_library(${MODULE_NAME}${SUFFIX} SHARED ${SRCS} ${HEADERS})
            
      install(TARGETS ${MODULE_NAME}${SUFFIX} DESTINATION lib)
      set_target_properties(${MODULE_NAME}${SUFFIX} PROPERTIES OUTPUT_NAME ${MODULE_NAME})
      target_link_libraries(${MODULE_NAME}${SUFFIX} ${DYNAMIC_DEPENDENCIES})
    endif()

    set(TEST_DEPENDENCIES ${MODULE_NAME}${TEST_LINK_SUFFIX} ${TEST_DEPENDENCIES})
  else()
    add_custom_target(${MODULE_NAME} SOURCES ${HEADERS})
  endif()

  if(TEST_SRCS)
    set(TEST_NAME ${MODULE_NAME}_unit-test)
    
    if(${DO_USE_GMOCK})
      set(TEST_SRCS ${TEST_SRCS} ${GMOCK_CODE_FILES})
      foreach(GMOCK_INCLUDE ${GMOCK_INCLUDES})
        include_directories(${GMOCK_INCLUDE})
      endforeach(GMOCK_INCLUDE)
      if(${MSVC})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_VARIADIC_MAX=10" PARENT_SCOPE)
      endif()
    endif(${DO_USE_GMOCK})
    add_executable(${TEST_NAME} ${TEST_SRCS} ${TEST_HEADERS})
    
    target_link_libraries(${TEST_NAME} ${TEST_DEPENDENCIES})
    add_test(NAME ${MODULE_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)

    if(${MSVC})
      set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
      set_target_properties(${TEST_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
    endif()
  endif(TEST_SRCS)
  
  if(FUNCTIONAL_TEST_SRCS)
    set(FUNCTIONAL_TEST_NAME ${MODULE_NAME}_functional-test)
    add_executable(${FUNCTIONAL_TEST_NAME} ${FUNCTIONAL_TEST_SRCS} ${FUNCTIONAL_TEST_HEADERS})
    target_link_libraries(${FUNCTIONAL_TEST_NAME} ${TEST_DEPENDENCIES})
    add_test(NAME ${MODULE_NAME}-functional COMMAND $<TARGET_FILE:${FUNCTIONAL_TEST_NAME}>)
  endif(FUNCTIONAL_TEST_SRCS)  
  
  if(RESOURCES)
    foreach(RESOURCE ${RESOURCES})
      add_custom_command(
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${RESOURCES_DIR}/${RESOURCE}" "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE}"
        MAIN_DEPENDENCY "${RESOURCES_DIR}/${RESOURCE}"
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE}"
        )
      set(ALL_RESOURCES ${ALL_RESOURCES} "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE}")
    endforeach(RESOURCE)
    add_custom_target(${MODULE_NAME}-copy-resources DEPENDS ${ALL_RESOURCES})
    
    add_dependencies(${MODULE_NAME} ${MODULE_NAME}-copy-resources)
  endif(RESOURCES)
  
  if(${MSVC})
    string(LENGTH "${CMAKE_CURRENT_SOURCE_DIR}/" PARENT_PATH_LEN)
    file(GLOB_RECURSE ALL_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
    foreach(SRC ${ALL_SRCS})
      get_filename_component(SRC_DIR "${SRC}" DIRECTORY)
      string(LENGTH "${SRC_DIR}" SRC_DIR_LEN)
      math(EXPR FILTER_LENGTH "${SRC_DIR_LEN} - ${PARENT_PATH_LEN}")
      string(SUBSTRING "${SRC_DIR}" ${PARENT_PATH_LEN} ${FILTER_LENGTH} FILTER_NAME_PATH)
      string(REPLACE "/" "\\" FILTER_NAME "${FILTER_NAME_PATH}")
      source_group("${FILTER_NAME}" FILES "${SRC}")
    endforeach(SRC)
  endif(${MSVC})
  
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
