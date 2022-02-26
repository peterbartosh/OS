cmake_minimum_required(VERSION 3.21)
project(Vector)

set(CMAKE_CXX_STANDARD 14)

add_library(Vector SHARED library.cpp)

add_library(Number STATIC library.cpp)

target_link_libraries(Vector PUBLIC Number)