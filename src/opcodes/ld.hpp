#ifndef CHIP8_OPCODES_LD_HPP
#define CHIP8_OPCODES_LD_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class LD : public Opcode {
    static constexpr char NMEMONIC[]{"ld"};

public:
    LD() : Opcode(".load", LD_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class LDI : public Opcode {
    static constexpr char NMEMONIC[]{"ld"};

public:
    LDI() : Opcode(".load", LDI_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class ADD : public Opcode {
    static constexpr char NMEMONIC[]{"add"};

public:
    ADD() : Opcode(".load", ADD_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class LDX : public Opcode {
    static constexpr char NMEMONIC[]{"ld"};
    static constexpr char ADD_NMEMONIC[]{"add"};
    static constexpr word GET_DT_OPCODE{0x0007};
    static constexpr word GET_KEY_OPCODE{0x000A};
    static constexpr word SET_DT_OPCODE{0x0015};
    static constexpr word SET_ST_OPCODE{0x0018};
    static constexpr word ADDX_OPCODE{0x001E};
    static constexpr word FONT_OPCODE{0x0029};
    static constexpr word BCD_OPCODE{0x0033};
    static constexpr word STORE_OPCODE{0x0055};
    static constexpr word READ_OPCODE{0x0065};

public:
    LDX() : Opcode(".load", LDX_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODES_LD_HPP
