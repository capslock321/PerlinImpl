cmake_minimum_required(VERSION 3.22.1)

message("Compiling PerlinImpl...")

project("PerlinImpl" VERSION 1.0.0 LANGUAGES CXX)

find_package(OpenCV)

set(sources src/perlin.cpp src/perlin.hpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(PerlinImpl ${sources} "tests/main.cpp")
