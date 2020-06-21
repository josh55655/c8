#include "state.hpp"
#include "state_impl.hpp"

#include <memory>
#include <tuple>

#include "opcode.hpp"

using std::make_unique;
using std::pair;

namespace chip8 {

State::State() : _impl{make_unique<_Pimpl>()} {}

State::~State() {}

void State::fetch() {
    _impl->opcode = (_impl->memory.at(_impl->pc) << 8) | _impl->memory.at(_impl->pc + 1);
    _impl->pc += 2;
}

State::Decoded State::decode() { return {makeOpcode(_impl->opcode & 0xF000), _impl->opcode & 0x0FFF}; }

void State::execute(Decoded &op) { op.first(*this, op.second); }

word State::indexRegister() const { return _impl->i; }
void State::indexRegister(word v) { _impl->i = v; }

}  // namespace chip8
