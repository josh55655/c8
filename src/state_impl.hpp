#ifndef CHIP8_STATE_IMPL_HPP
#define CHIP8_STATE_IMPL_HPP

#include <array>

#include "defines.hpp"
#include "state.hpp"

namespace chip8 {

struct State::_Pimpl {
    std::array<byte, MEMORY_SIZE> memory;               // device memory (reserver + ram + rom)
    std::array<byte, CHIP8_COLS * CHIP8_ROWS> vMemory;  // video memory
    std::array<byte, V_REG_NUM> v;                      // general purpose registers
    std::array<word, STACK_SIZE> stack;                 // function call stack
    std::array<byte, KEYPAD_SIZE> key;                  // keypad event mapper

    word opcode;      // current opcode to decode/execute
    word i;           // register
    word pc;          // program counter
    word sp;          // stack pointer
    byte delayTimer;  // timer register
    byte soundTimer;  // sound timer register, when comes to 0, buzzer ring
};

}  // namespace chip8

#endif  // CHIP8_STATE_IMPL_HPP
