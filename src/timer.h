#ifndef CHIP8_TIMER_H
#define CHIP8_TIMER_H

#include "state.hpp"

namespace chip8 {

class TimerInterface {
public:
    TimerInterface(State &state);
    virtual ~TimerInterface();

    virtual byte getDelay() const = 0;
    virtual void setDelay(byte nextD) const = 0;
};

}  // namespace chip8

#endif  // CHIP8_TIMER_H
