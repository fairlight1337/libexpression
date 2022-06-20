cmake_minimum_required(VERSION 3.5)
project(expression)

# Using C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output subpaths are under build directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Our version
set(${PROJECT_NAME}_VERSION_MAJOR_0)
set(${PROJECT_NAME}_VERSION_MINOR_1)

# Option settings
option(EXPRESSION_BUILD_TESTS "Build Expression unit tests" OFF)

set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/3rdparty)

include_directories(
  include)
#  ${THIRDPARTY_DIR}/Catch2/single_include)

link_directories(
  )

add_library(${PROJECT_NAME}
  src/expression/types.cpp)

target_link_libraries(${PROJECT_NAME}
  stdc++)

add_executable(${PROJECT_NAME}-bin
  src/main.cpp)

target_link_libraries(${PROJECT_NAME}-bin
  ${PROJECT_NAME})

### Tests

# enable_testing()

# macro(add_expression_test test_name)
#   message(STATUS "Adding test '${test_name}'")

#   add_executable(${test_name}-test
#     ${PROJECT_SOURCE_DIR}/test/${test_name}_test.cpp)

#   target_link_libraries(${test_name}-test
#     ${PROJECT_NAME})

#   add_test(
#     NAME ${test_name}-test
#     COMMAND ${test_name}-test)
# endmacro()

# if(EXPRESSION_BUILD_TESTS)
#   # Test cases: Expression
#   add_expression_test(expression)

#   # Test cases: And
#   add_expression_test(and)

#   # Test cases: Solution
#   add_expression_test(solution)
# endif()
