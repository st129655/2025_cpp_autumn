cmake_minimum_required(VERSION 3.14)
project(HW5)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

find_package(GTest REQUIRED)

add_executable(hw5 main.cpp)
target_link_libraries(hw5 GTest::gtest GTest::gtest_main)