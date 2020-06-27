#include "opcode.hpp"
#include "opcode_impl.hpp"

#include <map>
#include <memory>
#include <sys/time.h>

#include "opcode.hpp"
#include "state.hpp"

using std::make_unique;
using std::map;
using std::unique_ptr;

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
        _codes[Opcode::JMP_OPCODE] = make_unique<opcode::JMP>();
        _codes[Opcode::CALL_OPCODE] = make_unique<opcode::CALL>();
        _codes[Opcode::EQ_OPCODE] = make_unique<opcode::EQ>();
        _codes[Opcode::NEQ_OPCODE] = make_unique<opcode::NEQ>();
        _codes[Opcode::REQ_OPCODE] = make_unique<opcode::CMP>();
        _codes[Opcode::SET_OPCODE] = make_unique<opcode::SET>();
        _codes[Opcode::ADD_OPCODE] = make_unique<opcode::ADD>();
        _codes[Opcode::NREQ_OPCODE] = make_unique<opcode::NREQ>();
        _codes[Opcode::MVI_OPCODE] = make_unique<opcode::MVI>();
        _codes[Opcode::JMPO_OPCODE] = make_unique<opcode::JMPO>();
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

}  // namespace chip8
