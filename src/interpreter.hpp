#ifndef CHIP8_INTERPRETER_HPP
#define CHIP8_INTERPRETER_HPP

#include <iostream>

#include "state.hpp"

namespace chip8 {

class Interpreter {
    State state;
    std::ostream &stdout;

public:
    Interpreter(std::ostream &stdout);

    void init();
    void load();
    void runOne();
    void updateVideo();
    void updateKeyboard();
};

}  // namespace chip8

#endif  // CHIP8_INTERPRETER_HPP
