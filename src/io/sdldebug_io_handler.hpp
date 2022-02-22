#ifndef CHIP8_SDL_DEBUG_IO_HANDLER_HPP
#define CHIP8_SDL_DEBUG_IO_HANDLER_HPP

#include <string>
#include <iostream>
#include <thread>

#include "../core.hpp"
#include "sdl_io_handler.hpp"

namespace chip8 {

class SDLDebugIOHandler : public SDLIOHandler {
public:
    SDLDebugIOHandler(std::istream &_in, size_t magnify = 20);
    ~SDLDebugIOHandler();

    void log(const std::string &msg) override;
    void log(word pc, const Core::DecodedOperation &op) override;

    void init(State &_state) override;
    void draw(const State &_state) override;
};

}  // namespace chip8

#endif  // CHIP8_SDL_DEBUG_IO_HANDLER_HPP
