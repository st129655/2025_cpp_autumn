cmake_minimum_required(VERSION 3.14)
project(HW5)

set(CMAKE_CXX_STANDARD 17)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(hw5 main.cpp)
target_link_libraries(hw5 gtest gtest_main)