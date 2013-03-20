set(TEST_LIBRARIES
    coconut-tools-exceptions
    coconut-tools-system
    ${GMOCK_LIBRARIES}
    ${GTEST_LIBRARIES}
    ${Boost_REGEX_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_TEST_EXEC_MONITOR_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    )

library_module(coconut-tools-configuration "${TEST_LIBRARIES}")
