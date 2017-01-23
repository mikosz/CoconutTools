set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    )

set(TEST_LIBRARIES
    ${CMAKE_THREAD_LIBS_INIT}
    )

library_module(coconut-tools-utils "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" USE_GMOCK ${LIBRARY_TYPE})
