cmake_minimum_required(VERSION 3.10)
project(hw4)

# Добавить флаги для MSVC
if(MSVC)
    add_compile_options(/W4 /WX)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(hw4 main.cpp)