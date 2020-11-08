#ifndef CHIP8_INTERPRETER_HPP
#define CHIP8_INTERPRETER_HPP

#include <iostream>
#include <chrono>

#include "core.hpp"
#include "state.hpp"

namespace chip8 {

class Interpreter {
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    static constexpr std::size_t CLOCK_HZ{60};

    State _state;
    Core _core;
    std::ostream &_out;
    std::istream &_in;
    TimePoint _lastTick;

public:
    Interpreter(std::ostream &_out, std::istream &_in);

    void init();
    void load();
    void runOne();
    void updateVideo();
    void updateKeyboard();

private:
    void checkTime();

    static constexpr std::chrono::milliseconds CLOCK_RATE() {
        return std::chrono::milliseconds(std::size_t((1.0 / CLOCK_HZ) * 1000 + 0.5));
    };
};

}  // namespace chip8

#endif  // CHIP8_INTERPRETER_HPP
