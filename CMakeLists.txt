cmake_minimum_required(VERSION 3.16)
project(chip8)

set(CMAKE_CXX_STANDARD 20)

add_executable(chip8 src/main.cpp src/defines.hpp src/state.hpp src/interpreter.hpp src/interpreter.cpp src/state_impl.hpp src/state.cpp)
