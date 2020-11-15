#include "interpreter.hpp"

#include <chrono>
#include <iostream>
#include <vector>
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

Interpreter::Interpreter(std::unique_ptr<IOHandler> &&_io) : _core(_state), _io(std::move(_io)) {}

void Interpreter::init() {
    word nextAddress{0};
    _io->log("CHIP8 Interpreter starting...");

    _state.pc(State::CODE_ADDRESS);
    _state.clrscr();

    for (auto &digit : Core::FONT_SET) {
        _state.load(digit, nextAddress);
        nextAddress += digit.size();
    }

    _lastTick = TimePoint::min();
}

void Interpreter::load() {
    _io->log("Loading...");
    auto program = _io->load();
    _state.load(program);
    _io->log("CHIP8 Program loaded.");
}

void Interpreter::start() {
    __started = true;
    _io->initScreen();
}

void Interpreter::checkTime() {
    if ((Clock::now() - _lastTick) >= CLOCK_RATE()) {
        _state.tick();
        _lastTick = Clock::now();
    }
}

void Interpreter::runOne() {
    if (!__started) throw std::logic_error("Interpreter not STARTED!");

    auto pc = _state.pc();
    _core.fetch();
    auto op = _core.decode();
    _io->log(pc, op);
    _core.execute(std::move(op));
}

void Interpreter::updateVideo() {
    if (!_state.videoChanged()) return;
    _io->draw(_state);
}

void Interpreter::updateKeyboard() {}

}  // namespace chip8
