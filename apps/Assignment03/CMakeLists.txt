cmake_minimum_required(VERSION 3.12)

project(Assignment03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

add_executable(Assignment03 source/VectorTiming.cpp)