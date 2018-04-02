cmake_minimum_required(VERSION 2.6)
project(sudoku)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -Wall -Wpedantic")
# include_directories(include)

add_executable(
    sudoku
    sudoku.cpp
    sudoku4.cpp
    generate.cpp
    sudoku9.cpp
    sudoku9_util.cpp
    globals.cpp
)
