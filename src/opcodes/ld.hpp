#ifndef CHIP8_OPCODES_LD_HPP
#define CHIP8_OPCODES_LD_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class LD : public Opcode {
    static constexpr char NMEMONIC[]{"ld"};

public:
    LD() : Opcode("load", LD_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODES_LD_HPP
