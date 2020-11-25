#ifndef CHIP8_OPCODE_RND_HPP
#define CHIP8_OPCODE_RND_HPP

#include "../defines.hpp"
#include "../opcode.hpp"
#include "../state.hpp"

namespace chip8::opcode {

class RND : public Opcode {
    static constexpr char NMEMONIC[4]{"rnd"};

public:
    RND() : Opcode(".random", RND_OPCODE) {}
    void apply(State &state, word _data) override;
    std::string toString(word _data) override;
};

}  // namespace chip8::opcode

#endif  // CHIP8_OPCODE_RND_HPP
