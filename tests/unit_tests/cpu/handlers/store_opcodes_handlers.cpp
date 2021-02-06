#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "gtest/gtest.h"

#include "cpu/handlers/store_opcodes_handlers.h"
#include "cpu/machine.h"
#include <iostream>


namespace nespp::tests {

    constexpr uint8_t STA_ZERO    = 0x85;
    constexpr uint8_t STA_ZERO_X  = 0x95;
    constexpr uint8_t STA_ABS     = 0x8d;
    constexpr uint8_t STA_ABS_X   = 0x9d;
    constexpr uint8_t STA_ABS_Y   = 0x99;
    constexpr uint8_t STA_IND_X   = 0x81;
    constexpr uint8_t STA_IND_Y   = 0x91;

    constexpr uint16_t LOAD_ADDR      = 0x200;
    constexpr uint16_t ZERO_PAGE_ADDR = 0x10;
    constexpr uint16_t ABS_ADDR_LOW   = 0x20;
    constexpr uint16_t ABS_ADDR_HIGH  = 0x10;
    constexpr uint16_t ABS_ADDR       = 0x1020;

    TEST(StoreOpcodeHandlers, STA_ZERO) {
        uint8_t a_value = 0x14;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {STA_ZERO, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ZERO_PAGE_ADDR), machine.get_cpu().get_a().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, STA_ZERO_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x20;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {STA_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), machine.get_cpu().get_a().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, STA_ZERO_X_WRAP_AROUND) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0xf5;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {STA_ZERO_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        auto address = (ZERO_PAGE_ADDR + x_value) & 0xff;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), machine.get_cpu().get_a().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, STA_ABS) {
        uint8_t a_value = 0x14;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {STA_ABS, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(ABS_ADDR), machine.get_cpu().get_a().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, STA_ABS_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {STA_ABS_X, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        auto address = ABS_ADDR + x_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), machine.get_cpu().get_a().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, STA_ABS_Y) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x10;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {STA_ABS_Y, ABS_ADDR_LOW, ABS_ADDR_HIGH};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.execute();

        auto address = ABS_ADDR + y_value;
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), machine.get_cpu().get_a().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, STA_IND_X) {
        uint8_t a_value = 0x14;
        uint8_t x_value = 0x15;
        uint16_t indirect_addr = 0x220;

        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {STA_IND_X, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        auto address = (x_value + ZERO_PAGE_ADDR) & 0xff;

        std::cerr << "address: 0x" << std::hex << std::setfill('0') << std::setw(4) << address << "\n";

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_x().set_value(x_value);
        machine.get_cpu().get_program_status().set_value(0);

        machine.get_cpu().get_memory().add_callback_on_read([](uint16_t addr, uint16_t value) {
            std::cerr << "Reading 0x" << std::hex << std::setfill('0') << std::setw(4) << value << " @ 0x" << std::hex << std::setfill('0') << std::setw(4) << addr << "\n";
        });

        machine.get_cpu().get_memory().add_callback_on_write([](uint16_t addr, uint16_t value) {
            std::cerr << "Writing 0x" << std::hex << std::setfill('0') << std::setw(4) << value << " @ 0x" << std::hex << std::setfill('0') << std::setw(4) << addr << "\n";
        });

        std::cerr << "SETUP\n";
        machine.get_cpu().get_memory().set_u16(address, indirect_addr);

        std::cerr << "EXECUTE\n";
        machine.execute();

        std::cerr << "CHECK\n";
        EXPECT_EQ(machine.get_cpu().get_memory().get_u16(indirect_addr), machine.get_cpu().get_a().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }

    TEST(StoreOpcodeHandlers, STA_IND_Y) {
        uint8_t a_value = 0x14;
        uint8_t y_value = 0x10;
        uint8_t zero_pg_addr = 0xf3;
        auto flags = std::bitset<8>(0);

        std::vector<uint8_t> rom = {STA_IND_Y, ZERO_PAGE_ADDR};
        auto machine = Machine(rom, LOAD_ADDR);

        machine.get_cpu().get_a().set_value(a_value);
        machine.get_cpu().get_y().set_value(y_value);
        machine.get_cpu().get_program_status().set_value(0);
        machine.get_cpu().get_memory().set_u8(ZERO_PAGE_ADDR, zero_pg_addr);

        machine.execute();

        auto address = ((uint16_t)y_value + zero_pg_addr);
        EXPECT_EQ(machine.get_cpu().get_memory().get_u8(address), machine.get_cpu().get_a().get_value());
        EXPECT_EQ(machine.get_cpu().get_program_status().get_value(), flags);
    }
}

#pragma clang diagnostic pop