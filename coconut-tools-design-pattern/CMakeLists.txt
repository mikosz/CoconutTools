set(TEST_LIBRARIES
    coconut-tools-exceptions
    ${GMOCK_LIBRARIES}
    ${GTEST_LIBRARIES}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_TEST_EXEC_MONITOR_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )

library_module(coconut-tools-design-pattern "${TEST_LIBRARIES}")
