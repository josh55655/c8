#include "jp.hpp"

namespace chip8::opcode {

void opcode::JP::apply(State &state, word _data) { state.pc(_data); }

}  // namespace chip8::opcode