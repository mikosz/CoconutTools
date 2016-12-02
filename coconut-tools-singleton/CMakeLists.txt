set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    ${Boost_SYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )

set(TEST_LIBRARIES
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	)

library_module(coconut-tools-singleton "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" USE_GMOCK ${LIBRARY_TYPE})
