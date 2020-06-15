cmake_minimum_required(VERSION 3.0)
project(chip8 CXX)

option(WITH_TEST "Enable test module" ON)

set(CMAKE_CXX_STANDARD 20)

add_executable(chip8
               src/main.cpp
               src/interpreter.cpp
               src/state.cpp)

if (WITH_TEST)
    add_subdirectory(test)
endif ()
