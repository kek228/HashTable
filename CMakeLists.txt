cmake_minimum_required(VERSION 3.15)
project(HashTable)


set(gtest_SOURCE_DIR /Users/nikita/CLionProjects/googletest)
include_directories(${gtest_SOURCE_DIR}/googletest/include)
link_directories(${gtest_SOURCE_DIR}/build/lib)

set(CMAKE_CXX_STANDARD 11)
add_executable(test main.cpp HashTable.h)

add_executable( UNIT_TESTS test.cpp HashTable.h)
target_link_libraries(UNIT_TESTS gtest gtest_main)
set_target_properties(UNIT_TESTS PROPERTIES CXX_STANDARD 11)
