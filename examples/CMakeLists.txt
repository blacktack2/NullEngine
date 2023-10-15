cmake_minimum_required(VERSION 3.25)
project(NullEngine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC CMAKE_CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_executable(NullEngine ${SRC})
