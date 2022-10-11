# Disable clang-tidy for 3rdparty subprojects
set(CMAKE_CXX_CLANG_TIDY "")

# Add Catch2 for unit testing purposes
set(CATCH_DEVELOPMENT_BUILD OFF)
add_subdirectory(Catch2)
