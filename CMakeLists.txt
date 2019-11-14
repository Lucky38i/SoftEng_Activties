cmake_minimum_required(VERSION 3.15)
project(SoftEng_Activties)

message(STATUS "start running cmake...")

set(CMAKE_CXX_STANDARD 11)
include_directories(.)
add_subdirectory(test)
add_executable(main main.cpp
        binarySearchTree.h)
