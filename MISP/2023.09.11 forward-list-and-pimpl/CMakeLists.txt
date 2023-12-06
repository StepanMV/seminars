cmake_minimum_required(VERSION 3.11)
project(tasks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
    set(task2_platform src/task2/time_meter_win.cpp)
else()
    set(task2_platform src/task2/time_meter_lin.cpp)
endif()

add_executable(task1 src/task1/main.cpp)
add_executable(task2 src/task2/main.cpp ${task2_platform})