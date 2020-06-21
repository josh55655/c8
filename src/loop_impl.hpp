#ifndef CHIP8_LOOP_IMPL_HPP
#define CHIP8_LOOP_IMPL_HPP

#include "loop.hpp"

namespace chip8 {

struct Loop::_Pimpl {
    State &state;
    word opcode{0};  //!< current opcode to decode

    _Pimpl(State &state) : state(state) {}
};

}  // namespace chip8

#endif  // CHIP8_LOOP_IMPL_HPP
