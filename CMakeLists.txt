cmake_minimum_required(VERSION 3.7)
project(Project_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp d_except.h d_matrix.h d_random.h knapsack.h)
add_executable(Project_1 ${SOURCE_FILES})