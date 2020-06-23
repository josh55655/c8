#include <gtest/gtest.h>

#include <core.hpp>
#include <opcode.hpp>

#include "test_state.hpp"

using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;

namespace chip8 {

TEST(OpCodesTest, MVI_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xA123));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0123, data);
    ASSERT_EQ("mvi", op.nmemonic);
    ASSERT_EQ(0xA000, op.code);
}

TEST(OpCodesTest, MVI_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xA123));
    EXPECT_CALL(state, indexRegister(0x0123)).Times(1);
    core.fetch();
    core.execute(core.decode());
}

TEST(OpCodesTest, JMP_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x1123));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0123, data);
    ASSERT_EQ("jmp", op.nmemonic);
    ASSERT_EQ(0x1000, op.code);
}

TEST(OpCodesTest, JMP_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x1123));
    EXPECT_CALL(state, pc(0x0123)).Times(1);
    core.fetch();
    core.execute(core.decode());
}

TEST(OpCodesTest, CALL_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x2123));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0123, data);
    ASSERT_EQ("call", op.nmemonic);
    ASSERT_EQ(0x2000, op.code);
}

TEST(OpCodesTest, CALL_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x2123));
    EXPECT_CALL(state, pc()).WillOnce(Return(0x202));
    EXPECT_CALL(state, push(0x202)).Times(1);
    EXPECT_CALL(state, pc(0x0123)).Times(1);

    core.fetch();
    core.execute(core.decode());
}

}  // namespace chip8
