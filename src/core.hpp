#ifndef CHIP8_CORE_HPP
#define CHIP8_CORE_HPP

#include <memory>
#include <tuple>

#include "defines.hpp"

namespace chip8 {

class State;
class Opcode;

class Core {
    struct _Pimpl;
    std::unique_ptr<_Pimpl> _impl;

public:
    using Decoded = std::pair<Opcode &, word>;

    explicit Core(State &state);
    virtual ~Core();

    /** the system will fetch one opcode from the memory at the location specified by the program counter (pc).
     * In our Chip 8 emulator, data is stored in an array in which each address contains one byte. As one opcode is 2
     * bytes long, we will need to fetch two successive bytes and merge them to get the actual opcode. */
    void fetch();

    /** decode the opcode and returns a decoded operation ready to run. */
    Decoded decode();

    /** execude a decoded operation. */
    void execute(Decoded &op);
    void execute(Decoded &&op);
};

}  // namespace chip8

#endif  // CHIP8_CORE_HPP
