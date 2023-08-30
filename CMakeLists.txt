cmake_minimum_required(VERSION 3.22.1)

project("PerlinImpl" VERSION 1.0.0 LANGUAGES CXX)

set(SOURCES src/perlin.cpp src/perlin.hpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(PerlinImpl ${SOURCES} "tests/main.cpp")

target_include_directories(PerlinImpl PRIVATE external/libpng)
target_include_directories(PerlinImpl PRIVATE external/png++)

