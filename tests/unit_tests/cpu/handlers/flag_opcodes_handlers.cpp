#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "gtest/gtest.h"

#include "cpu/machine.h"

namespace nespp::tests {
    constexpr uint8_t SEC = 0x38;
    constexpr uint8_t SED = 0xf8;
    constexpr uint8_t SEI = 0x78;
    constexpr uint8_t CLC = 0x18;
    constexpr uint8_t CLD = 0xd8;
    constexpr uint8_t CLI = 0x58;
    constexpr uint8_t CLV = 0xb8;

    constexpr uint16_t LOAD_ADDR = 0x200;

    TEST(FlagOpcodeHandlers, SEC) {
        std::vector<uint8_t> rom = {SEC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto flags = std::bitset<8>(0);
        flags[Flags::Carry] = true;

        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(FlagOpcodeHandlers, SED) {
        std::vector<uint8_t> rom = {SED};
        auto machine = Machine(rom, LOAD_ADDR);
        auto flags = std::bitset<8>(0);
        flags[Flags::DecimalMode] = true;

        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(FlagOpcodeHandlers, SEI) {
        std::vector<uint8_t> rom = {SEI};
        auto machine = Machine(rom, LOAD_ADDR);
        auto flags = std::bitset<8>(0);
        flags[Flags::Interrupt] = true;

        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(FlagOpcodeHandlers, CLC) {
        std::vector<uint8_t> rom = {CLC};
        auto machine = Machine(rom, LOAD_ADDR);
        auto flags = std::bitset<8>(0);

        machine.get_cpu().get_program_status().set_carry(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(FlagOpcodeHandlers, CLD) {
        std::vector<uint8_t> rom = {CLD};
        auto machine = Machine(rom, LOAD_ADDR);
        auto flags = std::bitset<8>(0);

        machine.get_cpu().get_program_status().set_decimal_mode(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(FlagOpcodeHandlers, CLI) {
        std::vector<uint8_t> rom = {CLI};
        auto machine = Machine(rom, LOAD_ADDR);
        auto flags = std::bitset<8>(0);

        machine.get_cpu().get_program_status().set_interrupt(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(FlagOpcodeHandlers, CLV) {
        std::vector<uint8_t> rom = {CLV};
        auto machine = Machine(rom, LOAD_ADDR);
        auto flags = std::bitset<8>(0);

        machine.get_cpu().get_program_status().set_overflow(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }
}

#pragma clang diagnostic pop