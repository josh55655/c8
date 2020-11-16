#include "sys.hpp"

namespace chip8::opcode {

void SYS::apply(State &state, word _data) {
    if (_data == RET_OPCODE) {
        state.pc(state.pop());
    } else if (_data == CLS_OPCODE) {
        state.clrscr();
    } else {
        state.push(state.pc());
        state.pc(_data);
    }
}

std::string SYS::toString(word _data) {
    if (_data == RET_OPCODE) {
        return _format(RET_NMEMONIC, _data);
    } else if (_data == CLS_OPCODE) {
        return _format(CLS_NMEMONIC, _data);
    }
    return _format(NMEMONIC, _data);
}

}  // namespace chip8::opcode