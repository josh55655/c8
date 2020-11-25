#ifndef CHIP8_OPCODES_SE_HPP
#define CHIP8_OPCODES_SE_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class SE : public Opcode {
    static constexpr char NMEMONIC[3]{"se"};

public:
    SE() : Opcode(".skip", SE_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SNE : public Opcode {
    static constexpr char NMEMONIC[4]{"sne"};

public:
    SNE() : Opcode(".skip", SNE_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SER : public Opcode {
    static constexpr char NMEMONIC[3]{"se"};

public:
    SER() : Opcode(".skip", SER_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SNER : public Opcode {
    static constexpr char NMEMONIC[4]{"sne"};

public:
    SNER() : Opcode(".skip", SNER_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SKP : public Opcode {
    static constexpr char NMEMONIC[4]{"skp"};
    static constexpr word OPCODE{0x009E};
    static constexpr char SKNP_NMEMONIC[5]{"sknp"};
    static constexpr word SKNP_OPCODE{0x00A1};

public:
    SKP() : Opcode(".skip", SKP_OPCODE) {}
    bool valid(word _data) override;
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODES_SE_HPP
