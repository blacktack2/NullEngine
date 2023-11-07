cmake_minimum_required(VERSION 3.25)
project(VectorTest)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../null-engine/ ${CMAKE_CURRENT_BINARY_DIR}/null-engine/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../lib/googletest/ ${CMAKE_CURRENT_BINARY_DIR}/googletest/)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_compile_options(-Werror)

add_executable(VectorTest VectorTest.cpp VectorTest.def)

target_link_libraries(VectorTest null_engine gtest gtest_main)
