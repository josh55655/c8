#ifndef CHIP8_OPCODES_CALL_HPP
#define CHIP8_OPCODES_CALL_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class CALL : public Opcode {
public:
    CALL() : Opcode("call", CALL_OPCODE) {}
    void apply(State &state, word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODES_CALL_HPP
