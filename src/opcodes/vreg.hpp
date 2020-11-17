#ifndef CHIP8_OPCODE_VREG_HPP
#define CHIP8_OPCODE_VREG_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class VREG : public Opcode {
    static const std::string NMEMONIC[];

public:
    VREG() : Opcode(".vreg", VREG_OPCODE) {}
    bool valid(word _data) override;
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODE_VREG_HPP
