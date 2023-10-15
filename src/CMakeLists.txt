cmake_minimum_required(VERSION 3.25)
project(NullEngine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE NULL_SRC CMAKE_CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE NULL_HEAD CMAKE_CONFIGURE_DEPENDS "*.h")

add_library(null_engine ${NULL_SRC} ${NULL_HEAD})
target_include_directories(null_engine PUBLIC .)
