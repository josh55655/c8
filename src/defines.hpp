#ifndef CHIP8_DEFINES_HPP
#define CHIP8_DEFINES_HPP

#include <cstdint>

namespace chip8 {

using byte = uint8_t;
using word = uint16_t;
using dword = uint32_t;
using qword = uint64_t;

constexpr std::size_t MEMORY_SIZE{4096};
constexpr std::size_t V_REG_NUM{16};
constexpr std::size_t CHIP8_LAST_RESERVED_MEMORY_ADDR{0x1ff};
constexpr std::size_t CHIP8_LAST_MEMORY_ADDR{0xfff};
constexpr std::size_t CHIP8_COLS{64};
constexpr std::size_t CHIP8_ROWS{32};
constexpr std::size_t STACK_SIZE{16};
constexpr std::size_t KEYPAD_SIZE{16};

}  // namespace chip8

#endif  // CHIP8_DEFINES_HPP
