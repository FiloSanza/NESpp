#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "gtest/gtest.h"

#include "cpu/machine.h"

namespace nespp::tests {

    constexpr uint8_t CMP_IMM    = 0xc9;
    constexpr uint8_t CMP_ZERO   = 0xc5;
    constexpr uint8_t CMP_ZERO_X = 0xd5;
    constexpr uint8_t CMP_ABS    = 0xcd;
    constexpr uint8_t CMP_ABS_X  = 0xdd;
    constexpr uint8_t CMP_ABS_Y  = 0xd9;
    constexpr uint8_t CMP_IND_X  = 0xc1;
    constexpr uint8_t CMP_IND_Y  = 0xd1;
    constexpr uint8_t CPX_IMM    = 0xe0;
    constexpr uint8_t CPX_ZERO   = 0xe4;
    constexpr uint8_t CPX_ABS    = 0xec;
    constexpr uint8_t CPY_IMM    = 0xc0;
    constexpr uint8_t CPY_ZERO   = 0xc4;
    constexpr uint8_t CPY_ABS    = 0xcc;

    constexpr uint16_t LOAD_ADDR      = 0x200;
    constexpr uint16_t ZERO_PAGE_ADDR = 0x10;
    constexpr uint16_t ABS_ADDR_LOW   = 0x20;
    constexpr uint16_t ABS_ADDR_HIGH  = 0x10;
    constexpr uint16_t ABS_ADDR       = 0x1020;

    TEST(StoreOpcodeHandlers, CMP_IMM_CARRY) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CMP_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_IMM_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CMP_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_IMM_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t immediate_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CMP_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ZERO_CARRY) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CMP_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ZERO_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CMP_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ZERO_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CMP_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ZERO_X_CARRY) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CMP_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        cpu.get_a().set_value(a_value);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ZERO_X_WRAP_AROUND) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0xf5;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CMP_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        cpu.get_a().set_value(a_value);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ZERO_X_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CMP_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        cpu.get_a().set_value(a_value);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ZERO_X_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CMP_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        cpu.get_a().set_value(a_value);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ABS_CARRY) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CMP_ABS, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ABS_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CMP_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ABS_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CMP_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ABS_X_CARRY) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x01;
        uint8_t x_value = 0x30;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CMP_ABS_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = x_value + ABS_ADDR;
        cpu.get_x().set_value(x_value);
        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ABS_X_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x14;
        uint8_t x_value = 0x30;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CMP_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = x_value + ABS_ADDR;
        cpu.get_a().set_value(a_value);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ABS_X_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x20;
        uint8_t x_value = 0x30;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CMP_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = x_value + ABS_ADDR;
        cpu.get_a().set_value(a_value);
        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ABS_Y_CARRY) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x01;
        uint8_t y_value = 0x30;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CMP_ABS_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = y_value + ABS_ADDR;
        cpu.get_y().set_value(y_value);
        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ABS_Y_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x14;
        uint8_t y_value = 0x30;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CMP_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = y_value + ABS_ADDR;
        cpu.get_a().set_value(a_value);
        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_ABS_Y_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t memory_value = 0x20;
        uint8_t y_value = 0x30;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CMP_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = y_value + ABS_ADDR;
        cpu.get_a().set_value(a_value);
        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_IND_X_CARRY) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x01;
        uint16_t indirect_addr = 0x300;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CMP_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        cpu.get_x().set_value(x_value);
        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u16(address, indirect_addr);
        cpu.get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_IND_X_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x14;
        uint16_t indirect_addr = 0x300;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CMP_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        cpu.get_x().set_value(x_value);
        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u16(address, indirect_addr);
        cpu.get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_IND_X_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x30;
        uint8_t memory_value = 0x20;
        uint16_t indirect_addr = 0x300;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CMP_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;
        cpu.get_x().set_value(x_value);
        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u16(address, indirect_addr);
        cpu.get_memory().set_u8(indirect_addr, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_IND_Y_CARRY) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x01;
        uint16_t indirect_addr = 0x300;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CMP_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = y_value + indirect_addr;
        cpu.get_y().set_value(y_value);
        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_IND_Y_ZERO) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x14;
        uint16_t indirect_addr = 0x300;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CMP_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = y_value + indirect_addr;
        cpu.get_y().set_value(y_value);
        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CMP_IND_Y_NEGATIVE) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x30;
        uint8_t memory_value = 0x20;
        uint16_t indirect_addr = 0x300;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CMP_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        auto address = y_value + indirect_addr;
        cpu.get_y().set_value(y_value);
        cpu.get_a().set_value(a_value);
        cpu.get_memory().set_u16(ZERO_PAGE_ADDR, indirect_addr);
        cpu.get_memory().set_u8(address, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_a().get_value(), a_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPX_IMM_CARRY) {
        uint8_t x_value = 0x14;
        uint8_t immediate_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CPX_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), x_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPX_IMM_ZERO) {
        uint8_t x_value = 0x14;
        uint8_t immediate_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CPX_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), x_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPX_IMM_NEGATIVE) {
        uint8_t x_value = 0x14;
        uint8_t immediate_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CPX_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), x_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPX_ZERO_CARRY) {
        uint8_t x_value = 0x14;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CPX_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), x_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPX_ZERO_ZERO) {
        uint8_t x_value = 0x14;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CPX_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), x_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPX_ZERO_NEGATIVE) {
        uint8_t x_value = 0x14;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CPX_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), x_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPX_ABS_CARRY) {
        uint8_t x_value = 0x14;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CPX_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), x_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPX_ABS_ZERO) {
        uint8_t x_value = 0x14;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CPX_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), x_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPX_ABS_NEGATIVE) {
        uint8_t x_value = 0x14;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CPX_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_x().set_value(x_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_x().get_value(), x_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPY_IMM_CARRY) {
        uint8_t y_value = 0x14;
        uint8_t immediate_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CPY_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_y().set_value(y_value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), y_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPY_IMM_ZERO) {
        uint8_t y_value = 0x14;
        uint8_t immediate_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CPY_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_y().set_value(y_value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), y_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPY_IMM_NEGATIVE) {
        uint8_t y_value = 0x14;
        uint8_t immediate_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CPY_IMM, immediate_value};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_y().set_value(y_value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), y_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPY_ZERO_CARRY) {
        uint8_t y_value = 0x14;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CPY_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), y_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPY_ZERO_ZERO) {
        uint8_t y_value = 0x14;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CPY_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), y_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPY_ZERO_NEGATIVE) {
        uint8_t y_value = 0x14;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CPY_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(ZERO_PAGE_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), y_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPY_ABS_CARRY) {
        uint8_t y_value = 0x14;
        uint8_t memory_value = 0x01;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;

        std::vector<uint8_t> rom = {CPY_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), y_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPY_ABS_ZERO) {
        uint8_t y_value = 0x14;
        uint8_t memory_value = 0x14;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Carry] = true;
        flags[Flags::Zero] = true;

        std::vector<uint8_t> rom = {CPY_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), y_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, CPY_ABS_NEGATIVE) {
        uint8_t y_value = 0x14;
        uint8_t memory_value = 0x20;
        auto flags = std::bitset<8>(0x24);
        flags[Flags::Negative] = true;

        std::vector<uint8_t> rom = {CPY_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);
		auto &cpu = machine.get_cpu();

        cpu.get_y().set_value(y_value);
        cpu.get_memory().set_u8(ABS_ADDR, memory_value);

        machine.execute();

        EXPECT_EQ(cpu.get_y().get_value(), y_value);
        EXPECT_EQ(cpu.get_program_status().get_value(), flags);
    }

}

#pragma clang diagnostic pop