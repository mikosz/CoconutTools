set(TEST_LIBRARIES
    coconut-tools-exceptions
    ${Boost_TEST_EXEC_MONITOR_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    )

library_module(coconut-tools-system "${TEST_LIBRARIES}")
