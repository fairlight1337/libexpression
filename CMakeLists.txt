cmake_minimum_required(VERSION 3.7.2)
project(libexpression)

# Configure clang-tidy
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,-modernize-use-trailing-return-type,-fuchsia-default-arguments-calls,-fuchsia-overloaded-operator,-llvm-header-guard;-header-filter=.*;-warnings-as-errors=*")

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

# Add 3rdparty subdirectory
add_subdirectory(${THIRDPARTY_DIR})

include_directories(
  include
  ${THIRDPARTY_DIR}/Catch2/src
  ${CMAKE_BINARY_DIR}/generated-includes)

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

# Testing
enable_testing()

macro(declare_test name)
  # For the tests, we disable clang-tidy to avoid Catch2 confusion
  set(CMAKE_CXX_CLANG_TIDY "")

  message(STATUS "Add test: ${name}")
  add_executable(test_${name} tests/${name}.cpp)
  target_include_directories(test_${name} PUBLIC 3rdparty/Catch2/single_include)
  target_link_libraries(test_${name} PUBLIC ${PROJECT_NAME} Catch2 Catch2WithMain)
  set_target_properties(test_${name}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)
  add_test(NAME test_${name} COMMAND test_${name})
endmacro()

declare_test(and)
declare_test(equality)
declare_test(or)
