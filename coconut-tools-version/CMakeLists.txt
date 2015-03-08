configure_file("src/main/cmake/coconut-tools/version/version.hpp.in" "coconut-tools/version/version.hpp")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/coconut-tools/version/version.hpp" DESTINATION "include/coconut-tools/version/")
