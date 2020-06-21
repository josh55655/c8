#ifndef CHIP8_OPCODE_HPP
#define CHIP8_OPCODE_HPP

#include "defines.hpp"

namespace chip8 {

class State;

class Opcode {
public:
    enum {
        MVI_OPCODE = 0xA000,
    };

    Opcode();
    virtual ~Opcode() {}

    virtual void apply(State &state, word _data) = 0;
    void operator()(State &state, word _data);
};

Opcode &makeOpcode(word opcode);

}  // namespace chip8

#endif  // CHIP8_OPCODE_HPP
