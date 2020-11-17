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

void SE::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    if (state.v(reg) == val) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

string SE::toString(word _data) {
    stringstream ss;
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    ss << NMEMONIC << " v" << hex << int(reg) << ", 0x" << setfill('0') << setw(2) << word(val) << dec << setfill(' ');
    return ss.str();
}

void SNE::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    if (state.v(reg) != val) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

string SNE::toString(word _data) {
    stringstream ss;
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    ss << NMEMONIC << " v" << hex << int(reg) << ", 0x" << setfill('0') << setw(2) << word(val) << dec << setfill(' ');
    return ss.str();
}

void SER::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    if (state.v(r1) == state.v(r2)) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

string SER::toString(word _data) {
    stringstream ss;
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    ss << NMEMONIC << " v" << hex << int(r1) << ", v" << int(r2) << dec << setfill(' ');
    return ss.str();
}

void SNER::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    if (state.v(r1) != state.v(r2)) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

string SNER::toString(word _data) {
    stringstream ss;
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    ss << NMEMONIC << " v" << hex << int(r1) << ", v" << int(r2) << dec << setfill(' ');
    return ss.str();
}

}  // namespace chip8::opcode