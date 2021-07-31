cmake_minimum_required(VERSION 3.8)

project(SimpleDB2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(SimpleDB2 "main.cpp")
