#include "state.hpp"
#include "state_impl.hpp"

#include <algorithm>
#include <memory>

#include "opcode.hpp"

using std::copy;
using std::make_unique;
using std::pair;

namespace chip8 {

State::State() : _impl{make_unique<_Pimpl>()} { srand(word(time(0))); }

State::~State() {}

void State::load(const std::vector<byte> &program, word address) {
    copy(program.begin(), program.end(), _impl->memory.begin() + address);
}

void State::load(const byte *program, std::size_t size, word address) {
    copy(program, program + size, _impl->memory.begin() + address);
}

word State::fetch() {
    word opcode = (_impl->memory.at(_impl->pc) << 8) | _impl->memory.at(_impl->pc + 1);
    _impl->pc += OPCODE_BYTES;

    return opcode;
}

word State::indexRegister() const { return _impl->i; }
void State::indexRegister(word v) { _impl->i = v; }

word State::pc() const { return _impl->pc; }
void State::pc(word _pc) { _impl->pc = _pc; }

void State::push(word datum) {
    _impl->stack[_impl->sp] = datum;
    ++_impl->sp;
}

word State::pop() {
    --_impl->sp;
    return _impl->stack[_impl->sp];
}

byte State::rand() const { return (rand() % 255); }

byte &State::v(byte index) { return _impl->v.at(index); }
byte &State::v(byte index) const { return _impl->v.at(index); }

void State::clrscr() {
    _impl->vMemory.fill(0);
    _impl->videoChanged = true;
}

State::VideoMemory &State::video() const { return _impl->vMemory; }

void State::video(const std::vector<byte> &spriteMap, word address) {
    word cursor{address};
    for (auto p : spriteMap) _impl->vMemory[cursor++] = p;
    _impl->videoChanged = true;
}

std::vector<byte> State::read(word address, word size) const {
    return std::vector<byte>(_impl->memory.begin() + address, _impl->memory.begin() + address + size);
}

bool State::keyPressed(byte key) const { return _impl->key.at(key); }

void State::keyPressed(byte key, bool pressed) { _impl->key.at(key) = pressed; }

byte &State::delayTimer() const { return _impl->delayTimer; }
void State::delayTimer(byte tmr) { _impl->delayTimer = tmr; }

byte &State::soundTimer() const { return _impl->soundTimer; }
void State::soundTimer(byte tmr) { _impl->soundTimer = tmr; }

}  // namespace chip8
