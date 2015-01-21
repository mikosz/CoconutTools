set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    )

set(TEST_LIBRARIES
	${Boost_TEST_EXEC_MONITOR_LIBRARY}
	)

library_module(coconut-tools-utils "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}")
