#include <iostream>

#include "interpreter.hpp"

using namespace chip8;

int main() {
    Interpreter i{std::cout};

    i.init();
    i.load();

    while (true) {
        i.runOne();
        i.updateVideo();
        i.updateKeyboard();
    }

    return 0;
}
