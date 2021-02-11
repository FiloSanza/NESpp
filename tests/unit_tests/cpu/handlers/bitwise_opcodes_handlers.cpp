#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <utils/debug.h>
#include "gtest/gtest.h"

#include "cpu/machine.h"

namespace nespp::tests {
    constexpr uint8_t AND_IMM    = 0x29;
    constexpr uint8_t AND_ZERO   = 0x25;
    constexpr uint8_t AND_ZERO_X = 0x35;
    constexpr uint8_t AND_ABS    = 0x2d;
    constexpr uint8_t AND_ABS_X  = 0x3d;
    constexpr uint8_t AND_ABS_Y  = 0x39;
    constexpr uint8_t AND_IND_X  = 0x21;
    constexpr uint8_t AND_IND_Y  = 0x31;
    constexpr uint8_t EOR_IMM    = 0x49;
    constexpr uint8_t EOR_ZERO   = 0x45;
    constexpr uint8_t EOR_ZERO_X = 0x55;
    constexpr uint8_t EOR_ABS    = 0x4d;
    constexpr uint8_t EOR_ABS_X  = 0x5d;
    constexpr uint8_t EOR_ABS_Y  = 0x59;
    constexpr uint8_t EOR_IND_X  = 0x41;
    constexpr uint8_t EOR_IND_Y  = 0x51;
    constexpr uint8_t ORA_IMM    = 0x09;
    constexpr uint8_t ORA_ZERO   = 0x05;
    constexpr uint8_t ORA_ZERO_X = 0x15;
    constexpr uint8_t ORA_ABS    = 0x0d;
    constexpr uint8_t ORA_ABS_X  = 0x1d;
    constexpr uint8_t ORA_ABS_Y  = 0x19;
    constexpr uint8_t ORA_IND_X  = 0x01;
    constexpr uint8_t ORA_IND_Y  = 0x11;
    constexpr uint8_t ROL_ACC    = 0x2a;
    constexpr uint8_t ROL_ZERO   = 0x26;
    constexpr uint8_t ROL_ZERO_X = 0x36;
    constexpr uint8_t ROL_ABS    = 0x2e;
    constexpr uint8_t ROL_ABS_X  = 0x3e;
    constexpr uint8_t ROR_ACC    = 0x6a;
    constexpr uint8_t ROR_ZERO   = 0x66;
    constexpr uint8_t ROR_ZERO_X = 0x76;
    constexpr uint8_t ROR_ABS    = 0x6e;
    constexpr uint8_t ROR_ABS_X  = 0x7e;
    constexpr uint8_t BIT_ZERO   = 0x24;
    constexpr uint8_t BIT_ABS    = 0x2c;

    constexpr uint16_t LOAD_ADDR      = 0x200;
    constexpr uint16_t ZERO_PAGE_ADDR = 0x10;
    constexpr uint16_t ABS_ADDR_LOW   = 0x20;
    constexpr uint16_t ABS_ADDR_HIGH  = 0x10;
    constexpr uint16_t ABS_ADDR       = 0x1020;

    TEST(BitwiseOpcodesHandlers, AND_IMM) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {AND_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & immediate_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_IMM_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {AND_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & immediate_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_IMM_NEGATIVE) {
        uint8_t a_value = 0xf4;
        uint8_t immediate_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {AND_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & immediate_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {AND_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ZERO_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {AND_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ZERO_NEGATIVE) {
        uint8_t a_value = 0xf4;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {AND_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ZERO_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {AND_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ZERO_X_WRAP_AROUND) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0xf5;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {AND_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ZERO_X_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {AND_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ZERO_X_NEGATIVE) {
        uint8_t a_value = 0xf4;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {AND_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ABS) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {AND_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ABS_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {AND_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ABS_NEGATIVE) {
        uint8_t a_value = 0xf4;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {AND_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ABS_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {AND_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + x_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ABS_X_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {AND_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + x_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ABS_X_NEGATIVE) {
        uint8_t a_value = 0xf4;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {AND_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + x_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ABS_Y) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {AND_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ABS_Y_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {AND_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_ABS_Y_NEGATIVE) {
        uint8_t a_value = 0xf4;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {AND_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_IND_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0f;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {AND_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_IND_X_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {AND_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_IND_X_NEGATIVE) {
        uint8_t a_value = 0xf4;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0xf0;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {AND_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_IND_Y) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x0f;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {AND_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = indirect_addr + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_IND_Y_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x0;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {AND_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = indirect_addr + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, AND_IND_Y_NEGATIVE) {
        uint8_t a_value = 0xf4;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0xf0;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {AND_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = indirect_addr + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value & memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_IMM) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {EOR_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ immediate_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_IMM_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {EOR_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ immediate_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_IMM_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {EOR_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ immediate_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {EOR_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ZERO_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {EOR_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ZERO_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {EOR_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ZERO_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {EOR_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ZERO_X_WRAP_AROUND) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0xf5;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {EOR_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ZERO_X_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {EOR_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ZERO_X_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {EOR_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ABS) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {EOR_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ABS_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {EOR_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ABS_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {EOR_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ABS_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {EOR_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + x_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ABS_X_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {EOR_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + x_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ABS_X_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {EOR_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + x_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ABS_Y) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {EOR_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ABS_Y_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {EOR_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_ABS_Y_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {EOR_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_IND_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0f;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {EOR_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_IND_X_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x14;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {EOR_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_IND_X_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0xf0;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {EOR_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_IND_Y) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x0f;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {EOR_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = indirect_addr + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_IND_Y_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x14;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {EOR_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = indirect_addr + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, EOR_IND_Y_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0xf0;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {EOR_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = indirect_addr + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value ^ memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_IMM) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ORA_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | immediate_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_IMM_ZERO) {
        uint8_t a_value = 0x00;
        uint8_t immediate_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ORA_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | immediate_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_IMM_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ORA_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | immediate_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ORA_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ZERO_ZERO) {
        uint8_t a_value = 0x00;
        uint8_t memory_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ORA_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ZERO_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ORA_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ZERO_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ORA_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ZERO_X_WRAP_AROUND) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0xf5;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ORA_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ZERO_X_ZERO) {
        uint8_t a_value = 0x00;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ORA_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ZERO_X_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ORA_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ABS) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ORA_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ABS_ZERO) {
        uint8_t a_value = 0x00;
        uint8_t memory_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ORA_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ABS_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ORA_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ABS_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ORA_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + x_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ABS_X_ZERO) {
        uint8_t a_value = 0x00;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ORA_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + x_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ABS_X_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ORA_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + x_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ABS_Y) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ORA_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ABS_Y_ZERO) {
        uint8_t a_value = 0x00;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ORA_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_ABS_Y_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ORA_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = ABS_ADDR + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_IND_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x0f;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ORA_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_IND_X_ZERO) {
        uint8_t a_value = 0x00;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x00;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ORA_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_IND_X_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0xf0;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ORA_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_IND_Y) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x0f;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ORA_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = indirect_addr + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_IND_Y_ZERO) {
        uint8_t a_value = 0x00;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x00;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ORA_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = indirect_addr + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ORA_IND_Y_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0xf0;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ORA_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = indirect_addr + y_value;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value | memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ACC) {
        uint8_t a_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROL_ACC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        a_value = (a_value << 1u) | 1;    //carry is set
        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ACC_CARRY) {
        uint8_t a_value = 0x8f;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ACC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);

        machine.execute();

        a_value <<= 1u;
        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ACC_NEGATIVE) {
        uint8_t a_value = 0b01111111;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROL_ACC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);

        machine.execute();

        a_value <<= 1u;
        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ACC_ZERO) {
        uint8_t a_value = 0b10000000;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ACC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);

        machine.execute();

        a_value <<= 1u;
        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ZERO) {
        uint8_t memory_value = 0x0f;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROL_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        memory_value = (memory_value << 1u) | 1;    //carry is set
        EXPECT_EQ(cpu.get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ZERO_CARRY) {
        uint8_t memory_value = 0x8f;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ZERO_NEGATIVE) {
        uint8_t memory_value = 0b01111111;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROL_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ZERO_ZERO) {
        uint8_t memory_value = 0b10000000;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ZERO_X) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0x0f;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROL_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        memory_value = (memory_value << 1u) | 1;    //carry is set
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ZERO_X_WRAP_AROUND) {
        uint8_t x_value = 0xf5;
        uint8_t memory_value = 0x0f;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROL_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        memory_value = (memory_value << 1u) | 1;    //carry is set
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ZERO_X_CARRY) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0x8f;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;

        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ZERO_X_NEGATIVE) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0b01111111;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROL_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ZERO_X_ZERO) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0b10000000;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ABS) {
        uint8_t memory_value = 0x0f;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROL_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ABS_ADDR, memory_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        memory_value = (memory_value << 1u) | 1;    //carry is set
        EXPECT_EQ(cpu.get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ABS_CARRY) {
        uint8_t memory_value = 0x8f;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ABS_NEGATIVE) {
        uint8_t memory_value = 0b01111111;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROL_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ABS_ZERO) {
        uint8_t memory_value = 0b10000000;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ABS_X) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0x0f;
        uint16_t address = x_value + ABS_ADDR;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROL_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        memory_value = (memory_value << 1u) | 1;    //carry is set
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ABS_X_CARRY) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0x8f;
        uint16_t address = x_value + ABS_ADDR;

        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ABS_X_NEGATIVE) {
        uint8_t memory_value = 0x7f;
        uint8_t x_value = 0x10;
        uint16_t address = x_value + ABS_ADDR;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROL_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROL_ABS_X_ZERO) {
        uint8_t memory_value = 0x80;
        uint8_t x_value = 0x10;
        uint16_t address = x_value + ABS_ADDR;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROL_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value <<= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ACC) {
        uint8_t a_value = 0xf0;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROR_ACC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);

        machine.execute();

        a_value >>= 1u;
        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ACC_CARRY) {
        uint8_t a_value = 0x0f;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ACC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);

        machine.execute();

        a_value >>= 1u;
        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ACC_NEGATIVE) {
        uint8_t a_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROR_ACC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        a_value >>= 1u;
        a_value |= 0b10000000;
        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ACC_ZERO) {
        uint8_t a_value = 0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ACC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);

        machine.execute();

        a_value >>= 1u;
        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ZERO) {
        uint8_t memory_value = 0xf0;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROR_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ZERO_CARRY) {
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ZERO_NEGATIVE) {
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROR_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        memory_value >>= 1u;
        memory_value |= 0b10000000;
        EXPECT_EQ(cpu.get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ZERO_ZERO) {
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ZERO_X) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0xf0;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROR_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ZERO_X_WRAP_AROUND) {
        uint8_t x_value = 0xff;
        uint8_t memory_value = 0xf0;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROR_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ZERO_X_CARRY) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0x0f;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;

        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ZERO_X_NEGATIVE) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0xf0;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROR_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        memory_value >>= 1u;
        memory_value |= 0b10000000;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ZERO_X_ZERO) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0x01;
        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ABS) {
        uint8_t memory_value = 0xf0;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROR_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ABS_CARRY) {
        uint8_t memory_value = 0x0f;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ABS_NEGATIVE) {
        uint8_t memory_value = 0xf0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROR_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ABS_ADDR, memory_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        memory_value >>= 1u;
        memory_value |= 0b10000000;
        EXPECT_EQ(cpu.get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ABS_ZERO) {
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ABS_X) {
        uint8_t x_value = 0x10;
        uint8_t memory_value = 0xf0;
        uint16_t address = x_value + ABS_ADDR;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ROR_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ABS_X_CARRY) {
        uint8_t memory_value = 0x0f;
        uint8_t x_value = 0x10;
        uint16_t address = x_value + ABS_ADDR;

        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ABS_X_NEGATIVE) {
        uint8_t memory_value = 0xf0;
        uint8_t x_value = 0x10;
        uint16_t address = ABS_ADDR + x_value;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ROR_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);
        cpu.get_program_status().set_carry(true);

        machine.execute();

        memory_value >>= 1u;
        memory_value |= 0b10000000;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, ROR_ABS_X_ZERO) {
        uint8_t memory_value = 0x01;
        uint8_t x_value = 0x10;
        uint16_t address = x_value + ABS_ADDR;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ROR_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        memory_value >>= 1u;
        EXPECT_EQ(cpu.get_memory().get_u8(address), memory_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, BIT_ZERO_ZERO) {
        uint8_t memory_value = 0x0f;
        uint8_t a_value = 0xf0;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {BIT_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, BIT_ZERO_NEGATIVE) {
        uint8_t memory_value = 0x8f;
        uint8_t a_value = 0x0f;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {BIT_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, BIT_ZERO_OVERFLOW) {
        uint8_t memory_value = 0x4f;
        uint8_t a_value = 0x0f;

        auto flags = std::bitset<8>(0);
        flags[Flags::Overflow] = true;

        std::vector<uint8_t> rom = {BIT_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, BIT_ABS_ZERO) {
        uint8_t memory_value = 0x0f;
        uint8_t a_value = 0xf0;

        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {BIT_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, BIT_ABS_NEGATIVE) {
        uint8_t memory_value = 0x8f;
        uint8_t a_value = 0x0f;

        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {BIT_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(BitwiseOpcodesHandlers, BIT_ABS_OVERFLOW) {
        uint8_t memory_value = 0x4f;
        uint8_t a_value = 0x0f;

        auto flags = std::bitset<8>(0);
        flags[Flags::Overflow] = true;

        std::vector<uint8_t> rom = {BIT_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

}

#pragma clang diagnostic pop