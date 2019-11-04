cmake_minimum_required(VERSION 3.15)
project(HashTable)


set(gtest_SOURCE_DIR /Users/nikita/CLionProjects/googletest)
include_directories(${gtest_SOURCE_DIR}/googletest/include)
link_directories(${gtest_SOURCE_DIR}/build/lib)

set(CMAKE_CXX_STANDARD 11)
add_executable(test main.cpp HashTable.h)

add_executable( TEST_HASH testTable.cpp HashTable.h)
add_executable( TEST_LFU testLFU.cpp LFU.h LRUQueue.h)

target_link_libraries(TEST_HASH gtest gtest_main)
set_target_properties(TEST_HASH PROPERTIES CXX_STANDARD 11)
#
target_link_libraries(TEST_LFU gtest gtest_main)
set_target_properties(TEST_LFU PROPERTIES CXX_STANDARD 11)
