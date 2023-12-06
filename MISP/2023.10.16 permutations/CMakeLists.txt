cmake_minimum_required(VERSION 3.11)
project(tasks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(task8 src/task8/main.cpp ${task_platform})