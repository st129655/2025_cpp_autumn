cmake_minimum_required(VERSION 3.10)
project(hw4)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(hw4 main.cpp)