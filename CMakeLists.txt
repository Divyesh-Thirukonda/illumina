cmake_minimum_required(VERSION 3.10)
project(Illumina)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
    extern/FileDialog/*.cpp
)

# GLFW
add_subdirectory(extern/glfw)

# Include paths
include_directories(
    extern/glfw/include
    extern/glad/include
    extern/imgui
    extern/imgui/backends
    extern/FileDialog
    extern/glm
    src
)

# GLAD
add_library(glad extern/glad/glad/src/glad.c)
target_include_directories(glad PUBLIC extern/glad/glad/include)

# IMGUI
file(GLOB IMGUI_SRC
    extern/imgui/*.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC extern/imgui extern/imgui/backends)

# Final executable
add_executable(illumina ${SOURCES})
target_link_libraries(illumina glfw glad imgui)
target_link_libraries(illumina opengl32)
