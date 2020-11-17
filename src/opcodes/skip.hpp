#ifndef CHIP8_OPCODES_SE_HPP
#define CHIP8_OPCODES_SE_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class SE : public Opcode {
    static constexpr char NMEMONIC[]{"se"};

public:
    SE() : Opcode(".skip", SE_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SNE : public Opcode {
    static constexpr char NMEMONIC[]{"sne"};

public:
    SNE() : Opcode(".skip", SNE_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SER : public Opcode {
    static constexpr char NMEMONIC[]{"se"};

public:
    SER() : Opcode(".skip", SER_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SNER : public Opcode {
    static constexpr char NMEMONIC[]{"sne"};

public:
    SNER() : Opcode(".skip", SNER_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SKP : public Opcode {
    static constexpr char NMEMONIC[]{"skp"};
    static constexpr word OPCODE{0x009E};
    static constexpr char SKNP_NMEMONIC[]{"sknp"};
    static constexpr word SKNP_OPCODE{0x00A1};

public:
    SKP() : Opcode(".skip", SKP_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODES_SE_HPP
