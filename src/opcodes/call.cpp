#include "call.hpp"

namespace chip8::opcode {

void opcode::CALL::apply(State &state, word _data) {
    state.push(state.pc());
    state.pc(_data);
}

}  // namespace chip8::opcode