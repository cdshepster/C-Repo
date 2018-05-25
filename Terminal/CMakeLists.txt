cmake_minimum_required(VERSION 3.7.2)
project(HW5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g3 -Wall -Wextra")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(HW4 ${SOURCE_FILES})
