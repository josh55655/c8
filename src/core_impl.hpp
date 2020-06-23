#ifndef CHIP8_CORE_IMPL_HPP
#define CHIP8_CORE_IMPL_HPP

#include "core.hpp"

namespace chip8 {

struct Core::_Pimpl {
    State &state;
    word opcode{0};  //!< current opcode to decode

    _Pimpl(State &state) : state(state) {}
};

}  // namespace chip8

#endif  // CHIP8_CORE_IMPL_HPP
