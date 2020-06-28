#ifndef CHIP8_OPCODE_IMPL_HPP
#define CHIP8_OPCODE_IMPL_HPP

#include "opcode.hpp"

namespace chip8::opcode {

byte getReg(word data, byte r);
byte getByte(word data);

class JMP : public Opcode {
public:
    JMP() : Opcode("jmp", JMP_OPCODE) {}
    void apply(State &state, word _data) override;
};

class CALL : public Opcode {
public:
    CALL() : Opcode("call", CALL_OPCODE) {}
    void apply(State &state, word _data) override;
};

class EQ : public Opcode {
public:
    EQ() : Opcode("eq", EQ_OPCODE) {}
    void apply(State &state, word _data) override;
};

class NEQ : public Opcode {
public:
    NEQ() : Opcode("neq", NEQ_OPCODE) {}
    void apply(State &state, word _data) override;
};

class CMP : public Opcode {
public:
    CMP() : Opcode("cmp", REQ_OPCODE) {}
    void apply(State &state, word _data) override;
};

class SET : public Opcode {
public:
    SET() : Opcode("set", SET_OPCODE) {}
    void apply(State &state, word _data) override;
};

class ADD : public Opcode {
public:
    ADD() : Opcode("add", ADD_OPCODE) {}
    void apply(State &state, word _data) override;
};

class NREQ : public Opcode {
public:
    NREQ() : Opcode("nreq", NREQ_OPCODE) {}
    void apply(State &state, word _data) override;
};

class MVI : public Opcode {
public:
    MVI() : Opcode("mvi", MVI_OPCODE) {}
    void apply(State &state, word _data) override;
};

class JMPO : public Opcode {
public:
    JMPO() : Opcode("jmpo", JMPO_OPCODE) {}
    void apply(State &state, word _data) override;
};

class RAND : public Opcode {
public:
    RAND() : Opcode("rand", RAND_OPCODE) {}
    void apply(State &state, word _data) override;
};

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

class ROUTINE : public Opcode {
public:
    ROUTINE() : Opcode(".routine", ROUTINES_OPCODE) {}
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
