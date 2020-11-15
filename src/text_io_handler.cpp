#include "text_io_handler.hpp"

#include <iomanip>
#include <iostream>
#include <string>

#include "core.hpp"
#include "opcode.hpp"
#include "state.hpp"

using std::dec;
using std::endl;
using std::hex;
using std::istream;
using std::ostream;
using std::setfill;
using std::setw;
using std::stringstream;
using std::to_string;
using std::vector;

namespace chip8 {

TextIOHandler::TextIOHandler(ostream &_out, istream &_in) : _out(_out), _in(_in) {}

void TextIOHandler::log(const std::string &msg) { _out << msg << endl; }

void TextIOHandler::log(word pc, const Core::DecodedOperation &op) {
    _out << "\x1B[1;1H"
         << "\x1B[2K";
    _out << "Read PC: 0x" << setw(4) << setfill('0') << hex << pc << " opcode: " << op.first.nmemonic << " 0x"
         << setw(4) << op.second << dec << setfill(' ') << endl;
}

void TextIOHandler::initScreen() {
    _out << "\x1B[2J"
         << "\x1B[1;1H";
}

void TextIOHandler::draw(const State &_state) {
    stringstream ss;
    auto &v = _state.video();
    for (int i = 0; i < CHIP8_ROWS; ++i) {
        for (int j = 0; j < CHIP8_COLS; ++j) {
            ss << (v[i * CHIP8_COLS + j] ? "#" : " ");
        }
        ss << endl;
    }

    _out << ss.str() << endl;
}

vector<byte> TextIOHandler::load() { return load(_in); }

vector<byte> TextIOHandler::load(istream &provider) {
    vector<byte> program;
    while (provider) {
        char b;
        provider.get(b);
        program.push_back(b);
    }

    return program;
}

}  // namespace chip8