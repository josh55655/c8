#ifndef CHIP8_KEYBOARD_HPP
#define CHIP8_KEYBOARD_HPP

#include "state.hpp"

namespace chip8 {

class KeyboardInterface {
public:
    KeyboardInterface(State &state);
    virtual ~KeyboardInterface();

    virtual byte getKey() const = 0;
};

}  // namespace chip8

#endif  // CHIP8_KEYBOARD_HPP
