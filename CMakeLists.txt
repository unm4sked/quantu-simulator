cmake_minimum_required(VERSION 3.15)
project(quantu_simulator C)

set(CMAKE_C_STANDARD 11)

add_executable(quantu_simulator main.c)
target_link_libraries(quantu_simulator m)