# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("gamegl")

include_directories(${PROJECT_SOURCE_DIR}/dependency/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/dependency/glfw-3.3.8/include)
include_directories(${PROJECT_SOURCE_DIR}/dependency/glm)
include_directories(${PROJECT_SOURCE_DIR}/dependency/stb_image)
include_directories(${PROJECT_SOURCE_DIR}/opengl/include)
include_directories(${PROJECT_SOURCE_DIR}/game/include)

find_library(GLFW glfw3 HINTS ${PROJECT_SOURCE_DIR}/dependency/glfw-3.3.8/lib-vc2022)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRC_DIR "opengl/include/*.h" "game/include/*.h" "opengl/*.cpp" "game/src/*.c" "game/src/*.cpp" "dependency/glad/src/*.c" )
add_executable (gamegl  ${SRC_DIR})
add_compile_definitions("STB_IMAGE_IMPLEMENTATION")
target_link_libraries(gamegl ${GLFW} opengl32)
