cmake_minimum_required(VERSION 3.15)
project(bakutov_lab2)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak")

set(SOURCE_FILES main.cpp insort.cpp)

add_executable(a.out ${SOURCE_FILES})
