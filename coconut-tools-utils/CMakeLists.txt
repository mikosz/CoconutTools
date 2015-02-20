set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    )

set(TEST_LIBRARIES
	${Boost_TEST_EXEC_MONITOR_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
	)

library_module(coconut-tools-utils "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" USE_GMOCK)
