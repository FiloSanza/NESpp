#include "compare_opcodes_handlers.h"

namespace nespp::compare_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers =  std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::CMP_IMM,cmp_imm);
        handlers.emplace(Opcodes::CMP_ZERO,cmp_zero);
        handlers.emplace(Opcodes::CMP_ZERO_X,cmp_zero_x);
        handlers.emplace(Opcodes::CMP_ABS, cmp_absolute);
        handlers.emplace(Opcodes::CMP_ABS_X, cmp_absolute_x);
        handlers.emplace(Opcodes::CMP_ABS_Y, cmp_absolute_y);
        handlers.emplace(Opcodes::CMP_IND_X, cmp_indirect_x);
        handlers.emplace(Opcodes::CMP_IND_Y, cmp_indirect_y);
        handlers.emplace(Opcodes::CPX_IMM, cpx_immediate);
        handlers.emplace(Opcodes::CPX_ZERO,cpx_zero);
        handlers.emplace(Opcodes::CPX_ABS, cpx_absolute);
        handlers.emplace(Opcodes::CPY_IMM, cpy_immediate);
        handlers.emplace(Opcodes::CPY_ZERO,cpy_zero);
        handlers.emplace(Opcodes::CPY_ABS, cpy_absolute);


        return handlers;
    }

    void cmp(Cpu &cpu, Register<uint8_t> &reg, uint8_t value) {
        uint8_t result = reg.get_value() - value;
        auto &ps = cpu.get_program_status();

        ps.set_zero(result == 0);
        ps.set_carry(reg.get_value() >= value);
        ps.set_negative(bits::get_nth_bit(result, 7));
    }

    void cmp_imm(Cpu &cpu) {
        uint8_t value = cpu.get_u8();
        cmp(cpu, cpu.get_a(), value);
    }

    void cmp_zero(Cpu &cpu) {
        uint8_t value = cpu.get_zero_value();
        cmp(cpu, cpu.get_a(), value);
    }

    void cmp_zero_x(Cpu &cpu) {
        uint8_t value = cpu.get_zero_x_value();
        cmp(cpu, cpu.get_a(), value);
    }

    void cmp_absolute(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_value();
        cmp(cpu, cpu.get_a(), value);
    }

    void cmp_absolute_x(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_x_value();
        cmp(cpu, cpu.get_a(), value);
    }

    void cmp_absolute_y(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_y_value();
        cmp(cpu, cpu.get_a(), value);
    }

    void cmp_indirect_x(Cpu &cpu) {
        uint8_t value = cpu.get_indirect_x_value();
        cmp(cpu, cpu.get_a(), value);
    }

    void cmp_indirect_y(Cpu &cpu) {
        uint8_t value = cpu.get_indirect_y_value();
        cmp(cpu, cpu.get_a(), value);
    }

    void cpx_immediate(Cpu &cpu) {
        uint8_t value = cpu.get_u8();
        cmp(cpu, cpu.get_x(), value);
    }

    void cpx_zero(Cpu &cpu) {
        uint8_t value = cpu.get_zero_value();
        cmp(cpu, cpu.get_x(), value);
    }

    void cpx_absolute(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_value();
        cmp(cpu, cpu.get_x(), value);
    }

    void cpy_immediate(Cpu &cpu) {
        uint8_t value = cpu.get_u8();
        cmp(cpu, cpu.get_y(), value);
    }

    void cpy_zero(Cpu &cpu) {
        uint8_t value = cpu.get_zero_value();
        cmp(cpu, cpu.get_y(), value);
    }

    void cpy_absolute(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_value();
        cmp(cpu, cpu.get_y(), value);
    }
}