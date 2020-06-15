#include <iostream>
#include "interpreter.hpp"

using std::endl;

namespace chip8 {

Interpreter::Interpreter(std::ostream &stdout) : stdout(stdout) {}

void Interpreter::init() { stdout << "CHIP8 Interpreter starting..." << endl; }

void Interpreter::load() {}

void Interpreter::runOne() {}

void Interpreter::updateVideo() {}

void Interpreter::updateKeyboard() {}

}  // namespace chip8
