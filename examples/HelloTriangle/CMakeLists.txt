cmake_minimum_required(VERSION 3.25)
project(HelloTriangle)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC CMAKE_CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

set(NE_WINDOW "SDL2")
set(NE_DEVICE "Vulkan")
add_subdirectory(../../null-engine ${CMAKE_CURRENT_BINARY_DIR}/null-engine)

add_executable(HelloTriangle ${SRC})

target_link_libraries(HelloTriangle null_engine)
