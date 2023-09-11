cmake_minimum_required(VERSION 3.11)
project(tasks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE sources1 src/task1/*.cpp src/task1/*.h)
file(GLOB_RECURSE sources2 src/task2/*.cpp src/task2/*.h)

add_executable(task1 ${sources1})
add_executable(task2 ${sources2})