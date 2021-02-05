#include "gtest/gtest.h"

#include "cpu/handlers/transfer_opcodes_handlers.h"
#include "cpu/machine.h"
#include "cpu/register/program_status.h"

namespace nespp::tests {

    constexpr uint8_t TAX = 0xaa;
    constexpr uint8_t TAY = 0xa8;
    constexpr uint8_t TSX = 0xba;
    constexpr uint8_t TXA = 0x8a;
    constexpr uint8_t TXS = 0x9a;
    constexpr uint8_t TYA = 0x98;

    constexpr uint16_t LOAD_ADDR = 0x200;

    TEST(TransferOpcodeHandlers, TAX) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x04;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {TAX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TAX_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {TAX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TAX_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0xff;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {TAX};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

}