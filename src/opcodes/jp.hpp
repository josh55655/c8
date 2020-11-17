#ifndef CHIP8_OPCODES_JP_HPP
#define CHIP8_OPCODES_JP_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class JP : public Opcode {
public:
    JP() : Opcode(".jump", JP_OPCODE) {}
    void apply(State &state, word _data) override;
};

class JPV0 : public Opcode {
public:
    JPV0() : Opcode(".jump", JPV0_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODES_JP_HPP
