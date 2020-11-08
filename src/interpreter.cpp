#include "interpreter.hpp"

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <sstream>
#include <string>
#include <iomanip>

#include "opcode.hpp"

using std::dec;
using std::endl;
using std::hex;
using std::setfill;
using std::setw;
using std::stringstream;
using std::to_string;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

using namespace std::chrono_literals;

namespace chip8 {

Interpreter::Interpreter(std::ostream &_out, std::istream &_in) : _out(_out), _in(_in), _core(_state) {}

void Interpreter::init() {
    word nextAddress{0};
    _out << "CHIP8 Interpreter starting..." << endl;
    _state.pc(State::CODE_ADDRESS);
    _state.clrscr();

    for (auto &digit : Core::FONT_SET) {
        _state.load(digit, nextAddress);
        nextAddress += digit.size();
    }

    _lastTick = TimePoint::min();
}

void Interpreter::load() {
    vector<byte> program;
    while (_in) {
        char b;
        _in.get(b);
        program.push_back(b);
    }
    _out << "CHIP8 Program read." << endl;
    _state.load(program);
    _out << "CHIP8 Program loaded." << endl;
    _out << "\x1B[2J"
         << "\x1B[1;1H";
}

void Interpreter::checkTime() {
    if ((Clock::now() - _lastTick) >= CLOCK_RATE()) {
        _state.tick();
        _lastTick = Clock::now();
    }
}

void Interpreter::runOne() {
    auto pc = _state.pc();
    _core.fetch();
    auto op = _core.decode();
    _out << "\x1B[1;1H"
         << "\x1B[2K";
    _out << "Read " << pc << " opcode: " << op.first.nmemonic << " 0x" << setw(4) << setfill('0') << hex << op.second
         << dec << setfill(' ') << endl;
    _core.execute(std::move(op));
}

void Interpreter::updateVideo() {
    if (!_state.videoChanged()) return;

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

void Interpreter::updateKeyboard() {}

}  // namespace chip8
