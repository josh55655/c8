#include <gtest/gtest.h>

#include <array>
#include <vector>

#include <core.hpp>
#include <opcode.hpp>

#include "test_state.hpp"

using std::array;
using std::vector;

using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;

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

TEST(OpCodesTest, EQ_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x3123));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0123, data);
    ASSERT_EQ("eq", op.nmemonic);
    ASSERT_EQ(0x3000, op.code);
}

TEST(OpCodesTest, EQ_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte v1 = 0x23;
    byte v2 = 0x24;

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x3123));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(v1));
    EXPECT_CALL(state, pc()).WillOnce(Return(0x202));
    EXPECT_CALL(state, pc(0x204)).Times(1);
    EXPECT_CALL(state, fetch()).WillOnce(Return(0x3223));
    EXPECT_CALL(state, v(2)).WillOnce(ReturnRef(v2));
    EXPECT_CALL(state, pc(_)).Times(0);

    core.fetch();
    core.execute(core.decode());
    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(0x23, v1);
    ASSERT_EQ(0x24, v2);
}

TEST(OpCodesTest, NEQ_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x4123));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0123, data);
    ASSERT_EQ("neq", op.nmemonic);
    ASSERT_EQ(0x4000, op.code);
}

TEST(OpCodesTest, NEQ_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte v1 = 0x23;
    byte v2 = 0x24;

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x4123));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(v1));
    EXPECT_CALL(state, pc(_)).Times(0);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x4223));
    EXPECT_CALL(state, v(2)).WillOnce(ReturnRef(v2));
    EXPECT_CALL(state, pc()).WillOnce(Return(0x202));
    EXPECT_CALL(state, pc(0x204)).Times(1);

    core.fetch();
    core.execute(core.decode());
    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(0x23, v1);
    ASSERT_EQ(0x24, v2);
}

TEST(OpCodesTest, CMP_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x5120));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0120, data);
    ASSERT_EQ("cmp", op.nmemonic);
    ASSERT_EQ(0x5000, op.code);
}

TEST(OpCodesTest, CMP_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte v1 = 0x23;
    byte v2 = 0x24;
    byte v3 = 0x23;

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x5120));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(v1));
    EXPECT_CALL(state, v(2)).WillOnce(ReturnRef(v2));
    EXPECT_CALL(state, pc(_)).Times(0);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x5130));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(v1));
    EXPECT_CALL(state, v(3)).WillOnce(ReturnRef(v3));
    EXPECT_CALL(state, pc()).WillOnce(Return(0x202));
    EXPECT_CALL(state, pc(0x204)).Times(1);

    core.fetch();
    core.execute(core.decode());
    core.fetch();
    core.execute(core.decode());

    ASSERT_EQ(0x23, v1);
    ASSERT_EQ(0x24, v2);
    ASSERT_EQ(0x23, v3);
}

TEST(OpCodesTest, SET_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x6120));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0120, data);
    ASSERT_EQ("set", op.nmemonic);
    ASSERT_EQ(0x6000, op.code);
}

TEST(OpCodesTest, SET_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte datum{0};

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x6123));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(datum));
    EXPECT_CALL(state, fetch()).WillOnce(Return(0x6712));
    EXPECT_CALL(state, v(7)).WillOnce(ReturnRef(datum));

    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(0x23u, datum);
    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(0x12u, datum);
}

TEST(OpCodesTest, ADD_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x7120));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0120, data);
    ASSERT_EQ("add", op.nmemonic);
    ASSERT_EQ(0x7000, op.code);
}

TEST(OpCodesTest, ADD_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte datum{0}, other{0};

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x7123));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(datum));
    EXPECT_CALL(state, fetch()).WillOnce(Return(0x7712));
    EXPECT_CALL(state, v(7)).WillOnce(ReturnRef(other));
    EXPECT_CALL(state, fetch()).WillOnce(Return(0x7112));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(datum));

    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(0x23u, datum);
    ASSERT_EQ(0u, other);
    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(0x23u, datum);
    ASSERT_EQ(0x12u, other);
    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(0x35u, datum);
    ASSERT_EQ(0x12u, other);
}

TEST(OpCodesTest, NREQ_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x9120));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0120, data);
    ASSERT_EQ("nreq", op.nmemonic);
    ASSERT_EQ(0x9000, op.code);
}

TEST(OpCodesTest, NREQ_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte v1 = 0x23;
    byte v2 = 0x24;
    byte v3 = 0x23;

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x9120));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(v1));
    EXPECT_CALL(state, v(2)).WillOnce(ReturnRef(v2));
    EXPECT_CALL(state, pc()).WillOnce(Return(0x202));
    EXPECT_CALL(state, pc(0x204)).Times(1);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x9130));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(v1));
    EXPECT_CALL(state, v(3)).WillOnce(ReturnRef(v3));
    EXPECT_CALL(state, pc(_)).Times(0);

    core.fetch();
    core.execute(core.decode());
    core.fetch();
    core.execute(core.decode());

    ASSERT_EQ(0x23, v1);
    ASSERT_EQ(0x24, v2);
    ASSERT_EQ(0x23, v3);
}

TEST(OpCodesTest, JMPO_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xB120));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0120, data);
    ASSERT_EQ("jmpo", op.nmemonic);
    ASSERT_EQ(0xb000, op.code);
}

TEST(OpCodesTest, JMPO_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte datum{0x30};

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xB123));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(datum));
    EXPECT_CALL(state, pc()).Times(0);
    EXPECT_CALL(state, pc(0x0053)).Times(1);
    EXPECT_CALL(state, fetch()).WillOnce(Return(0xB512));
    EXPECT_CALL(state, v(5)).WillOnce(ReturnRef(datum));
    EXPECT_CALL(state, pc()).Times(0);
    EXPECT_CALL(state, pc(0x0042)).Times(1);

    core.fetch();
    core.execute(core.decode());
    core.fetch();
    core.execute(core.decode());
}

TEST(OpCodesTest, DRAW_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xD120));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0120, data);
    ASSERT_EQ("draw", op.nmemonic);
    ASSERT_EQ(0xd000, op.code);
}

TEST(OpCodesTest, DRAW_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte xCord{0};
    byte yCord{0};
    byte vf{0};
    array<byte, CHIP8_COLS * CHIP8_ROWS> display{0};

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xD123));
    EXPECT_CALL(state, video()).WillOnce(ReturnRef(display));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(xCord));
    EXPECT_CALL(state, v(2)).WillOnce(ReturnRef(yCord));
    EXPECT_CALL(state, indexRegister()).WillOnce(Return(0x30));
    EXPECT_CALL(state, read(0x30, 3)).WillOnce(Return(vector<byte>({1, 2, 3})));

    EXPECT_CALL(state, v(0xf)).WillRepeatedly(ReturnRef(vf));
    EXPECT_CALL(state, video(vector<byte>({0, 0, 0, 0, 0, 0, 0, 1}), 0x0));

    EXPECT_CALL(state, v(0xf)).WillRepeatedly(ReturnRef(vf));
    EXPECT_CALL(state, video(vector<byte>({0, 0, 0, 0, 0, 0, 1, 0}), 0x40)).Times(1);

    EXPECT_CALL(state, v(0xf)).WillRepeatedly(ReturnRef(vf));
    EXPECT_CALL(state, video(vector<byte>({0, 0, 0, 0, 0, 0, 1, 1}), 0x80)).Times(1);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xD123));
    EXPECT_CALL(state, video()).WillOnce(ReturnRef(display));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(xCord));
    EXPECT_CALL(state, v(2)).WillOnce(ReturnRef(yCord));
    EXPECT_CALL(state, indexRegister()).WillOnce(Return(0x30));
    EXPECT_CALL(state, read(0x30, 3)).WillOnce(Return(vector<byte>({1, 2, 3})));

    EXPECT_CALL(state, v(0xf)).WillRepeatedly(ReturnRef(vf));
    EXPECT_CALL(state, video(vector<byte>({0, 0, 0, 0, 0, 0, 0, 1}), 0x4A));

    EXPECT_CALL(state, v(0xf)).WillRepeatedly(ReturnRef(vf));
    EXPECT_CALL(state, video(vector<byte>({0, 0, 0, 0, 0, 0, 1, 0}), 0x8A)).Times(1);

    EXPECT_CALL(state, v(0xf)).WillRepeatedly(ReturnRef(vf));
    EXPECT_CALL(state, video(vector<byte>({0, 0, 0, 0, 0, 0, 1, 1}), 0xCA)).Times(1);

    core.fetch();
    core.execute(core.decode());
    xCord = 10;
    yCord = 1;
    ASSERT_EQ(1, vf);
    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(1, vf);
}

TEST(OpCodesTest, RAND_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xC120));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0120, data);
    ASSERT_EQ("rand", op.nmemonic);
    ASSERT_EQ(0xc000, op.code);
}

TEST(OpCodesTest, RAND_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte datum{0xff};

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xC123));
    EXPECT_CALL(state, rand()).WillOnce(Return(0x30));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(datum));
    EXPECT_CALL(state, fetch()).WillOnce(Return(0xC512));
    EXPECT_CALL(state, rand()).WillOnce(Return(0x12));
    EXPECT_CALL(state, v(5)).WillOnce(ReturnRef(datum));

    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(0x20, datum);
    core.fetch();
    core.execute(core.decode());
    ASSERT_EQ(0x12, datum);
}

TEST(OpCodesTest, JKEY_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xE120));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0120, data);
    ASSERT_EQ("jkey", op.nmemonic);
    ASSERT_EQ(0xe000, op.code);
}

TEST(OpCodesTest, JKEY_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);
    byte datum{0x12};

    EXPECT_CALL(state, fetch()).WillOnce(Return(0xE19E));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(datum));
    EXPECT_CALL(state, keyPressed(0x12)).WillOnce(Return(false));
    EXPECT_CALL(state, pc(_)).Times(0);
    EXPECT_CALL(state, fetch()).WillOnce(Return(0xE5A1));
    EXPECT_CALL(state, v(5)).WillOnce(ReturnRef(datum));
    EXPECT_CALL(state, keyPressed(0x13)).WillOnce(Return(true));
    EXPECT_CALL(state, pc(_)).Times(0);
    EXPECT_CALL(state, fetch()).WillOnce(Return(0xE19E));
    EXPECT_CALL(state, v(1)).WillOnce(ReturnRef(datum));
    EXPECT_CALL(state, keyPressed(0x14)).WillOnce(Return(true));
    EXPECT_CALL(state, pc()).WillOnce(Return(0x200));
    EXPECT_CALL(state, pc(0x202)).Times(1);
    EXPECT_CALL(state, fetch()).WillOnce(Return(0xE5A1));
    EXPECT_CALL(state, v(5)).WillOnce(ReturnRef(datum));
    EXPECT_CALL(state, keyPressed(0x15)).WillOnce(Return(false));
    EXPECT_CALL(state, pc()).WillOnce(Return(0x200));
    EXPECT_CALL(state, pc(0x202)).Times(1);

    core.fetch();
    core.execute(core.decode());
    datum = 0x13;
    core.fetch();
    core.execute(core.decode());
    datum = 0x14;
    core.fetch();
    core.execute(core.decode());
    datum = 0x15;
    core.fetch();
    core.execute(core.decode());
}

TEST(OpCodesTest, ROUTINES_decode) {
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x0120));
    core.fetch();
    auto [op, data] = core.decode();
    ASSERT_EQ(0x0120, data);
    ASSERT_EQ(".routine", op.nmemonic);
    ASSERT_EQ(0x0000, op.code);
}

TEST(OpCodesTest, ROUTINES_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x0120));
    EXPECT_CALL(state, pc()).WillOnce(Return(0x202));
    EXPECT_CALL(state, push(0x202)).Times(1);
    EXPECT_CALL(state, pc(0x0120)).Times(1);

    core.fetch();
    core.execute(core.decode());
}

TEST(OpCodesTest, ROUTINES_CLRSCR_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x00E0));
    EXPECT_CALL(state, clrscr()).Times(1);

    core.fetch();
    core.execute(core.decode());
}

TEST(OpCodesTest, ROUTINES_RETURN_execute) {
    InSequence seq;
    NiceMock<StateMock> state;
    Core core(state);

    EXPECT_CALL(state, fetch()).WillOnce(Return(0x00EE));
    EXPECT_CALL(state, pop()).WillOnce(Return(0x0202));
    EXPECT_CALL(state, pc(0x0202)).Times(1);

    core.fetch();
    core.execute(core.decode());
}

}  // namespace chip8
