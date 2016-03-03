cmake_minimum_required(VERSION 3.3)
project(IntroductiontoAlgorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BinarySearchTree.h)
add_executable(IntroductiontoAlgorithms ${SOURCE_FILES})