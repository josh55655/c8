#include "opcode.hpp"
#include "opcode_impl.hpp"

#include <map>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "state.hpp"

#include "opcodes/sys.hpp"
#include "opcodes/jp.hpp"
#include "opcodes/call.hpp"
#include "opcodes/se.hpp"
#include "opcodes/ld.hpp"
#include "opcodes/add.hpp"
#include "opcodes/rnd.hpp"

using std::dec;
using std::hex;
using std::make_unique;
using std::map;
using std::setfill;
using std::setw;
using std::string;
using std::stringstream;
using std::unique_ptr;
using std::vector;

namespace chip8 {

namespace {

using OpcodePtr = unique_ptr<Opcode>;

class OpCodeContainer {
public:
    static OpCodeContainer &instance() {
        static OpCodeContainer _instance;
        return _instance;
    }

    OpCodeContainer(const OpCodeContainer &) = delete;
    OpCodeContainer(OpCodeContainer &&) = delete;

    OpCodeContainer &operator=(const OpCodeContainer &) = delete;
    OpCodeContainer &operator=(OpCodeContainer &&) = delete;

    Opcode &find(word code) { return *_codes.find(code)->second; }

private:
    OpCodeContainer() {
        _codes[Opcode::SYS_OPCODE] = make_unique<opcode::SYS>();
        _codes[Opcode::JP_OPCODE] = make_unique<opcode::JP>();
        _codes[Opcode::CALL_OPCODE] = make_unique<opcode::CALL>();
        _codes[Opcode::SE_OPCODE] = make_unique<opcode::SE>();
        _codes[Opcode::SNE_OPCODE] = make_unique<opcode::SNE>();
        _codes[Opcode::SER_OPCODE] = make_unique<opcode::SER>();
        _codes[Opcode::LD_OPCODE] = make_unique<opcode::LD>();
        _codes[Opcode::ADD_OPCODE] = make_unique<opcode::ADD>();
        _codes[Opcode::VREG_OPCODE] = make_unique<opcode::VREG>();
        _codes[Opcode::SNER_OPCODE] = make_unique<opcode::SNER>();
        _codes[Opcode::LDI_OPCODE] = make_unique<opcode::LDI>();
        _codes[Opcode::JPV0_OPCODE] = make_unique<opcode::JPV0>();
        _codes[Opcode::RND_OPCODE] = make_unique<opcode::RND>();
        _codes[Opcode::DRAW_OPCODE] = make_unique<opcode::DRAW>();
        _codes[Opcode::JKEY_OPCODE] = make_unique<opcode::JKEY>();
        _codes[Opcode::FUNC_OPCODE] = make_unique<opcode::FUNC>();
    }

    map<word, OpcodePtr> _codes;
};

}  // namespace

byte opcode::getReg(word _data, byte r) {
    if (r == 0) return (_data & 0x0F00) >> 8;

    return (_data & 0x00F0) >> 4;
}

byte opcode::getByte(word data) { return data & 0x00FF; }

word opcode::getWord(word data) { return data & 0x0FFF; }

Opcode &makeOpcode(word opcode) {
    word code = opcode & 0xF000;
    return OpCodeContainer::instance().find(code);
}

Opcode::Opcode(const std::string family, word code) : family(family), code(code) {}

void Opcode::operator()(State &state, word _data) { apply(state, _data); }

string Opcode::toString(word _data) { return _format(family, _data); }

string Opcode::_format(const string &nmemonic, word data) const {
    stringstream ss;
    ss << nmemonic << hex << " 0x" << setfill('0') << setw(4) << opcode::getWord(data) << dec << setfill(' ');
    return ss.str();
}

void opcode::DRAW::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    byte h = (_data & 0x000F);
    byte y = 0;

    auto vMemory = state.video();
    byte cx = state.v(r1), cy = state.v(r2);
    auto sprite = state.read(state.indexRegister(), h);
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

void opcode::JKEY::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);

    if (val == 0x9e) {
        if (state.keyPressed(state.v(reg))) state.pc(state.pc() + state.OPCODE_BYTES);
    } else if (val == 0xa1) {
        if (!state.keyPressed(state.v(reg))) state.pc(state.pc() + state.OPCODE_BYTES);
    }
}

void opcode::FUNC::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);

    if (val == 0x07) {
        state.v(reg) = state.delayTimer();
    } else if (val == 0x0A) {
        state.readKey(reg);
    } else if (val == 0x15) {
        state.delayTimer(state.v(reg));
    } else if (val == 0x18) {
        state.soundTimer(state.v(reg));
    } else if (val == 0x1E) {
        state.indexRegister(state.indexRegister() + state.v(reg));
    } else if (val == 0x29) {
        state.indexRegister(state.sprite(state.v(reg)));
    } else if (val == 0x33) {
        state.storeBCD(state.v(reg));
    } else if (val == 0x55) {
        vector<byte> data;
        byte i = 0;
        for (; i <= reg; ++i) data.push_back(state.v(i));
        state.write(data, state.indexRegister());
        state.indexRegister(state.indexRegister() + i + 1);
    } else if (val == 0x65) {
        vector<byte> data = state.read(state.indexRegister(), reg + 1);
        byte i = 0;
        for (; i <= reg; ++i) state.v(i) = data[i];
        state.indexRegister(state.indexRegister() + i + 1);
    }
}

void opcode::VREG::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    byte h = (_data & 0x000F);
    word ris = 0;

    switch (h) {
    case 0:
        state.v(r1) = state.v(r2);
        break;
    case 1:
        state.v(r1) |= state.v(r2);
        break;
    case 2:
        state.v(r1) &= state.v(r2);
        break;
    case 3:
        state.v(r1) ^= state.v(r2);
        break;
    case 4:
        ris = state.v(r1) + state.v(r2);
        state.v(0xf) = (ris & 0xff00) ? 1 : 0;
        state.v(r1) = 0x00ff & ris;
        break;
    case 5:
        state.v(0xf) = (state.v(r1) > state.v(r2)) ? 1 : 0;
        state.v(r1) -= state.v(r2);
        break;
    case 6:
        state.v(0xf) = state.v(r1) & 0x01;
        state.v(r1) >>= 1;
        break;
    case 7:
        state.v(0xf) = (state.v(r1) < state.v(r2)) ? 1 : 0;
        state.v(r1) = state.v(r2) - state.v(r1);
        break;
    case 8:
        state.v(0xf) = (state.v(r1) & 0x80) >> 7;
        state.v(r1) <<= 1;
        break;

    default:
        break;
    }
}

}  // namespace chip8
