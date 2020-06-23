#include "core.hpp"
#include "core_impl.hpp"

#include <memory>

#include "opcode.hpp"
#include "state.hpp"

using std::make_unique;

namespace chip8 {

Core::Core(State &state) : _impl(make_unique<_Pimpl>(state)) {}
Core::~Core() = default;

void Core::fetch() { _impl->opcode = _impl->state.fetch(); }

Core::Decoded Core::decode() { return {makeOpcode(_impl->opcode & 0xF000), _impl->opcode & 0x0FFF}; }

void Core::execute(Decoded &op) { op.first(_impl->state, op.second); }
void Core::execute(Decoded &&op) { op.first(_impl->state, op.second); }

}  // namespace chip8
