#include "loop.hpp"
#include "loop_impl.hpp"

#include <memory>

#include "opcode.hpp"
#include "state.hpp"

using std::make_unique;

namespace chip8 {

Loop::Loop(State &state) : _impl(make_unique<_Pimpl>(state)) {}

void Loop::fetch() { _impl->opcode = _impl->state.fetch(); }

Loop::Decoded Loop::decode() { return {makeOpcode(_impl->opcode & 0xF000), _impl->opcode & 0x0FFF}; }

void Loop::execute(Decoded &op) { op.first(_impl->state, op.second); }

}  // namespace chip8
