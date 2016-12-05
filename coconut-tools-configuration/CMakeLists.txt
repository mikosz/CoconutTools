set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    coconut-tools-system
    ${Boost_REGEX_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )

set(TEST_LIBRARIES
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	)

library_module(coconut-tools-configuration "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" USE_GMOCK ${LIBRARY_TYPE})
