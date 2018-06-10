cmake_minimum_required(VERSION 3.8)
project(test02)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES main.cpp 02_open_closed.h 05_dependency_inversion.h equal_sides_of_an_array.h sort_the_odd.h sort_the_inner_content.h tortoise_race.h count_duplicates.h fibonacci_tribonacci_and_friends.h rainfall.h simple_encryption_1.h simple_builder.h.h simple_factory.h functional_factory.h composite_pattern.h tank_truck.h condition_variable_test01.h condition_variable_test02.h futures_and_promises.h battleship_field_validator.h twice_linear.h n_linear.h center_of_attention.h)
add_executable(test02 ${SOURCE_FILES})

target_include_directories(test02 PRIVATE SYSTEM "../igloo")
target_compile_options(test02 PRIVATE -Wall -Wpedantic -Wextra -Wno-deprecated-declarations)
