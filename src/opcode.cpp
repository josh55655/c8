#include "opcode.hpp"
#include "opcode_impl.hpp"

#include <map>
#include <memory>
#include <vector>

#include "state.hpp"

using std::make_unique;
using std::map;
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
        _codes[Opcode::ROUTINES_OPCODE] = make_unique<opcode::ROUTINE>();
        _codes[Opcode::JMP_OPCODE] = make_unique<opcode::JMP>();
        _codes[Opcode::CALL_OPCODE] = make_unique<opcode::CALL>();
        _codes[Opcode::EQ_OPCODE] = make_unique<opcode::EQ>();
        _codes[Opcode::NEQ_OPCODE] = make_unique<opcode::NEQ>();
        _codes[Opcode::REQ_OPCODE] = make_unique<opcode::CMP>();
        _codes[Opcode::SET_OPCODE] = make_unique<opcode::SET>();
        _codes[Opcode::ADD_OPCODE] = make_unique<opcode::ADD>();
        _codes[Opcode::VREG_OPCODE] = make_unique<opcode::VREG>();
        _codes[Opcode::NREQ_OPCODE] = make_unique<opcode::NREQ>();
        _codes[Opcode::MVI_OPCODE] = make_unique<opcode::MVI>();
        _codes[Opcode::JMPO_OPCODE] = make_unique<opcode::JMPO>();
        _codes[Opcode::RAND_OPCODE] = make_unique<opcode::RAND>();
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

Opcode &makeOpcode(word opcode) {
    word code = opcode & 0xF000;
    return OpCodeContainer::instance().find(code);
}

Opcode::Opcode(const std::string nmemonic, word code) : nmemonic(nmemonic), code(code) {}

void Opcode::operator()(State &state, word _data) { apply(state, _data); }

void opcode::CALL::apply(State &state, word _data) {
    state.push(state.pc());
    state.pc(_data);
}

void opcode::MVI::apply(State &state, word _data) { state.indexRegister(_data); }

void opcode::JMP::apply(State &state, word _data) { state.pc(_data); }

void opcode::EQ::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    if (state.v(reg) == val) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

void opcode::NEQ::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    if (state.v(reg) != val) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

void opcode::CMP::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    if (state.v(r1) == state.v(r2)) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

void opcode::SET::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    state.v(r1) = _data & 0x00FF;
}

void opcode::ADD::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    state.v(reg) += val;
}

void opcode::NREQ::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    if (state.v(r1) != state.v(r2)) {
        // skip next instruction
        state.pc(state.pc() + State::OPCODE_BYTES);
    }
}

void opcode::JMPO::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    state.pc(state.v(reg) + val);
}

void opcode::RAND::apply(State &state, word _data) {
    byte reg = getReg(_data, 0);
    byte val = getByte(_data);
    state.v(reg) = val & state.rand();
}

void opcode::ROUTINE::apply(State &state, word _data) {
    if (_data == 0x00EE) {
        state.pc(state.pop());
    } else if (_data == 0x00E0) {
        state.clrscr();
    } else {
        state.push(state.pc());
        state.pc(_data);
    }
}

void opcode::DRAW::apply(State &state, word _data) {
    byte r1 = getReg(_data, 0);
    byte r2 = getReg(_data, 1);
    byte h = (_data & 0x000F);
    byte y = 0;

    auto vMemory = state.video();
    byte cx = state.v(r1), cy = state.v(r2);
    auto sprite = state.read(state.indexRegister(), h);
    if (state.v(0x0f)) state.video().fill(0);
    while (y < h) {
        vector<byte> row;
        for (byte x = 0; x < 8; ++x) {
            byte p = sprite[y] & (0x80 >> x);
            row.push_back((p > 0) ? 1 : 0);
            if ((vMemory[(cy + y) * CHIP8_COLS + cx + x] != p)) state.v(0xf) = 1;
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
