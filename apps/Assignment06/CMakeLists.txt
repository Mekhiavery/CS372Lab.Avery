cmake_minimum_required(VERSION 3.15)
project(DictionaryAssignment LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
add_executable(DictionaryTest source/DictionaryTest.cpp)
target_include_directories(DictionaryTest PRIVATE include)
add_test(NAME DictionaryTest COMMAND DictionaryTest)

add_executable(DictionaryStress source/DictionaryStress.cpp)
target_include_directories(DictionaryStress PRIVATE include)
add_test(NAME DictionaryStress COMMAND DictionaryStress)
