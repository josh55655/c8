#ifndef CHIP8_OPCODE_HPP
#define CHIP8_OPCODE_HPP

#include <string>

#include "defines.hpp"

namespace chip8 {

class State;

class Opcode {
public:
    enum {
        CALL_OPCODE = 0x2000,
        MVI_OPCODE = 0xA000,
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
