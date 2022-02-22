#include "drw.hpp"

#include <array>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

#include "../opcode_impl.hpp"

using std::array;
using std::dec;
using std::hex;
using std::setfill;
using std::setw;
using std::string;
using std::stringstream;
using std::vector;

namespace chip8::opcode {

void DRW::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    byte h = getNibble(_data);
    byte y = 0;

    auto vMemory = state.video();
    byte cx = state.v(r1), cy = state.v(r2);
    auto sprite = state.read(state.indexRegister(), h);
    state.v(0xf) = 0;

    while (y < h) {
        vector<byte> row;
        for (byte x = 0; x < 8; ++x) {
            byte current = vMemory[(cy + y) * CHIP8_COLS + cx + x];
            byte p = (sprite[y] & (0x80 >> x)) ^ current;
            row.push_back(p);
            if (current && !p) state.v(0xf) = 1;
        }
        state.video(row, (cy + y) * CHIP8_COLS + cx);
        ++y;
    }
}

string DRW::toString(word _data) {
    stringstream ss;
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    byte h = getNibble(_data);

    ss << NMEMONIC << " v" << hex << int(r1) << ", v" << int(r2) << ", 0x" << setw(1) << word(h) << dec;
    return ss.str();
}

}  // namespace chip8::opcode
