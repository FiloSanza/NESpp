#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "gtest/gtest.h"
#include "cpu/machine.h"

namespace nespp::tests {

    constexpr uint8_t LDA_IMM    = 0xa9;
    constexpr uint8_t LDA_ZERO   = 0xa5;
    constexpr uint8_t LDA_ZERO_X = 0xb5;
    constexpr uint8_t LDA_ABS    = 0xad;
    constexpr uint8_t LDA_ABS_X  = 0xbd;
    constexpr uint8_t LDA_ABS_Y  = 0xb9;
    constexpr uint8_t LDA_IND_X  = 0xa1;
    constexpr uint8_t LDA_IND_Y  = 0xb1;
    constexpr uint8_t LDX_IMM    = 0xa2;
    constexpr uint8_t LDX_ZERO   = 0xa6;
    constexpr uint8_t LDX_ZERO_Y = 0xb6;
    constexpr uint8_t LDX_ABS    = 0xae;
    constexpr uint8_t LDX_ABS_Y  = 0xbe;
    constexpr uint8_t LDY_IMM    = 0xa0;
    constexpr uint8_t LDY_ZERO   = 0xa4;
    constexpr uint8_t LDY_ZERO_X = 0xb4;
    constexpr uint8_t LDY_ABS    = 0xac;
    constexpr uint8_t LDY_ABS_X  = 0xbc;

    constexpr uint16_t LOAD_ADDR     = 0x200;
    constexpr uint16_t ZERO_PAGE_ADDR = 0x10;
    constexpr uint16_t ABS_ADDR      = 0x3020;
    constexpr uint16_t ABS_ADDR_LOW  = 0x20;
    constexpr uint16_t ABS_ADDR_HIGH = 0x30;

    TEST(LoadOpcodeHandlers, LDA_IMM) {
        uint8_t immediate_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDA_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), immediate_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDA_IMM_ZERO) {
        uint8_t immediate_value = 0x0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {LDA_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), immediate_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDA_IMM_NEGATIVE) {
        uint8_t immediate_value = 0x8f;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {LDA_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), immediate_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDA_ZERO) {
        uint8_t value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDA_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDA_ZERO_X) {
        uint8_t value = 0x0f;
        uint8_t x_value = 0x30;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDA_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        cpu.get_program_status().set_value(0);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDA_ABS) {
        uint8_t value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDA_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);
        cpu.get_memory().set_u8(ABS_ADDR, value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDA_ABS_X) {
        uint8_t value = 0x0f;
        uint8_t x_value = 0x30;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDA_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        auto address = x_value + ABS_ADDR;
        cpu.get_program_status().set_value(0);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDA_ABS_Y) {
        uint8_t value = 0x0f;
        uint8_t y_value = 0x30;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDA_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        auto address = y_value + ABS_ADDR;
        cpu.get_program_status().set_value(0);
        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(address, value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDA_IND_X) {
        uint8_t value = 0x0f;
        uint8_t x_value = 0x30;
        uint16_t indirect_addr = 0x320;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDA_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        cpu.get_program_status().set_value(0);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u16(address, indirect_addr);
        cpu.get_memory().set_u8(indirect_addr, value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDA_IND_Y) {
        uint8_t value = 0x0f;
        uint8_t y_value = 0x30;
        uint16_t indirect_addr = 0x320;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDA_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        auto address = y_value + indirect_addr;
        cpu.get_program_status().set_value(0);
        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        cpu.get_memory().set_u8(address, value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDX_IMM) {
        uint8_t immediate_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDX_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), immediate_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDX_ZERO) {
        uint8_t value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDX_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDX_ZERO_Y) {
        uint8_t value = 0x0f;
        uint8_t y_value = 0x30;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDX_ZERO_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        auto address = (y_value + ZERO_PAGE_ADDR) & 0xff;
        cpu.get_program_status().set_value(0);
        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(address, value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDX_ABS) {
        uint8_t value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDX_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);
        cpu.get_memory().set_u8(ABS_ADDR, value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDX_ABS_Y) {
        uint8_t value = 0x0f;
        uint8_t y_value = 0x30;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDX_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        auto address = y_value + ABS_ADDR;
        cpu.get_program_status().set_value(0);
        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(address, value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDY_IMM) {
        uint8_t immediate_value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDY_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), immediate_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDY_ZERO) {
        uint8_t value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDY_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDY_ZERO_X) {
        uint8_t value = 0x0f;
        uint8_t x_value = 0x30;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDY_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        cpu.get_program_status().set_value(0);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDY_ABS) {
        uint8_t value = 0x0f;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDY_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        cpu.get_program_status().set_value(0);
        cpu.get_memory().set_u8(ABS_ADDR, value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(LoadOpcodeHandlers, LDY_ABS_X) {
        uint8_t value = 0x0f;
        uint8_t x_value = 0x30;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {LDY_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
        auto &cpu = machine.get_cpu();

        auto address = x_value + ABS_ADDR;
        cpu.get_program_status().set_value(0);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

}

#pragma clang diagnostic pop
