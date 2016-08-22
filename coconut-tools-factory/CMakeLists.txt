set(DEPENDENCY_LIBRARIES
    # coconut-tools-exceptions
    # ${Boost_SYSTEM_LIBRARY}
    # ${CMAKE_THREAD_LIBS_INIT}
    )

set(TEST_LIBRARIES
	# ${Boost_TEST_EXEC_MONITOR_LIBRARY}
	)

library_module(coconut-tools-factory "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" USE_GMOCK ${LIBRARY_TYPE})
