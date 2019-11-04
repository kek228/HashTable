cmake_minimum_required(VERSION 3.15)
project(TEST_TASK)
enable_testing()
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

set(gtest_SOURCE_DIR /Users/nikita/CLionProjects/googletest)
include_directories(${gtest_SOURCE_DIR}/googletest/include)
link_directories(${gtest_SOURCE_DIR}/build/lib)

set(TABLE HashTableWithAnalyser.h HashTable.h LFU.h LRUQueue.h)


add_executable( main main.cpp ${TABLE})
add_executable( TEST_HASH testTable.cpp ${TABLE})
add_executable( TEST_LFU testLFU.cpp ${TABLE})

