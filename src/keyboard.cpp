#include "keyboard.hpp"

#include "state.hpp"

namespace chip8 {

KeyboardInterface::KeyboardInterface(State &state) : _state(state) {}

NoKeyboard::NoKeyboard(State &state) : KeyboardInterface(state) {}

byte NoKeyboard::getKey() const { return 0; };

}  // namespace chip8