cmake_minimum_required(VERSION 3.14)
project(bank_account)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_executable(bank_account main.cpp)
target_link_libraries(bank_account gtest gtest_main)