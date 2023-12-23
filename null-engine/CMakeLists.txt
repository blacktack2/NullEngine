cmake_minimum_required(VERSION 3.25)
project(NullEngine)

set(CMAKE_CXX_STANDARD 20)

# Null Engine options
set(NE_WINDOW "Unspecified" CACHE STRING "Window API")
set_property(CACHE NE_WINDOW PROPERTY STRINGS "Unspecified" "SDL2" "GLFW")

set(NE_DEVICE "Unspecified" CACHE STRING "Graphics device API")
set_property(CACHE NE_DEVICE PROPERTY STRINGS "Unspecified" "Vulkan" "OpenGL")

# Null Engine source
file(GLOB_RECURSE NULL_HEAD CMAKE_CONFIGURE_DEPENDS "include/*.h" "include/*.hpp")  # C++ header
file(GLOB_RECURSE NULL_SRC CMAKE_CONFIGURE_DEPENDS "src/*.cpp")                     # C++ source
file(GLOB_RECURSE NULL_INL CMAKE_CONFIGURE_DEPENDS "include/*.inl")                 # C++ header inline definitions
file(GLOB_RECURSE NULL_DEF CMAKE_CONFIGURE_DEPENDS "include/*.def")                 # C++ X-Macro definitions

add_library(null_engine ${NULL_SRC} ${NULL_INL} ${NULL_DEF} ${NULL_HEAD})
target_include_directories(null_engine PUBLIC include)

# Null Engine dependencies
if (NE_WINDOW STREQUAL "SDL2")
    message("Building with SDL2")
    find_package(SDL2 REQUIRED)
    target_include_directories(null_engine PRIVATE ${SDL_INCLUDE_DIRS})
    target_link_libraries(null_engine ${SDL2_LIBRARIES})
    target_compile_definitions(null_engine PUBLIC NE_BUILD_SDL2)
elseif (NE_DEVICE STREQUAL "GLFW")
    message(FATAL_ERROR "GLFW support not yet implemented")
else()
    message("No window library specified")
endif()

if (NE_DEVICE STREQUAL "Vulkan")
    message("Building with Vulkan")
    find_package(Vulkan REQUIRED)
    target_include_directories(null_engine PRIVATE ${VULKAN_INCLUDE_DIRS})
    target_link_libraries(null_engine ${VULKAN_LIB_LIST} Vulkan::Vulkan)
    target_compile_definitions(null_engine PUBLIC NE_BUILD_VULKAN)
elseif (NE_DEVICE STREQUAL "OpenGL")
    message(FATAL_ERROR "OpenGL support not yet implemented")
else()
    message("No graphics device library specified")
endif()

# Build-level specific settings
if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Building NullEngine in Debug configuration")
    target_compile_definitions(null_engine PUBLIC NE_DEBUG)
    set(CMAKE_CXX_FLAGS_RELEASE "-O0")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Building NullEngine in Release configuration")
    target_compile_definitions(null_engine PUBLIC NE_RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif(CMAKE_BUILD_TYPE MATCHES Final)
    message("Building NullEngine in Final configuration")
    target_compile_definitions(null_engine PUBLIC NE_FINAL)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
    message("Building NullEngine with unknown configuration")
endif()
