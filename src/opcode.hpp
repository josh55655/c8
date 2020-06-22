#ifndef CHIP8_OPCODE_HPP
#define CHIP8_OPCODE_HPP

#include <string>

#include "defines.hpp"

namespace chip8 {

class State;

class Opcode {
public:
    enum {
        DISPATCH0_OPCODE = 0x0000,
        JMP_OPCODE = 0x1000,   //!< Jumps to address NNN.
        CALL_OPCODE = 0x2000,  //!< Calls subroutine at NNN.
        EQ_OPCODE = 0x3000,    //!< Skips the next instruction if VX equals NN.
        NEQ_OPCODE = 0x4000,   //!< Skips the next instruction if VX doesn't equal NN.
        CMP_OPCODE = 0x5000,   //!< Skips the next instruction if VX equals VY (5XY0).
        MVI_OPCODE = 0xA000,   //!< Sets Index Register to the address NNN.
    };

    explicit Opcode(const std::string nmemonic, word code);
    virtual ~Opcode() {}

    virtual void apply(State &state, word _data) = 0;
    void operator()(State &state, word _data);

    const std::string nmemonic;
    const word code;
};

Opcode &makeOpcode(word opcode);

}  // namespace chip8

#endif  // CHIP8_OPCODE_HPP
