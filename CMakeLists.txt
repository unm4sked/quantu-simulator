cmake_minimum_required(VERSION 3.15)
project(qs)

set(CMAKE_CXX_STANDARD 17)

add_library(
        quantumSimulator STATIC
        lib/quantum.h
        lib/quantum.cpp
)

add_executable(qs main.cpp)

target_link_libraries(qs quantumSimulator)