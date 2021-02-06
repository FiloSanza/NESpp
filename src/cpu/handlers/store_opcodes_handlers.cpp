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

        return handlers;
    }

    void sta(Cpu &cpu, Register<uint8_t> &reg, uint16_t address) {
        cpu.get_memory().set_u8(address, reg.get_value());
    }

    void sta_zero(Cpu &cpu) {
        uint16_t address = cpu.get_u8();
        sta(cpu, cpu.get_a(), address);
    }

    void sta_zero_x(Cpu &cpu) {
        uint16_t address = cpu.get_u8() + cpu.get_x().get_value();
        address &= 0xffu;
        sta(cpu, cpu.get_a(), address);
    }

    void sta_absolute(Cpu &cpu) {
        uint16_t address = cpu.get_u16();
        sta(cpu, cpu.get_a(), address);
    }

    void sta_absolute_x(Cpu &cpu) {
        uint16_t address = cpu.get_u16() + cpu.get_x().get_value();
        sta(cpu, cpu.get_a(), address);
    }

    void sta_absolute_y(Cpu &cpu) {
        uint16_t address = cpu.get_u16() + cpu.get_y().get_value();
        sta(cpu, cpu.get_a(), address);
    }

    void sta_indirect_x(Cpu &cpu) {
        uint16_t indirect_address = cpu.get_u8() + cpu.get_x().get_value();
        indirect_address &= 0xffu;
        uint16_t address = cpu.get_memory().get_u16(indirect_address);
        sta(cpu, cpu.get_a(), address);
    }

    void sta_indirect_y(Cpu &cpu) {
        uint16_t indirect_address = cpu.get_u8();
        uint16_t address = cpu.get_memory().get_u16(indirect_address) + cpu.get_y().get_value();
        sta(cpu, cpu.get_a(), address);
    }
}