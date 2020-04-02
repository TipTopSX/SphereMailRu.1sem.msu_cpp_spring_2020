cmake_minimum_required(VERSION 3.14)
project(msu_cpp_spring_2020)

set(CMAKE_CXX_STANDARD 14)

include_directories(04)

add_executable(msu_cpp_spring_2020
        04/serializer.hpp
        04/main.cpp)
