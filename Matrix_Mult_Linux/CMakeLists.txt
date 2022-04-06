cmake_minimum_required(VERSION 3.21)
project(Matrix_Mult_Linux)

set(CMAKE_CXX_STANDARD 14)

add_executable(Matrix_Mult_Linux main.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
