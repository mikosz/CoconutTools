set(TEST_LIBRARIES
    coconut-tools-exceptions
    coconut-tools-system
    ${Boost_REGEX_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_TEST_EXEC_MONITOR_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )

library_module(coconut-tools-configuration "${TEST_LIBRARIES}" USE_GMOCK)
