cmake_minimum_required(VERSION 3.16.3)

project(PerlinImpl VERSION 1.0.0 LANGUAGES CXX)

set(SOURCES src/perlin.cpp src/perlin.hpp)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(/std:c++20)
else()
    add_compile_options(-Wall -Wpedantic -std=c++2a)
endif()

add_compile_options(-lpng)

add_executable(PerlinImpl ${SOURCES} "tests/main.cpp")

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(PerlinImpl ${PNG_LIBRARY})

