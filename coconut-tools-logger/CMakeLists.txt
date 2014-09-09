set(TEST_LIBRARIES
    coconut-tools-logger
    coconut-tools-system
    coconut-tools-exceptions
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_TEST_EXEC_MONITOR_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )

library_module(coconut-tools-logger "${TEST_LIBRARIES}" USE_GMOCK)
