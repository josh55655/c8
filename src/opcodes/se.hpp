#ifndef CHIP8_OPCODES_SE_HPP
#define CHIP8_OPCODES_SE_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class SE : public Opcode {
    static constexpr char NMEMONIC[]{"se"};

public:
    SE() : Opcode(".equal", SE_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SNE : public Opcode {
    static constexpr char NMEMONIC[]{"sne"};

public:
    SNE() : Opcode(".equal", SNE_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

class SER : public Opcode {
    static constexpr char NMEMONIC[]{"ser"};

public:
    SER() : Opcode(".equal", SER_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODES_SE_HPP
