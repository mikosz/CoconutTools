set(DEPENDENCY_LIBRARIES
    coconut-tools-exceptions
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    )

SET(TEST_LIBRARIES
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )
	
library_module(coconut-tools-system "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" ${LIBRARY_TYPE})
