cmake_minimum_required(VERSION 3.25)
project(NullEngine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE NULL_SRC CMAKE_CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE NULL_INL CMAKE_CONFIGURE_DEPENDS "*.inl")
file(GLOB_RECURSE NULL_HEAD CMAKE_CONFIGURE_DEPENDS "*.h")

add_library(null_engine ${NULL_SRC} ${NULL_INL} ${NULL_HEAD})
target_include_directories(null_engine PUBLIC .)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Building NullEngine in Debug configuration")
    target_compile_definitions(null_engine PUBLIC NE_DEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Building NullEngine in Release configuration")
    target_compile_definitions(null_engine PUBLIC NE_RELEASE)
elseif(CMAKE_BUILD_TYPE MATCHES Final)
    message("Building NullEngine in Final configuration")
    target_compile_definitions(null_engine PUBLIC NE_FINAL)
else()
    message("Building NullEngine with unknown configuration")
endif()
