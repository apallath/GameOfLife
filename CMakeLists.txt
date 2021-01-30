cmake_minimum_required(VERSION 3.10)

project(GameOfLife)

# Require C++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# All .cpp files from src/
file(GLOB SOURCES "src/*.cpp")

add_executable(GameOfLife ${SOURCES})
