cmake_minimum_required(VERSION 3.5.1)

project(minesweeper)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES main.cpp Board.cpp)

set(CMAKE_BUILD_TYPE Debug)
add_executable(minesweeper ${SOURCES})
