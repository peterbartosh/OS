cmake_minimum_required(VERSION 3.21)
project(Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(Client main.cpp)

add_library(Number STATIC  ../../Libs/Number/library.cpp)
add_library(Vector SHARED ../../Libs/Vector/library.cpp)

target_link_libraries(Client PRIVATE Number)
target_link_libraries(Client PRIVATE Vector)
