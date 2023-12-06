cmake_minimum_required(VERSION 3.25)
project(testProj)

set(CMAKE_CXX_STANDARD 17)

add_executable(testProj main.cpp pair.cpp pair.h Matrix.cpp Matrix.h SmartPtr.cpp SmartPtr.h)
