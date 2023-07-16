cmake_minimum_required(VERSION 3.10)
project(toy_robot)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory("lib/googletest")
add_subdirectory("src")
add_subdirectory("tests")