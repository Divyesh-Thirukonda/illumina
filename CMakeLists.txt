# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(illumina)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === GLFW (build from source) ===
# Assumes GLFW source is in externals/glfw
enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/externals/glfw)

# === Find OpenGL ===
if(WIN32)
  set(OPENGL_LIB opengl32)
else()
  find_package(OpenGL REQUIRED)
  set(OPENGL_LIB OpenGL::GL)
endif()

# === Include directories ===
include_directories(
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/externals/glfw/include
)

# === Source files ===
set(SRC_FILES
    src/main.cpp
    src/Engine.cpp
)

# === Executable target ===
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    glfw        # from externals/glfw
    ${OPENGL_LIB}
)

# === Copy GLFW DLL on Windows ===
if(WIN32)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:glfw>
      $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
endif()