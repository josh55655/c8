#include "se.hpp"

#include <string>
#include <sstream>
#include <iomanip>

#include "../opcode_impl.hpp"

using std::dec;
using std::hex;
using std::setfill;
using std::setw;
using std::string;
using std::stringstream;

namespace chip8::opcode {

void opcode::SE::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    if (state.v(reg) == val) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

string opcode::SE::toString(word _data) {
    stringstream ss;
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    ss << NMEMONIC << " V" << hex << int(reg) << ", 0x" << setfill('0') << setw(2) << val << dec << setfill(' ');
    return ss.str();
}

void opcode::SNE::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    if (state.v(reg) != val) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

string opcode::SNE::toString(word _data) {
    stringstream ss;
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    ss << NMEMONIC << " V" << hex << int(reg) << ", 0x" << setfill('0') << setw(2) << val << dec << setfill(' ');
    return ss.str();
}

void opcode::SER::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    if (state.v(r1) == state.v(r2)) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

string opcode::SER::toString(word _data) {
    stringstream ss;
    byte reg = getReg(_data, 0);
    byte val = getReg(_data, 1);
    ss << NMEMONIC << " V" << hex << int(reg) << ", v" << int(val) << dec << setfill(' ');
    return ss.str();
}

}  // namespace chip8::opcode