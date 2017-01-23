set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    coconut-tools-logger
    ${Boost_SYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )

set(TEST_LIBRARIES
	)

library_module(coconut-tools-factory "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" USE_GMOCK ${LIBRARY_TYPE})
