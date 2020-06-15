cmake_minimum_required(VERSION 3.0)
project(chip8 CXX)

option(WITH_TEST "Enable test module" ON)

set(CMAKE_CXX_STANDARD 20)

add_library(c8support
            src/interpreter.cpp
            src/state.cpp)

add_executable(chip8
               src/main.cpp)

target_link_libraries(chip8 c8support)

if (WITH_TEST)
    add_subdirectory(test)
endif ()
