cmake_minimum_required(VERSION 3.25)
project(Example)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC CMAKE_CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_subdirectory(../../null-engine ${CMAKE_CURRENT_BINARY_DIR}/null-engine)

add_executable(Example ${SRC})

target_link_libraries(Example null_engine)
