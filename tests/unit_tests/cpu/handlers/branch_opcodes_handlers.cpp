#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "gtest/gtest.h"

#include "cpu/handlers/branch_opcodes_handlers.h"
#include "cpu/machine.h"

namespace nespp::tests {
    constexpr uint8_t BCC = 0x90;
    constexpr uint8_t BCS = 0xb0;
    constexpr uint8_t BEQ = 0xf0;
    constexpr uint8_t BNE = 0xd0;
    constexpr uint8_t BMI = 0x30;
    constexpr uint8_t BPL = 0x10;
    constexpr uint8_t BVC = 0x50;
    constexpr uint8_t BVS = 0x70;

    constexpr uint16_t LOAD_ADDR = 0x200;
    constexpr uint8_t OFFSET     = 0x0f;

    TEST(BranchOpcodesHandlers, BCC_BRANCH) {
        std::vector<uint8_t> rom = {BCC, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + OFFSET + 0x2);
    }

    TEST(BranchOpcodesHandlers, BCC_NO_BRANCH) {
        std::vector<uint8_t> rom = {BCC, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_program_status().set_carry(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + 0x2);
    }

    TEST(BranchOpcodesHandlers, BCS_BRANCH) {
        std::vector<uint8_t> rom = {BCS, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_program_status().set_carry(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + OFFSET + 0x2);
    }

    TEST(BranchOpcodesHandlers, BCS_NO_BRANCH) {
        std::vector<uint8_t> rom = {BCS, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + 0x2);
    }

    TEST(BranchOpcodesHandlers, BEQ_BRANCH) {
        std::vector<uint8_t> rom = {BEQ, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_program_status().set_zero(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + OFFSET + 0x2);
    }

    TEST(BranchOpcodesHandlers, BEQ_NO_BRANCH) {
        std::vector<uint8_t> rom = {BEQ, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + 0x2);
    }

    TEST(BranchOpcodesHandlers, BNE_BRANCH) {
        std::vector<uint8_t> rom = {BNE, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + OFFSET + 0x2);
    }

    TEST(BranchOpcodesHandlers, BNE_NO_BRANCH) {
        std::vector<uint8_t> rom = {BNE, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_program_status().set_zero(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + 0x2);
    }

    TEST(BranchOpcodesHandlers, BMI_BRANCH) {
        std::vector<uint8_t> rom = {BMI, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_program_status().set_negative(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + OFFSET + 0x2);
    }

    TEST(BranchOpcodesHandlers, BMI_NO_BRANCH) {
        std::vector<uint8_t> rom = {BMI, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + 0x2);
    }

    TEST(BranchOpcodesHandlers, BPL_BRANCH) {
        std::vector<uint8_t> rom = {BPL, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + OFFSET + 0x2);
    }

    TEST(BranchOpcodesHandlers, BPL_NO_BRANCH) {
        std::vector<uint8_t> rom = {BPL, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_program_status().set_negative(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + 0x2);
    }

    TEST(BranchOpcodesHandlers, BVC_BRANCH) {
        std::vector<uint8_t> rom = {BVC, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + OFFSET + 0x2);
    }

    TEST(BranchOpcodesHandlers, BVC_NO_BRANCH) {
        std::vector<uint8_t> rom = {BVC, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_program_status().set_overflow(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + 0x2);
    }

    TEST(BranchOpcodesHandlers, BVS_BRANCH) {
        std::vector<uint8_t> rom = {BVS, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_program_status().set_overflow(true);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + OFFSET + 0x2);
    }

    TEST(BranchOpcodesHandlers, BVS_NO_BRANCH) {
        std::vector<uint8_t> rom = {BVS, OFFSET};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_program_counter().get_value(), LOAD_ADDR + 0x2);
    }

}

#pragma clang diagnostic pop