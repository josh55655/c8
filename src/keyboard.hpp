#ifndef CHIP8_KEYBOARD_HPP
#define CHIP8_KEYBOARD_HPP

#include "defines.hpp"

namespace chip8 {

class State;

class KeyboardInterface {
public:
    KeyboardInterface(State &state);
    virtual ~KeyboardInterface() {}

    virtual byte getKey() const = 0;

protected:
    State &_state;
};

class NoKeyboard : public KeyboardInterface {
public:
    NoKeyboard(State &state);
    virtual byte getKey() const;
};

}  // namespace chip8

#endif  // CHIP8_KEYBOARD_HPP
