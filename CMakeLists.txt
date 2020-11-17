cmake_minimum_required(VERSION 3.0)
project(chip8 CXX)

option(WITH_TEST "Enable test module" ON)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads)

add_library(c8opcodes
        src/opcodes/sys.cpp
        src/opcodes/jp.cpp
        src/opcodes/call.hpp
        src/opcodes/call.cpp
        src/opcodes/se.cpp
        src/opcodes/ld.cpp
        src/opcodes/add.cpp
        src/opcodes/rnd.cpp)

add_library(c8support
        src/interpreter.cpp
        src/state.cpp
        src/opcode.cpp
        src/core.cpp
        src/keyboard.cpp
        src/text_io_handler.cpp
        src/debug_io_handler.cpp)

add_executable(chip8
        src/main.cpp)

target_link_libraries(chip8 PRIVATE c8support c8opcodes Threads::Threads)

if (WITH_TEST)
    add_subdirectory(test)
endif ()
