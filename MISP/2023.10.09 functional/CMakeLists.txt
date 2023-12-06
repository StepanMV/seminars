cmake_minimum_required(VERSION 3.11)
project(tasks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
    set(task_platform src/task7/time_meter_win.cpp)
else()
    set(task_platform src/task7/time_meter_lin.cpp)
endif()

add_executable(task7 src/task7/main.cpp ${task_platform})