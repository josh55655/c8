#include <iostream>

#include "interpreter.hpp"
#include "debug_io_handler.hpp"
#include "text_io_handler.hpp"

using namespace chip8;

int main(int argc, char *argv[]) {
    Interpreter i{std::make_unique<TextIOHandler>(std::cout, std::cin), argv[1]};
    // Interpreter i{std::make_unique<DebugIOHandler>(), argv[1]};

    i.init();
    i.load();
    i.run();

    return 0;
}
