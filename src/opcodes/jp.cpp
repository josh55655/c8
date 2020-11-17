#include "jp.hpp"

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

void JP::apply(State &state, word _data) { state.pc(_data); }

string JP::toString(word _data) {
    stringstream ss;
    ss << "jp 0x" << hex << setfill('0') << setw(4) << getWord(_data) << dec << setfill(' ');
    return ss.str();
}

void opcode::JPV0::apply(State &state, word _data) {
    word val = getWord(_data);
    state.pc(state.v(0) + val);
}

string JPV0::toString(word _data) {
    stringstream ss;
    ss << "jp v0, " << hex << setfill('0') << setw(4) << getWord(_data) << dec << setfill(' ');
    return ss.str();
}

}  // namespace chip8::opcode