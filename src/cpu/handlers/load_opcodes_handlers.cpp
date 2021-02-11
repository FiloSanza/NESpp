#include "load_opcodes_handlers.h"

namespace nespp::load_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::LDA_IMM, lda_immediate);
        handlers.emplace(Opcodes::LDA_ZERO, lda_zero);
        handlers.emplace(Opcodes::LDA_ZERO_X, lda_zero_x);
        handlers.emplace(Opcodes::LDA_ABS, lda_absolute);
        handlers.emplace(Opcodes::LDA_ABS_X, lda_absolute_x);
        handlers.emplace(Opcodes::LDA_ABS_Y, lda_absolute_y);
        handlers.emplace(Opcodes::LDA_IND_X, lda_indirect_x);
        handlers.emplace(Opcodes::LDA_IND_Y, lda_indirect_y);
        handlers.emplace(Opcodes::LDX_IMM, ldx_immediate);
        handlers.emplace(Opcodes::LDX_ZERO, ldx_zero);
        handlers.emplace(Opcodes::LDX_ZERO_Y, ldx_zero_y);
        handlers.emplace(Opcodes::LDX_ABS, ldx_absolute);
        handlers.emplace(Opcodes::LDX_ABS_Y, ldx_absolute_y);
        handlers.emplace(Opcodes::LDY_IMM, ldy_immediate);
        handlers.emplace(Opcodes::LDY_ZERO, ldy_zero);
        handlers.emplace(Opcodes::LDY_ZERO_X, ldy_zero_x);
        handlers.emplace(Opcodes::LDY_ABS, ldy_absolute);
        handlers.emplace(Opcodes::LDY_ABS_X, ldy_absolute_x);

        return handlers;
    }

    void load(Cpu &cpu, Register<uint8_t> &reg, uint8_t value) {
        auto &ps = cpu.get_program_status();
        reg.set_value(value);

        ps.set_zero(value == 0);
        ps.set_negative(utils::get_nth_bit(value, 7));
    }

    void lda_immediate(Cpu &cpu) {
        auto value = cpu.get_u8();
        load(cpu, cpu.get_a(), value);
    }

    void lda_zero(Cpu &cpu) {
        auto value = cpu.get_zero_value();
        load(cpu, cpu.get_a(), value);
    }

    void lda_zero_x(Cpu &cpu) {
        auto value = cpu.get_zero_x_value();
        load(cpu, cpu.get_a(), value);
    }

    void lda_absolute(Cpu &cpu) {
        auto value = cpu.get_absolute_value();
        load(cpu, cpu.get_a(), value);
    }

    void lda_absolute_x(Cpu &cpu) {
        auto value = cpu.get_absolute_x_value();
        load(cpu, cpu.get_a(), value);
    }

    void lda_absolute_y(Cpu &cpu) {
        auto value = cpu.get_absolute_y_value();
        load(cpu, cpu.get_a(), value);
    }

    void lda_indirect_x(Cpu &cpu) {
        auto value = cpu.get_indirect_x_value();
        load(cpu, cpu.get_a(), value);
    }

    void lda_indirect_y(Cpu &cpu) {
        auto value = cpu.get_indirect_y_value();
        load(cpu, cpu.get_a(), value);
    }

    void ldx_immediate(Cpu &cpu) {
        auto value = cpu.get_u8();
        load(cpu, cpu.get_x(), value);
    }

    void ldx_zero(Cpu &cpu) {
        auto value = cpu.get_zero_value();
        load(cpu, cpu.get_x(), value);
    }

    void ldx_zero_y(Cpu &cpu) {
        auto value = cpu.get_zero_y_value();
        load(cpu, cpu.get_x(), value);
    }

    void ldx_absolute(Cpu &cpu) {
        auto value = cpu.get_absolute_value();
        load(cpu, cpu.get_x(), value);
    }

    void ldx_absolute_y(Cpu &cpu) {
        auto value = cpu.get_absolute_y_value();
        load(cpu, cpu.get_x(), value);
    }

    void ldy_immediate(Cpu &cpu) {
        auto value = cpu.get_u8();
        load(cpu, cpu.get_y(), value);
    }

    void ldy_zero(Cpu &cpu) {
        auto value = cpu.get_zero_value();
        load(cpu, cpu.get_y(), value);
    }

    void ldy_zero_x(Cpu &cpu) {
        auto value = cpu.get_zero_x_value();
        load(cpu, cpu.get_y(), value);
    }

    void ldy_absolute(Cpu &cpu) {
        auto value = cpu.get_absolute_value();
        load(cpu, cpu.get_y(), value);
    }

    void ldy_absolute_x(Cpu &cpu) {
        auto value = cpu.get_absolute_x_value();
        load(cpu, cpu.get_y(), value);
    }


}