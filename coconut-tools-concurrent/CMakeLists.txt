set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
	${Boost_FILESYSTEM_LIBRARY}
    )

set(TEST_LIBRARIES
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    ${Boost_TEST_EXEC_MONITOR_LIBRARY}
    )

library_module(coconut-tools-concurrent "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" ${LIBRARY_TYPE})
