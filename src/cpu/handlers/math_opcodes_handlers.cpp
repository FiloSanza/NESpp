#include "math_opcodes_handlers.h"

namespace nespp::math_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::DEC_ZERO, dec_zero);
        handlers.emplace(Opcodes::DEC_ZERO_X, dec_zero_x);
        handlers.emplace(Opcodes::DEC_ABS, dec_abs);
        handlers.emplace(Opcodes::DEC_ABS_X, dec_abs_x);
        handlers.emplace(Opcodes::DEX, dex);
        handlers.emplace(Opcodes::DEY, dey);

        return handlers;
    }

    void dec_memory(Cpu &cpu, uint16_t address) {
        auto &memory = cpu.get_memory();

        uint8_t value = memory.get_u8(address);
        memory.set_u8(address, --value);

        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(value, 7));
    }

    void dec_zero(Cpu &cpu) {
        uint16_t address = cpu.get_u8();
        dec_memory(cpu, address);
    }

    void dec_zero_x(Cpu &cpu) {
        auto address = cpu.get_zero_x_address();
        dec_memory(cpu, address);
    }

    void dec_abs(Cpu &cpu) {
        auto address = cpu.get_u16();
        dec_memory(cpu, address);
    }

    void dec_abs_x(Cpu &cpu) {
        auto address = cpu.get_absolute_x_address();
        dec_memory(cpu, address);
    }

    void dec_register(Cpu &cpu, Register<uint8_t> &reg) {
        uint8_t value = reg.get_value();
        reg.set_value(--value);

        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(value, 7));
    }

    void dex(Cpu &cpu) {
        dec_register(cpu, cpu.get_x());
    }

    void dey(Cpu &cpu) {
        dec_register(cpu, cpu.get_y());
    }
}