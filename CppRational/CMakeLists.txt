cmake_minimum_required(VERSION 3.8)

project(Rational VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(Rational "main.cpp")
