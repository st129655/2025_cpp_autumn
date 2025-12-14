cmake_minimum_required(VERSION 3.10)
project(HW4)

add_executable(hw4 main.cpp)  # ← ИМЯ ИСПОЛНЯЕМОГО ФАЙЛА

if(MSVC)
    target_compile_options(hw4 PRIVATE /W4 /WX /wd4100)
else()
    target_compile_options(hw4 PRIVATE -Wall -Wextra -Werror -pedantic)
endif()