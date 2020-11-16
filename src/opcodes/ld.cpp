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
    ss << NMEMONIC << " V" << hex << int(reg) << ", 0x" << setfill('0') << setw(2) << val << dec << setfill(' ');
    return ss.str();
}

}  // namespace chip8::opcode