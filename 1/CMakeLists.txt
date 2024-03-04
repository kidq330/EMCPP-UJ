cmake_minimum_required(VERSION 3.10)

# set the project name
project(MatrixProject VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

# add the executable
add_executable(mt matrix_test.cpp)