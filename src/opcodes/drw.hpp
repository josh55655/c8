#ifndef CHIP8_OPCODE_DRW_HPP
#define CHIP8_OPCODE_DRW_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class DRW : public Opcode {
    static constexpr char NMEMONIC[]{"drw"};

public:
    DRW() : Opcode(".draw", DRW_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODE_DRW_HPP
