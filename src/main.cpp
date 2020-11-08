#include <iostream>

#include "interpreter.hpp"

using namespace chip8;

int main(int argc, char *argv[]) {
    Interpreter i{std::cout, std::cin};

    i.init();
    i.load();

    while (true) {
        i.runOne();
        i.updateVideo();
        i.updateKeyboard();
    }

    return 0;
}
