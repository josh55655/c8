#include "ld.hpp"

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

void LD::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    state.v(r1) = getByte(_data);
}

string LD::toString(word _data) {
    stringstream ss;
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    ss << NMEMONIC << " v" << hex << int(reg) << ", 0x" << setfill('0') << setw(2) << word(val) << dec << setfill(' ');
    return ss.str();
}

void LDI::apply(State &state, word _data) { state.indexRegister(getWord(_data)); }

string LDI::toString(word _data) {
    stringstream ss;
    word val = getWord(_data);
    ss << NMEMONIC << " i"
       << ", 0x" << setfill('0') << setw(4) << val << dec << setfill(' ');
    return ss.str();
}

}  // namespace chip8::opcode