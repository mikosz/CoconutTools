set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
	${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    )

SET(TEST_LIBRARIES
	${Boost_TEST_EXEC_MONITOR_LIBRARY}
	)

library_module(coconut-tools-concurrent "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}")
