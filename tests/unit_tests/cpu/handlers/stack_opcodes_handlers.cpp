#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "gtest/gtest.h"

#include "cpu/machine.h"

namespace nespp::tests {
    constexpr uint8_t PHA = 0x48;
    constexpr uint8_t PHP = 0x08;
    constexpr uint8_t PLA = 0x68;
    constexpr uint8_t PLP = 0x28;

    constexpr uint16_t LOAD_ADDR = 0x200;

    TEST(StackOpcodeHandlers, PHA) {
        uint8_t a_value = 0x14;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {PHA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_stack().pop(), a_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StackOpcodeHandlers, PHP) {
        auto flags = std::bitset<8>(0b10101010);

        std::vector<uint8_t> rom = {PHP};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_program_status().set_value(flags);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_stack().pop(), flags);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StackOpcodeHandlers, PLA) {
        uint8_t a_value = 0x14;
        uint8_t a_temp_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {PLA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_temp_value);
        machine.get_cpu().get_stack().push(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StackOpcodeHandlers, PLA_ZERO) {
        uint8_t a_value = 0x0;
        uint8_t a_temp_value = 0x10;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {PLA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_temp_value);
        machine.get_cpu().get_stack().push(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StackOpcodeHandlers, PLA_NEGATIVE) {
        uint8_t a_value = 0xff;
        uint8_t a_temp_value = 0x10;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {PLA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_temp_value);
        machine.get_cpu().get_stack().push(a_value);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), a_value);
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StackOpcodeHandlers, PLP) {
        auto flags = std::bitset<8>(0b10101010);

        std::vector<uint8_t> rom = {PLP};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_stack().push((uint8_t)flags.to_ulong());

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

}
#pragma clang diagnostic pop