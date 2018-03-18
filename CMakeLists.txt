cmake_minimum_required(VERSION 3.8)
project(test02)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp 02_open_closed.h 05_dependency_inversion.h equal_sides_of_an_array.h sort_the_odd.h sort_the_inner_content.h)
add_executable(test02 ${SOURCE_FILES})
