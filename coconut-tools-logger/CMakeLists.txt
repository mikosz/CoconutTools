set(DEPENDENCY_LIBRARIES
    coconut-tools-system
    coconut-tools-exceptions
    coconut-tools-configuration
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )

set(TEST_LIBRARIES
    )

library_module(coconut-tools-logger "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" USE_GMOCK ${LIBRARY_TYPE})
