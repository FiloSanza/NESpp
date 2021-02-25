#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "gtest/gtest.h"

#include "cpu/machine.h"

namespace nespp::tests {

    constexpr uint8_t RTS     = 0x60;
    constexpr uint8_t JMP_ABS = 0x4c;
    constexpr uint8_t JMP_IND = 0x6c;
    constexpr uint8_t JSR     = 0x20;

    constexpr uint16_t LOAD_ADDR = 0x200;
    constexpr uint16_t ABS_ADDR = 0x3020;
    constexpr uint16_t ABS_ADDR_LOW = 0x20;
    constexpr uint16_t ABS_ADDR_HIGH = 0x30;

    TEST(JumpOpcodeHandlers, JMP_IND) {
        uint16_t value = 0x2010;
        uint8_t low_value = 0x10;
        uint8_t high_value = 0x20;

        std::vector<uint8_t> rom = {JMP_IND, low_value, high_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &pc = machine.get_cpu().get_program_counter();

        machine.execute();

        EXPECT_EQ(pc.get_value(), value);
    }

    TEST(JumpOpcodeHandlers, JMP_ABS) {
        uint16_t value = 0x2010;

        std::vector<uint8_t> rom = {JMP_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &pc = machine.get_cpu().get_program_counter();

        machine.get_cpu().get_memory().set_u16(ABS_ADDR, value);

        machine.execute();

        EXPECT_EQ(pc.get_value(), value);
    }

    TEST(JumpOpcodeHandlers, JSR) {
        std::vector<uint8_t> rom = {JSR, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &pc = machine.get_cpu().get_program_counter();

        machine.execute();

        auto low_pc = machine.get_cpu().get_stack().pop();
        auto high_pc = machine.get_cpu().get_stack().pop();
        auto queued_pc = bits::merge_u8(low_pc, high_pc);
        EXPECT_EQ(queued_pc, LOAD_ADDR + 3);
    }

    TEST(JumpOpcodeHandlers, RTS) {
        uint16_t value = 0x2010;

        std::vector<uint8_t> rom = {JSR, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &pc = machine.get_cpu().get_program_counter();

        machine.get_cpu().get_memory().set_u16(ABS_ADDR, value);
        machine.get_cpu().get_memory().set_u8(value, RTS);

        machine.execute();
        machine.execute();

        EXPECT_EQ(pc.get_value(), LOAD_ADDR + 3);
    }

}

#pragma clang diagnostic pop