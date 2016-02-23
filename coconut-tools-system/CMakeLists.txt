set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    )

SET(TEST_LIBRARIES
	${Boost_TEST_EXEC_MONITOR_LIBRARY}
	)
	

library_module(coconut-tools-system "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" STATIC SHARED)
