#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "gtest/gtest.h"

#include "cpu/handlers/math_opcodes_handlers.h"
#include "cpu/machine.h"

namespace nespp::tests {

    constexpr uint8_t DEC_ZERO   = 0xc6;
    constexpr uint8_t DEC_ZERO_X = 0xd6;
    constexpr uint8_t DEC_ABS    = 0xce;
    constexpr uint8_t DEC_ABS_X  = 0xde;
    constexpr uint8_t DEX        = 0xca;
    constexpr uint8_t DEY        = 0x88;

    constexpr uint16_t LOAD_ADDR      = 0x200;
    constexpr uint16_t ZERO_PAGE_ADDR = 0x10;
    constexpr uint16_t ABS_ADDR_LOW   = 0x20;
    constexpr uint16_t ABS_ADDR_HIGH  = 0x10;
    constexpr uint16_t ABS_ADDR       = 0x1020;

    TEST(StoreOpcodeHandlers, DEC_ZERO) {
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEC_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ZERO_PAGE_ADDR), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, DEC_ZERO_ZERO) {
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

    TEST(StoreOpcodeHandlers, DEC_ZERO_NEGATIVE) {
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

    TEST(StoreOpcodeHandlers, DEC_ZERO_X) {
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

    TEST(StoreOpcodeHandlers, DEC_ZERO_X_ZERO) {
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

    TEST(StoreOpcodeHandlers, DEC_ZERO_X_NEGATIVE) {
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

    TEST(StoreOpcodeHandlers, DEC_ABS) {
        uint8_t memory_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEC_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ABS_ADDR), memory_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, DEC_ABS_ZERO) {
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

    TEST(StoreOpcodeHandlers, DEC_ABS_NEGATIVE) {
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

    TEST(StoreOpcodeHandlers, DEC_ABS_X) {
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

    TEST(StoreOpcodeHandlers, DEC_ABS_X_ZERO) {
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

    TEST(StoreOpcodeHandlers, DEC_ABS_X_NEGATIVE) {
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

    TEST(StoreOpcodeHandlers, DEX) {
        uint8_t x_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_x().get_value(), x_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, DEX_ZERO) {
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

    TEST(StoreOpcodeHandlers, DEX_NEGATIVE) {
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

    TEST(StoreOpcodeHandlers, DEY) {
        uint8_t y_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {DEY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_y().set_value(y_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_y().get_value(), y_value - 1);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, DEY_ZERO) {
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

    TEST(StoreOpcodeHandlers, DEY_NEGATIVE) {
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

}

#pragma clang diagnostic pop