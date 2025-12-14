cmake_minimum_required(VERSION 3.10)
project(HW2)

add_executable(hw2 main.cpp)  

if(MSVC)
    target_compile_options(hw2 PRIVATE /W4 /WX /wd4100)
else()
    target_compile_options(hw2 PRIVATE -Wall -Wextra -Werror -pedantic)
endif()