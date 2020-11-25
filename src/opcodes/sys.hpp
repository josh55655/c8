#ifndef CHIP8_OPCODE_SYS_HPP
#define CHIP8_OPCODE_SYS_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class SYS : public Opcode {
    static constexpr char NMEMONIC[4]{"sys"};
    static constexpr word CLS_OPCODE{0x00E0};
    static constexpr char CLS_NMEMONIC[4]{"cls"};
    static constexpr word RET_OPCODE{0x00EE};
    static constexpr char RET_NMEMONIC[4]{"ret"};

public:
    SYS() : Opcode(".sys", SYS_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODE_SYS_HPP
