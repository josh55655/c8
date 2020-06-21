#ifndef CHIP8_STATE_HPP
#define CHIP8_STATE_HPP

#include <memory>
#include <tuple>

#include "defines.hpp"

namespace chip8 {

class Opcode;

class State {
    using Decoded = std::pair<Opcode &, word>;
    struct _Pimpl;
    std::unique_ptr<_Pimpl> _impl;

public:
    State();
    virtual ~State();

    /** the system will fetch one opcode from the memory at the location specified by the program counter (pc).
     * In our Chip 8 emulator, data is stored in an array in which each address contains one byte. As one opcode is 2
     * bytes long, we will need to fetch two successive bytes and merge them to get the actual opcode. */
    void fetch();

    /** decode the opcode and check the opcode table to see what it means. */
    Decoded decode();

    void execute(Decoded &op);

    word indexRegister() const;
    void indexRegister(word v);

    friend class StateTest;
};

}  // namespace chip8
#endif  // CHIP8_STATE_HPP
