set(DEPENDENCY_LIBRARIES
    coconut-tools-logger
    coconut-tools-configuration
    coconut-tools-system
    coconut-tools-exceptions
    )

set(TEST_LIBRARIES
    )

library_module(coconut-tools-serialisation "${TEST_LIBRARIES}" "${DEPENDENCY_LIBRARIES}" USE_GMOCK ${LIBRARY_TYPE})
