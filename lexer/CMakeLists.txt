cmake_minimum_required(VERSION 3.10)
project(LexerProject VERSION 1.0 DESCRIPTION "A simple lexer project")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Specify the executable and its source files
add_executable(LexerTest
  src/token.cc
  src/keyword_table.cc
  src/lexer.cc
  src/Mlexer.cc
  src/Mlexer_test.cc
)

# Link against Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(LexerTest ${GTEST_LIBRARIES} pthread)

# Enable testing
enable_testing()
add_test(NAME LexerTest COMMAND LexerTest)
