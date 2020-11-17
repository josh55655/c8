#ifndef CHIP8_OPCODE_IMPL_HPP
#define CHIP8_OPCODE_IMPL_HPP

#include "opcode.hpp"

namespace chip8::opcode {

byte getReg(word data, byte r);
byte getNibble(word data);
byte getByte(word data);
word getWord(word data);

class VREG : public Opcode {
public:
    VREG() : Opcode(".vreg", VREG_OPCODE) {}
    void apply(State &state, word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODE_IMPL_HPP
