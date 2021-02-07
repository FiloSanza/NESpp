#include "store_opcodes_handlers.h"

namespace nespp::store_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::STA_ZERO, sta_zero);
        handlers.emplace(Opcodes::STA_ZERO_X, sta_zero_x);
        handlers.emplace(Opcodes::STA_ABS, sta_absolute);
        handlers.emplace(Opcodes::STA_ABS_X, sta_absolute_x);
        handlers.emplace(Opcodes::STA_ABS_Y, sta_absolute_y);
        handlers.emplace(Opcodes::STA_IND_X, sta_indirect_x);
        handlers.emplace(Opcodes::STA_IND_Y, sta_indirect_y);
        handlers.emplace(Opcodes::STX_ZERO, stx_zero);
        handlers.emplace(Opcodes::STX_ZERO_Y, stx_zero_y);
        handlers.emplace(Opcodes::STX_ABS, stx_absolute);
        handlers.emplace(Opcodes::STY_ZERO, sty_zero);
        handlers.emplace(Opcodes::STY_ZERO_X, sty_zero_x);
        handlers.emplace(Opcodes::STY_ABS, sty_absolute);


        return handlers;
    }

    void store(Cpu &cpu, Register<uint8_t> &reg, uint16_t address) {
        cpu.get_memory().set_u8(address, reg.get_value());
    }

    void sta_zero(Cpu &cpu) {
        uint16_t address = cpu.get_u8();
        store(cpu, cpu.get_a(), address);
    }

    void sta_zero_x(Cpu &cpu) {
        auto address = cpu.get_zero_x_address();
        store(cpu, cpu.get_a(), address);
    }

    void sta_absolute(Cpu &cpu) {
        uint16_t address = cpu.get_u16();
        store(cpu, cpu.get_a(), address);
    }

    void sta_absolute_x(Cpu &cpu) {
        uint16_t address = cpu.get_absolute_x_address();
        store(cpu, cpu.get_a(), address);
    }

    void sta_absolute_y(Cpu &cpu) {
        uint16_t address = cpu.get_absolute_y_address();
        store(cpu, cpu.get_a(), address);
    }

    void sta_indirect_x(Cpu &cpu) {
        auto address = cpu.get_indirect_x_address();
        store(cpu, cpu.get_a(), address);
    }

    void sta_indirect_y(Cpu &cpu) {
        auto address = cpu.get_indirect_y_address();
        store(cpu, cpu.get_a(), address);
    }

    void stx_zero(Cpu &cpu) {
        uint16_t address = cpu.get_u8();
        store(cpu, cpu.get_x(), address);
    }

    void stx_zero_y(Cpu &cpu) {
        uint16_t address = cpu.get_u8() + cpu.get_y().get_value();
        address &= 0xffu;
        store(cpu, cpu.get_x(), address);
    }

    void stx_absolute(Cpu &cpu) {
        uint16_t address = cpu.get_u16();
        store(cpu, cpu.get_x(), address);
    }

    void sty_zero(Cpu &cpu) {
        uint16_t address = cpu.get_u8();
        store(cpu, cpu.get_y(), address);
    }

    void sty_zero_x(Cpu &cpu) {
        uint16_t address = cpu.get_u8() + cpu.get_x().get_value();
        address &= 0xffu;
        store(cpu, cpu.get_y(), address);
    }

    void sty_absolute(Cpu &cpu) {
        uint16_t address = cpu.get_u16();
        store(cpu, cpu.get_y(), address);
    }
}