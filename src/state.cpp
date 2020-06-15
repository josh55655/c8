#include "state.hpp"
#include "state_impl.hpp"

#include <memory>

using std::make_unique;

namespace chip8 {

State::State() : _impl{make_unique<_Pimpl>()} {}

State::~State() {}

void State::fetch() {
    _impl->opcode = (_impl->memory.at(_impl->pc) << 8) | _impl->memory.at(_impl->pc + 1);
    _impl->pc += 2;
}

}  // namespace chip8
