#ifndef CHIP8_TEXT_IO_HANDLER_HPP
#define CHIP8_TEXT_IO_HANDLER_HPP

#include <iostream>
#include <string>

#include "core.hpp"
#include "io_handler.hpp"

namespace chip8 {

class TextIOHandler : public IOHandler {
    std::ostream &_out;
    std::istream &_in;

public:
    TextIOHandler(std::ostream &_out, std::istream &_in);

    void log(const std::string &msg) override;
    void log(word pc, const Core::DecodedOperation &op) override;

    void initScreen() override;
    void draw(const State &_state) override;

    std::vector<byte> load() override;
    std::vector<byte> load(std::istream &provider) override;
};

}  // namespace chip8

#endif  // CHIP8_TEXT_IO_HANDLER_HPP
