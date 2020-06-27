#ifndef CHIP8_TEST_STATE_HPP
#define CHIP8_TEST_STATE_HPP

#include <gmock/gmock.h>

#include "state.hpp"

namespace chip8 {

class StateMock : public State {
public:
    MOCK_METHOD(word, fetch, (), (override));
    MOCK_METHOD(word, indexRegister, (), (const override));
    MOCK_METHOD(void, indexRegister, (word), (override));
    MOCK_METHOD(word, pc, (), (const override));
    MOCK_METHOD(void, pc, (word), (override));
    MOCK_METHOD(void, push, (word), (override));
    MOCK_METHOD(word, pop, (), (override));
    MOCK_METHOD(byte &, v, (byte), (override));
    MOCK_METHOD(byte &, v, (byte), (const override));
    MOCK_METHOD(byte, rand, (), (const override));
    MOCK_METHOD(void, clrscr, (), (override));
};

}  // namespace chip8

#endif  // CHIP8_TEST_STATE_HPP
