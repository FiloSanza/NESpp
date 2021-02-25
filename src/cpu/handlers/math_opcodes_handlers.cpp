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

        handlers.emplace(Opcodes::INC_ZERO, inc_zero);
        handlers.emplace(Opcodes::INC_ZERO_X, inc_zero_x);
        handlers.emplace(Opcodes::INC_ABS, inc_abs);
        handlers.emplace(Opcodes::INC_ABS_X, inc_abs_x);
        handlers.emplace(Opcodes::INX, inx);
        handlers.emplace(Opcodes::INY, iny);

        handlers.emplace(Opcodes::ADC_IMM, adc_immediate);
        handlers.emplace(Opcodes::ADC_ZERO, adc_zero);
        handlers.emplace(Opcodes::ADC_ZERO_X, adc_zero_x);
        handlers.emplace(Opcodes::ADC_ABS, adc_absolute);
        handlers.emplace(Opcodes::ADC_ABS_X, adc_absolute_x);
        handlers.emplace(Opcodes::ADC_ABS_Y, adc_absolute_y);
        handlers.emplace(Opcodes::ADC_IND_X, adc_indirect_x);
        handlers.emplace(Opcodes::ADC_IND_Y, adc_indirect_y);

        handlers.emplace(Opcodes::SBC_IMM, sbc_immediate);
        handlers.emplace(Opcodes::SBC_ZERO, sbc_zero);
        handlers.emplace(Opcodes::SBC_ZERO_X, sbc_zero_x);
        handlers.emplace(Opcodes::SBC_ABS, sbc_absolute);
        handlers.emplace(Opcodes::SBC_ABS_X, sbc_absolute_x);
        handlers.emplace(Opcodes::SBC_ABS_Y, sbc_absolute_y);
        handlers.emplace(Opcodes::SBC_IND_X, sbc_indirect_x);
        handlers.emplace(Opcodes::SBC_IND_Y, sbc_indirect_y);

        return handlers;
    }

    void dec_memory(Cpu &cpu, uint16_t address) {
        auto &memory = cpu.get_memory();

        uint8_t value = memory.get_u8(address);
        memory.set_u8(address, --value);

        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(bits::get_nth_bit(value, 7));
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
        cpu.get_program_status().set_negative(bits::get_nth_bit(value, 7));
    }

    void dex(Cpu &cpu) {
        dec_register(cpu, cpu.get_x());
    }

    void dey(Cpu &cpu) {
        dec_register(cpu, cpu.get_y());
    }

    void inc_memory(Cpu &cpu, uint16_t address) {
        auto &memory = cpu.get_memory();

        uint8_t value = memory.get_u8(address);
        memory.set_u8(address, ++value);

        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(bits::get_nth_bit(value, 7));
    }

    void inc_zero(Cpu &cpu) {
        uint16_t address = cpu.get_u8();
        inc_memory(cpu, address);
    }

    void inc_zero_x(Cpu &cpu) {
        auto address = cpu.get_zero_x_address();
        inc_memory(cpu, address);
    }

    void inc_abs(Cpu &cpu) {
        auto address = cpu.get_u16();
        inc_memory(cpu, address);
    }

    void inc_abs_x(Cpu &cpu) {
        auto address = cpu.get_absolute_x_address();
        inc_memory(cpu, address);
    }

    void inc_register(Cpu &cpu, Register<uint8_t> &reg) {
        uint8_t value = reg.get_value();
        reg.set_value(++value);

        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(bits::get_nth_bit(value, 7));
    }

    void inx(Cpu &cpu) {
        inc_register(cpu, cpu.get_x());
    }

    void iny(Cpu &cpu) {
        inc_register(cpu, cpu.get_y());
    }

    void adc(Cpu &cpu, Register<uint8_t> &reg, uint16_t value) {
        auto old_val = reg.get_value();
        auto &ps = cpu.get_program_status();

        uint16_t result = value + reg.get_value();
        result += ps.is_carry_set();

        reg.set_value(result & 0xffu);

        //overflow happens when result's sign is wrong (value and old_val both positive but negative result and the opposite)
        bool overflow = ((old_val ^ result) & (value ^ result) & 0x80) != 0;

        ps.set_zero((result & 0xffu) == 0);
        ps.set_carry(result >= 0x100);
        ps.set_overflow(overflow);
        ps.set_negative(bits::get_nth_bit(result, 7));

    }

    void adc_immediate(Cpu &cpu) {
        auto value = cpu.get_u8();
        adc(cpu, cpu.get_a(), value);
    }

    void adc_zero(Cpu &cpu) {
        auto value = cpu.get_zero_value();
        adc(cpu, cpu.get_a(), value);
    }

    void adc_zero_x(Cpu &cpu) {
        auto value = cpu.get_zero_x_value();
        adc(cpu, cpu.get_a(), value);
    }

    void adc_absolute(Cpu &cpu) {
        auto value = cpu.get_absolute_value();
        adc(cpu, cpu.get_a(), value);
    }

    void adc_absolute_x(Cpu &cpu) {
        auto value = cpu.get_absolute_x_value();
        adc(cpu, cpu.get_a(), value);
    }

    void adc_absolute_y(Cpu &cpu) {
        auto value = cpu.get_absolute_y_value();
        adc(cpu, cpu.get_a(), value);
    }

    void adc_indirect_x(Cpu &cpu) {
        auto value = cpu.get_indirect_x_value();
        adc(cpu, cpu.get_a(), value);
    }

    void adc_indirect_y(Cpu &cpu) {
        auto value = cpu.get_indirect_y_value();
        adc(cpu, cpu.get_a(), value);
    }

    void sbc(Cpu &cpu, Register<uint8_t> &reg, uint16_t value) {
        auto old_val = reg.get_value();
        auto &ps = cpu.get_program_status();

        uint16_t result = old_val;
        result = result - value - (cpu.get_program_status().is_carry_set() ? 0 : 1);

        reg.set_value(result & 0xffu);

        bool overflow = ((old_val ^ result) & 0x80) && ((old_val ^ value) & 0x80);

        ps.set_zero((result & 0xffu) == 0);
        ps.set_carry(result < 0x100);
        ps.set_overflow(overflow);
        ps.set_negative(bits::get_nth_bit(result, 7));
    }

    void sbc_immediate(Cpu &cpu) {
        auto value = cpu.get_u8();
        sbc(cpu, cpu.get_a(), value);
    }

    void sbc_zero(Cpu &cpu) {
        auto value = cpu.get_zero_value();
        sbc(cpu, cpu.get_a(), value);
    }

    void sbc_zero_x(Cpu &cpu) {
        auto value = cpu.get_zero_x_value();
        sbc(cpu, cpu.get_a(), value);
    }

    void sbc_absolute(Cpu &cpu) {
        auto value = cpu.get_absolute_value();
        sbc(cpu, cpu.get_a(), value);
    }

    void sbc_absolute_x(Cpu &cpu) {
        auto value = cpu.get_absolute_x_value();
        sbc(cpu, cpu.get_a(), value);
    }

    void sbc_absolute_y(Cpu &cpu) {
        auto value = cpu.get_absolute_y_value();
        sbc(cpu, cpu.get_a(), value);
    }

    void sbc_indirect_x(Cpu &cpu) {
        auto value = cpu.get_indirect_x_value();
        sbc(cpu, cpu.get_a(), value);
    }

    void sbc_indirect_y(Cpu &cpu) {
        auto value = cpu.get_indirect_y_value();
        sbc(cpu, cpu.get_a(), value);
    }

}