#include "interpreter.hpp"

#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "opcode.hpp"

using std::dec;
using std::endl;
using std::hex;
using std::ifstream;
using std::ios;
using std::setfill;
using std::setw;
using std::stringstream;
using std::to_string;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

using namespace std::chrono_literals;

namespace chip8 {

Interpreter::Interpreter(std::unique_ptr<IOHandler> &&_io, const std::string &_programFile, std::size_t clockHZ)
    : _core(_state), _io(std::move(_io)), _programFile(_programFile), _clockHZ(clockHZ) {}

void Interpreter::init() {
    word nextAddress{0};
    _io->log("CHIP8 Interpreter starting...");

    _state.pc(State::CODE_ADDRESS);
    _state.clrscr();

    for (auto &digit : Core::FONT_SET) {
        _state.load(digit, nextAddress);
        nextAddress += word(digit.size());
    }

    _lastTick = TimePoint::min();
}

void Interpreter::load() {
    vector<byte> program;

    if (!_programFile.empty()) {
        auto _programStream{ifstream(_programFile, ios::binary)};
        _io->log("Loading " + _programFile + "...");
        program = _io->load(_programStream);
    } else {
        _io->log("Loading...");
        program = _io->load();
    }

    _state.load(program);
    _io->log("CHIP8 Program loaded.");
}

void Interpreter::run( string logFileName ) {
    __started = true;
    _io->init(_state);
    _lastTick = Clock::now();

    while (true) {
        if (checkTime()) {
            runOne( logFileName );
            updateVideo();
            updateKeyboard();
        }
    }
}

bool Interpreter::checkTime() {
    if ((Clock::now() - _lastTick) >= clockRate()) {
        _state.tick();
        _lastTick = Clock::now();
        return true;
    }

    return false;
}

milliseconds Interpreter::clockRate() const { return RATE(_clockHZ); };

void Interpreter::runOne( string logFileName ) {
    if (!__started) throw std::logic_error("Interpreter not STARTED!");

    auto pc = _state.pc();
    _core.fetch();
    auto op = _core.decode();
    _io->log(pc, op);

    ofstream logfile;
    logfile.open ( logFileName );
    logfile << Clock::now(); //* the point in time when the instruction is executed
    logfile << "\n";
    logfile << op;   //* the instruction itself
    logfile << "\n";
    logfile << _state.indexRegister(); //* the resulting state of the registry -> i
    logfile << "\n";
	logfile << _state.pc(); //* the resulting state of the registry  ->pc
	logfile << "\n";
    logfile.close();

    _core.execute(std::move(op));


    //* the resulting state of the registry (including `i` and `pc`) i = ; pc  =
}

void Interpreter::updateVideo() {
    if (!_state.videoChanged()) return;
    _io->draw(_state);
}

void Interpreter::updateKeyboard() {}

}  // namespace chip8
