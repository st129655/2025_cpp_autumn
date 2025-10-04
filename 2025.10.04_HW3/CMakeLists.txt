cmake_minimum_required(VERSION 3.10)
project(HW3)

add_executable(hw3 main.cpp)  # ← ИМЯ ИСПОЛНЯЕМОГО ФАЙЛА

if(MSVC)
    target_compile_options(hw3 PRIVATE /W4 /WX /wd4100)
else()
    target_compile_options(hw3 PRIVATE -Wall -Wextra -Werror -pedantic)
endif()