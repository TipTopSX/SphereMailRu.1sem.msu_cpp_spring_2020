cmake_minimum_required(VERSION 3.14)
project(msu_cpp_spring_2020)

set(CMAKE_CXX_STANDARD 14)

include_directories(01)

add_executable(msu_cpp_spring_2020
        02/parse.cpp
        02/parse.hpp
        02/main.cpp)
