cmake_minimum_required(VERSION 3.15)
project(bakutov_lab3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address,undefined,leak")

set(SOURCE_FILES main.cpp priority_queue.cpp)

add_executable(a.out ${SOURCE_FILES})
