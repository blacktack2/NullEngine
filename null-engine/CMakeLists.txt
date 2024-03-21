cmake_minimum_required(VERSION 3.25)
project(NullEngine)

set(CMAKE_CXX_STANDARD 20)

# Null Engine directory structure
set(NE_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(NE_TOOL_ROOT   "${NE_PROJECT_ROOT}/tools")
set(NE_HEADER_ROOT "${NE_PROJECT_ROOT}/include")
set(NE_SRC_ROOT    "${NE_PROJECT_ROOT}/src")
set(NE_SHADER_ROOT "${NE_PROJECT_ROOT}/shaders")

message("Project root: ${NE_PROJECT_ROOT}")
message("Tool root:    ${NE_TOOL_ROOT}")
message("Header root:  ${NE_HEADER_ROOT}")
message("Source root:  ${NE_SRC_ROOT}")
message("Shader root:  ${NE_SHADER_ROOT}")

# Null Engine output directory structure
if (CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(NE_OUTPUT_ROOT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else()
    set(NE_OUTPUT_ROOT ${CMAKE_BINARY_DIR})
endif()
set(NE_SHADER_OUTPUT_ROOT ${NE_OUTPUT_ROOT}/shaders)

message("Project output: ${NE_OUTPUT_ROOT}")
message("Shader output: ${NE_SHADER_OUTPUT_ROOT}")

set(NE_OUTPUT_DEPENDENCIES)

# Null Engine options
set(NE_WINDOW "Unspecified" CACHE STRING "Window API")
set_property(CACHE NE_WINDOW PROPERTY STRINGS "Unspecified" "SDL2" "GLFW")

set(NE_DEVICE "Unspecified" CACHE STRING "Graphics device API")
set_property(CACHE NE_DEVICE PROPERTY STRINGS "Unspecified" "Vulkan" "OpenGL")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Building NullEngine in Debug configuration")
    set(NE_BUILD_MACRO NE_DEBUG)
    set(CMAKE_CXX_FLAGS_RELEASE "-O0")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message("Building NullEngine in Release configuration")
    set(NE_BUILD_MACRO NE_RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif(CMAKE_BUILD_TYPE MATCHES Final)
    message("Building NullEngine in Final configuration")
    set(NE_BUILD_MACRO NE_FINAL)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
    message(FATAL_ERROR "Building NullEngine with unknown configuration")
endif()

# Null Engine source
file(GLOB_RECURSE NE_HEAD    CMAKE_CONFIGURE_DEPENDS "${NE_HEADER_ROOT}/*.h" "${NE_HEADER_ROOT}/*.hpp")     # C++ header
file(GLOB_RECURSE NE_SRC     CMAKE_CONFIGURE_DEPENDS "${NE_SRC_ROOT}/*.cpp")                                # C++ source
file(GLOB_RECURSE NE_INL     CMAKE_CONFIGURE_DEPENDS "${NE_HEADER_ROOT}/*.inl")                             # C++ header inline definitions
file(GLOB_RECURSE NE_DEF     CMAKE_CONFIGURE_DEPENDS "${NE_HEADER_ROOT}/*.def")                             # C++ X-Macro definitions
file(GLOB_RECURSE NE_SHADERS CMAKE_CONFIGURE_DEPENDS "${NE_SHADER_ROOT}/*.frag" "${NE_SHADER_ROOT}/*.vert") # Shaders

set(NE_SHADER_LIST ${NE_HEADER_ROOT}/NE/ShaderList.h)

add_library(null_engine ${NE_SRC} ${NE_INL} ${NE_DEF} ${NE_HEAD} ${NE_SHADER_LIST})
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
    message(FATAL_ERROR "No window library specified")
endif()

if (NE_DEVICE STREQUAL "Vulkan")
    message("Building with Vulkan")
    find_package(Vulkan REQUIRED)
    target_include_directories(null_engine PRIVATE ${VULKAN_INCLUDE_DIRS})
    target_link_libraries(null_engine ${VULKAN_LIB_LIST} Vulkan::Vulkan)
    target_compile_definitions(null_engine PUBLIC NE_BUILD_VULKAN)

    set(NE_SHADER_BYTECODE_FORMAT "spv")
elseif (NE_DEVICE STREQUAL "OpenGL")
    message(FATAL_ERROR "OpenGL support not yet implemented")
else()
    message(FATAL_ERROR "No graphics device library specified")
endif()

find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_program(VIRTUALENV virtualenv)
if (NOT VIRTUALENV)
    message(FATAL_ERROR "Could not find 'virtualenv' in PATH")
endif()
set(VIRTUALENV ${VIRTUALENV} -p python3)

message("virtualenv location: ${VIRTUALENV}")

add_custom_command(
    OUTPUT ${NE_TOOL_ROOT}/venv
    COMMAND ${VIRTUALENV} ${NE_TOOL_ROOT}/venv -q
    COMMENT "Creating python virtual environment"
)
set(NE_OUTPUT_DEPENDENCIES ${NE_OUTPUT_DEPENDENCIES} ${NE_TOOL_ROOT}/venv)
add_custom_command(
    OUTPUT ${NE_TOOL_ROOT}/venv.stamp
    COMMAND ${NE_TOOL_ROOT}/venv/bin/pip -q install -r ${NE_TOOL_ROOT}/requirements.txt --upgrade
    DEPENDS ${NE_TOOL_ROOT}/requirements.txt ${NE_TOOL_ROOT}/venv
    COMMENT "Installing python dependencies"
)
set(NE_OUTPUT_DEPENDENCIES ${NE_OUTPUT_DEPENDENCIES} ${NE_TOOL_ROOT}/venv.stamp)

set(NE_PYTHON_EXEC ${NE_TOOL_ROOT}/venv/bin/python3)

set(NE_SHADER_OUTPUTS)
set(NE_ABS_SHADER_OUTPUTS)
# Null Engine pre-build steps
foreach(SHADER ${NE_SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(SHADER_OUTPUT ${NE_SHADER_OUTPUT_ROOT}/${SHADER_NAME}.${NE_SHADER_BYTECODE_FORMAT})
    message("Adding pre-build step for shader: '${SHADER}' to '${SHADER_OUTPUT}'")
    add_custom_command(
        OUTPUT ${SHADER_OUTPUT}
        COMMAND ${NE_PYTHON_EXEC} compile_shaders.py
        ARGS -vv --dev-platform=linux --build-platform=linux -o "${SHADER_OUTPUT}" "${SHADER}"
        DEPENDS ${SHADER} ${NE_TOOL_ROOT}/compile_shaders.py ${NE_TOOL_ROOT}/venv.stamp
        WORKING_DIRECTORY ${NE_TOOL_ROOT}
        VERBATIM
        COMMENT "Compiling shader source '${SHADER}' into '${SHADER_OUTPUT}'"
    )
    set(NE_OUTPUT_DEPENDENCIES ${NE_OUTPUT_DEPENDENCIES} ${SHADER_OUTPUT})
    file(RELATIVE_PATH SHADER_OUTPUT_RELATIVE ${NE_SHADER_OUTPUT_ROOT} ${SHADER_OUTPUT})
    set(NE_SHADER_OUTPUTS ${NE_SHADER_OUTPUTS} ${SHADER_OUTPUT},${SHADER_OUTPUT_RELATIVE})
    set(NE_ABS_SHADER_OUTPUTS ${NE_ABS_SHADER_OUTPUTS} ${SHADER_OUTPUT})
endforeach()

add_custom_command(
    OUTPUT ${NE_SHADER_LIST}
    COMMAND ${NE_PYTHON_EXEC} create_shader_list.py
    ARGS -vv -o ${NE_SHADER_LIST} -m ${NE_BUILD_MACRO} ${NE_SHADER_OUTPUTS}
    DEPENDS ${NE_ABS_SHADER_OUTPUTS} ${NE_TOOL_ROOT}/create_shader_list.py ${NE_TOOL_ROOT}/venv.stamp
    WORKING_DIRECTORY ${NE_TOOL_ROOT}
    VERBATIM
    COMMENT "Creating shader list"
)

# Null Engine build settings
target_compile_definitions(null_engine PUBLIC ${NE_BUILD_MACRO})

add_custom_target(
    null_engine_prebuild ALL
    DEPENDS ${NE_OUTPUT_DEPENDENCIES} ${NE_SHADER_LIST}
)

add_dependencies(null_engine null_engine_prebuild)
