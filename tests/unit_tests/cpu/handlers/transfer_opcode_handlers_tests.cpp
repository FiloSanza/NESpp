#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "gtest/gtest.h"

#include "cpu/handlers/transfer_opcodes_handlers.h"
#include "cpu/machine.h"

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
        uint8_t x_value = 0x14;
        uint8_t a_value = 0x00;
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
        uint8_t x_value = 0x14;
        uint8_t a_value = 0xff;
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

    TEST(TransferOpcodeHandlers, TAY) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x04;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {TAY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_y().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TAY_ZERO) {
        uint8_t y_value = 0x14;
        uint8_t a_value = 0x00;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {TAY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_y().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TAY_NEGATIVE) {
        uint8_t y_value = 0x14;
        uint8_t a_value = 0xff;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {TAY};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_y().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TSX) {
        uint8_t sp_value = 0x04;
        uint8_t x_value = 0x14;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {TXS};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_stack_pointer().set_value(sp_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_stack_pointer().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TSX_ZERO) {
        uint8_t sp_value = 0x00;
        uint8_t x_value = 0x14;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {TXS};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_stack_pointer().set_value(sp_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_stack_pointer().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TSX_NEGATIVE) {
        uint8_t sp_value = 0xff;
        uint8_t x_value = 0x14;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {TXS};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_stack_pointer().set_value(sp_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_stack_pointer().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TXA) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x04;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {TXA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TXA_ZERO) {
        uint8_t x_value = 0x00;
        uint8_t a_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {TXA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TXA_NEGATIVE) {
        uint8_t x_value = 0xff;
        uint8_t a_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {TXA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TXS) {
        uint8_t x_value = 0x04;
        uint8_t sp_value = 0x14;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {TXS};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_stack_pointer().set_value(sp_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_stack_pointer().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TXS_ZERO) {
        uint8_t sp_value = 0x04;
        uint8_t x_value = 0x0;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {TXS};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_stack_pointer().set_value(sp_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_stack_pointer().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TXS_NEGATIVE) {
        uint8_t sp_value = 0x04;
        uint8_t x_value = 0xff;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {TXS};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_stack_pointer().set_value(sp_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_stack_pointer().get_value(), machine.get_cpu().get_x().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TYA) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x04;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {TYA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_y().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TYA_ZERO) {
        uint8_t y_value = 0x00;
        uint8_t a_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {TYA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_y().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(TransferOpcodeHandlers, TYA_NEGATIVE) {
        uint8_t y_value = 0xff;
        uint8_t a_value = 0x14;
        auto flags = std::bitset<8>(0);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {TYA};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_a().get_value(), machine.get_cpu().get_y().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

}
