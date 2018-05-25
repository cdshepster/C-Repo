cmake_minimum_required(VERSION 3.0)
project(HW7)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -g3 -Wall -Wextra")
endif()

set(SOURCE_FILES main.cpp)
add_executable(HW7 ${SOURCE_FILES})