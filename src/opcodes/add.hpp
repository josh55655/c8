#ifndef CHIP8_OPCODE_ADD_HPP
#define CHIP8_OPCODE_ADD_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class ADD : public Opcode {
    static constexpr char NMEMONIC[]{"add"};

public:
    ADD() : Opcode(NMEMONIC, ADD_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODE_ADD_HPP
