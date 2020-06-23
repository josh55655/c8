#ifndef CHIP8_STATE_HPP
#define CHIP8_STATE_HPP

#include <vector>
#include <memory>
#include <tuple>

#include "defines.hpp"

namespace chip8 {

class Opcode;

class State {
    struct _Pimpl;
    std::unique_ptr<_Pimpl> _impl;

public:
    static constexpr word CODE_ADDRESS{0x200};
    static constexpr word OPCODE_BYTES{2};

    State();
    virtual ~State();

    void load(const std::vector<byte> &program, word address = CODE_ADDRESS);
    void load(const byte *program, std::size_t size, word address = CODE_ADDRESS);

    /** the system will fetch one opcode from the memory at the location specified by the program counter (pc).
     * In our Chip 8 emulator, data is stored in an array in which each address contains one byte. As one opcode is 2
     * bytes long, we will need to fetch two successive bytes and merge them to get the actual opcode. */
    virtual word fetch();

    virtual byte &v(byte index);
    virtual byte &v(byte index) const;

    virtual word indexRegister() const;
    virtual void indexRegister(word v);

    virtual word pc() const;
    virtual void pc(word _pc);

    virtual void push(word datum);

    friend class StateTest;
};

}  // namespace chip8
#endif  // CHIP8_STATE_HPP
