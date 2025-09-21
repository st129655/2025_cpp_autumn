cmake_minimum_required(VERSION 3.10)
project(2025_cpp_autumn)

add_executable(main 2025.09.20_HW1/main.cpp)

if(MSVC)
    # Отключаем только конкретное предупреждение C4100 (неиспользуемый параметр)
    target_compile_options(main PRIVATE /W4 /WX /wd4100)
else()
    target_compile_options(main PRIVATE -Wall -Wextra -Werror -pedantic)
endif()