#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "gtest/gtest.h"

#include "cpu/machine.h"

namespace nespp::tests {

    constexpr uint8_t DEC_ZERO   = 0xc6;
    constexpr uint8_t DEC_ZERO_X = 0xd6;
    constexpr uint8_t DEC_ABS    = 0xce;
    constexpr uint8_t DEC_ABS_X  = 0xde;
    constexpr uint8_t DEX        = 0xca;
    constexpr uint8_t DEY        = 0x88;
    constexpr uint8_t INC_ZERO   = 0xe6;
    constexpr uint8_t INC_ZERO_X = 0xf6;
    constexpr uint8_t INC_ABS    = 0xee;
    constexpr uint8_t INC_ABS_X  = 0xfe;
    constexpr uint8_t INX        = 0xe8;
    constexpr uint8_t INY        = 0xc8;
    constexpr uint8_t ADC_IMM    = 0x69;
    constexpr uint8_t ADC_ZERO   = 0x65;
    constexpr uint8_t ADC_ZERO_X = 0x75;
    constexpr uint8_t ADC_ABS    = 0x6d;
    constexpr uint8_t ADC_ABS_X  = 0x7d;
    constexpr uint8_t ADC_ABS_Y  = 0x79;
    constexpr uint8_t ADC_IND_X  = 0x61;
    constexpr uint8_t ADC_IND_Y  = 0x71;
    constexpr uint8_t SBC_IMM    = 0xe9;
    constexpr uint8_t SBC_ZERO   = 0xe5;
    constexpr uint8_t SBC_ZERO_X = 0xf5;
    constexpr uint8_t SBC_ABS    = 0xed;
    constexpr uint8_t SBC_ABS_X  = 0xfd;
    constexpr uint8_t SBC_ABS_Y  = 0xf9;
    constexpr uint8_t SBC_IND_X  = 0xe1;
    constexpr uint8_t SBC_IND_Y  = 0xf1;

    constexpr uint16_t LOAD_ADDR      = 0x200;
    constexpr uint16_t ZERO_PAGE_ADDR = 0x10;
    constexpr uint16_t ABS_ADDR_LOW   = 0x20;
    constexpr uint16_t ABS_ADDR_HIGH  = 0x10;
    constexpr uint16_t ABS_ADDR       = 0x1020;

    TEST(MathOpcodeHandlers, DEC_ZERO) {
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEC_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ZERO_PAGE_ADDR), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ZERO_ZERO) {
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {DEC_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ZERO_PAGE_ADDR), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ZERO_NEGATIVE) {
        uint8_t memory_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {DEC_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        --memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ZERO_X) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEC_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ZERO_X_ZERO) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {DEC_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ZERO_X_NEGATIVE) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {DEC_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        --memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ABS) {
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEC_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ABS_ADDR), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ABS_ZERO) {
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {DEC_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ABS_ADDR), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ABS_NEGATIVE) {
        uint8_t memory_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {DEC_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        --memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ABS_X) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEC_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = ABS_ADDR + x_value;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ABS_X_ZERO) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {DEC_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = ABS_ADDR + x_value;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEC_ABS_X_NEGATIVE) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {DEC_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = ABS_ADDR + x_value;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        --memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEX) {
        uint8_t x_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_x().get_value(), x_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEX_ZERO) {
        uint8_t x_value = 0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {DEX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_x().get_value(), x_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEX_NEGATIVE) {
        uint8_t x_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {DEX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);

        machine.execute();

        --x_value;
        EXPECT_EQ(machine.get_cpu().get_x().get_value(), x_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEY) {
        uint8_t y_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_y().set_value(y_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_y().get_value(), y_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEY_ZERO) {
        uint8_t y_value = 0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {DEY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_y().set_value(y_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_y().get_value(), y_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, DEY_NEGATIVE) {
        uint8_t y_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {DEY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_y().set_value(y_value);

        machine.execute();

        --y_value;
        EXPECT_EQ(machine.get_cpu().get_y().get_value(), y_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ZERO) {
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {INC_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ZERO_PAGE_ADDR), memory_value + 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ZERO_ZERO) {
        uint8_t memory_value = -0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {INC_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        ++memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ZERO_NEGATIVE) {
        uint8_t memory_value = -0x02;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {INC_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        ++memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ZERO_PAGE_ADDR), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ZERO_X) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {INC_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value + 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ZERO_X_ZERO) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = -0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {INC_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        ++memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ZERO_X_NEGATIVE) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = -0x02;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {INC_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        ++memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ABS) {
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {INC_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ABS_ADDR), memory_value + 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ABS_ZERO) {
        uint8_t memory_value = -0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {INC_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        ++memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ABS_NEGATIVE) {
        uint8_t memory_value = -0x02;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {INC_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        ++memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ABS_ADDR), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ABS_X) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {INC_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = ABS_ADDR + x_value;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value + 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ABS_X_ZERO) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = -0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {INC_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = ABS_ADDR + x_value;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        ++memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INC_ABS_X_NEGATIVE) {
        uint8_t x_value = 0x04;
        uint8_t memory_value = -0x02;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {INC_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = ABS_ADDR + x_value;
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        ++memory_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), memory_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INX) {
        uint8_t x_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {INX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_x().get_value(), x_value + 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INX_ZERO) {
        uint8_t x_value = -0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {INX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);

        machine.execute();

        ++x_value;
        EXPECT_EQ(machine.get_cpu().get_x().get_value(), x_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INX_NEGATIVE) {
        uint8_t x_value = -0x02;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {INX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);

        machine.execute();

        ++x_value;
        EXPECT_EQ(machine.get_cpu().get_x().get_value(), x_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INY) {
        uint8_t y_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {INY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_y().set_value(y_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_y().get_value(), y_value + 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INY_ZERO) {
        uint8_t y_value = -0x01;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {INY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_y().set_value(y_value);

        machine.execute();

        ++y_value;
        EXPECT_EQ(machine.get_cpu().get_y().get_value(), y_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, INY_NEGATIVE) {
        uint8_t y_value = -0x02;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {INY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_y().set_value(y_value);

        machine.execute();

        ++y_value;
        EXPECT_EQ(machine.get_cpu().get_y().get_value(), y_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_IMM) {
        uint8_t a_value = 20;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ADC_IMM, 20};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 40);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_IMM_ZERO) {
        uint8_t a_value = 0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ADC_IMM, 0};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_IMM_ZERO_CARRY) {
        uint8_t a_value = 1;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {ADC_IMM, 0xff};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_IMM_NEGATIVE) {
        uint8_t a_value = 20;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ADC_IMM, 200};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 220);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_IMM_OVERFLOW_NEGATIVE) {
        uint8_t a_value = 20;
        auto flags = std::bitset<8>(0);
        flags[Flags::Overflow] = true;
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {ADC_IMM, 120};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 140);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_IMM_OVERFLOW_POSITIVE) {
        uint8_t a_value = 170;
        auto flags = std::bitset<8>(0);
        flags[Flags::Overflow] = true;
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {ADC_IMM, 170};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 84);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_ZERO) {
        uint8_t a_value = 20;
        uint8_t zero_value = 20;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ADC_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, zero_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 40);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_ZERO_X) {
        uint8_t a_value = 20;
        uint8_t x_value = 0x10;
        uint8_t zero_value = 20;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ADC_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, zero_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 40);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_ABS) {
        uint8_t a_value = 20;
        uint8_t memory_value = 20;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ADC_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 40);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_ABS_X) {
        uint8_t a_value = 20;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 20;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ADC_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = x_value + ABS_ADDR;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 40);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_ABS_Y) {
        uint8_t a_value = 20;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 20;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ADC_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = y_value + ABS_ADDR;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 40);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_IND_X) {
        uint8_t a_value = 20;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 20;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ADC_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 40);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, ADC_IND_Y) {
        uint8_t a_value = 20;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 20;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {ADC_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = y_value + indirect_addr;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 40);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_IMM) {
        uint8_t a_value = 0x50;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {SBC_IMM, 0x20};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0x30);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_IMM_ZERO) {
        uint8_t a_value = 10;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {SBC_IMM, 10};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_IMM_BORROW) {
        uint8_t a_value = 0xd0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = false;
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {SBC_IMM, 0xf0};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0xe0);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_IMM_OVERFLOW) {
        uint8_t a_value = 0x50;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = false;
        flags[Flags::Overflow] = true;
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {SBC_IMM, 0xb0};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0xa0);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_ZERO) {
        uint8_t a_value = 0x30;
        uint8_t zero_value = 0x20;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {SBC_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, zero_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0x10);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_ZERO_X) {
        uint8_t a_value = 0x30;
        uint8_t x_value = 0x10;
        uint8_t zero_value = 0x20;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {SBC_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = (x_value + ZERO_PAGE_ADDR) & 0xffu;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, zero_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0x10);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_ABS) {
        uint8_t a_value = 0x30;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {SBC_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0x10);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_ABS_X) {
        uint8_t a_value = 0x30;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {SBC_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = x_value + ABS_ADDR;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0x10);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_ABS_Y) {
        uint8_t a_value = 0x30;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {SBC_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        uint16_t address = y_value + ABS_ADDR;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0x10);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_IND_X) {
        uint8_t a_value = 0x30;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x20;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {SBC_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);
        machine.get_cpu().get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0x10);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(MathOpcodeHandlers, SBC_IND_Y) {
        uint8_t a_value = 0x30;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x20;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {SBC_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = y_value + indirect_addr;
        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        machine.get_cpu().get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), 0x10);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }
}

#pragma clang diagnostic pop