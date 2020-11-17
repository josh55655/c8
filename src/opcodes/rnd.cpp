#include "rnd.hpp"

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

void RND::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    state.v(reg) = val & state.rand();
}

string RND::toString(word _data) {
    stringstream ss;
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    ss << NMEMONIC << " v" << hex << int(reg) << ", 0x" << setfill('0') << setw(2) << word(val) << dec << setfill(' ');
    return ss.str();
}

}  // namespace chip8::opcode
