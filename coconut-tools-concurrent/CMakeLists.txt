set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
	${Boost_FILESYSTEM_LIBRARY}
    )

set(TEST_LIBRARIES
    )

library_module(coconut-tools-concurrent "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" ${LIBRARY_TYPE})
