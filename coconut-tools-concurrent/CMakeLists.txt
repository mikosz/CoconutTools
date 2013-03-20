set(TEST_LIBRARIES ${Boost_THREAD_LIBRARY} ${Boost_TEST_EXEC_MONITOR_LIBRARY})

library_module(coconut-tools-concurrent "${TEST_LIBRARIES}")
