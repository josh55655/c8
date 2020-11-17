#ifndef CHIP8_OPCODE_IMPL_HPP
#define CHIP8_OPCODE_IMPL_HPP

#include "opcode.hpp"

namespace chip8::opcode {

byte getReg(word data, byte r);
byte getByte(word data);
word getWord(word data);

class DRAW : public Opcode {
public:
    DRAW() : Opcode("draw", DRAW_OPCODE) {}
    void apply(State &state, word _data) override;
};

class JKEY : public Opcode {
public:
    JKEY() : Opcode("jkey", JKEY_OPCODE) {}
    void apply(State &state, word _data) override;
};

class FUNC : public Opcode {
public:
    FUNC() : Opcode(".func", FUNC_OPCODE) {}
    void apply(State &state, word _data) override;
};

class VREG : public Opcode {
public:
    VREG() : Opcode(".vreg", VREG_OPCODE) {}
    void apply(State &state, word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODE_IMPL_HPP
