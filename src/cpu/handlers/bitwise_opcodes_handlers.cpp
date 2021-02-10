#include "bitwise_opcodes_handlers.h"

namespace nespp::bitwise_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::AND_IMM, and_immediate);
        handlers.emplace(Opcodes::AND_ZERO, and_zero);
        handlers.emplace(Opcodes::AND_ZERO_X, and_zero_x);
        handlers.emplace(Opcodes::AND_ABS, and_absolute);
        handlers.emplace(Opcodes::AND_ABS_X, and_absolute_x);
        handlers.emplace(Opcodes::AND_ABS_Y, and_absolute_y);
        handlers.emplace(Opcodes::AND_IND_X, and_indirect_x);
        handlers.emplace(Opcodes::AND_IND_Y, and_indirect_y);
        handlers.emplace(Opcodes::EOR_IMM, eor_immediate);
        handlers.emplace(Opcodes::EOR_ZERO, eor_zero);
        handlers.emplace(Opcodes::EOR_ZERO_X, eor_zero_x);
        handlers.emplace(Opcodes::EOR_ABS, eor_absolute);
        handlers.emplace(Opcodes::EOR_ABS_X, eor_absolute_x);
        handlers.emplace(Opcodes::EOR_ABS_Y, eor_absolute_y);
        handlers.emplace(Opcodes::EOR_IND_X, eor_indirect_x);
        handlers.emplace(Opcodes::EOR_IND_Y, eor_indirect_y);
        handlers.emplace(Opcodes::ORA_IMM, ora_immediate);
        handlers.emplace(Opcodes::ORA_ZERO, ora_zero);
        handlers.emplace(Opcodes::ORA_ZERO_X, ora_zero_x);
        handlers.emplace(Opcodes::ORA_ABS, ora_absolute);
        handlers.emplace(Opcodes::ORA_ABS_X, ora_absolute_x);
        handlers.emplace(Opcodes::ORA_ABS_Y, ora_absolute_y);
        handlers.emplace(Opcodes::ORA_IND_X, ora_indirect_x);
        handlers.emplace(Opcodes::ORA_IND_Y, ora_indirect_y);
        handlers.emplace(Opcodes::ROL_ACC, rol_acc);
        handlers.emplace(Opcodes::ROL_ZERO, rol_zero);
        handlers.emplace(Opcodes::ROL_ZERO_X, rol_zero_x);
        handlers.emplace(Opcodes::ROL_ABS, rol_abs);
        handlers.emplace(Opcodes::ROL_ABS_X, rol_abs_x);
        handlers.emplace(Opcodes::ROR_ACC, ror_acc);
        handlers.emplace(Opcodes::ROR_ZERO, ror_zero);
        handlers.emplace(Opcodes::ROR_ZERO_X, ror_zero_x);
        handlers.emplace(Opcodes::ROR_ABS, ror_abs);
        handlers.emplace(Opcodes::ROR_ABS_X, ror_abs_x);

        return handlers;
    }

    void bitwise_and(Cpu &cpu, Register<uint8_t> &a, uint8_t value) {
        uint8_t result = a.get_value() & value;
        a.set_value(result);

        cpu.get_program_status().set_zero(result == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(result, 7));
    }

    void and_immediate(Cpu &cpu) {
        uint8_t value = cpu.get_u8();
        bitwise_and(cpu, cpu.get_a(), value);
    }

    void and_zero(Cpu &cpu) {
        uint8_t value = cpu.get_zero_value();
        bitwise_and(cpu, cpu.get_a(), value);
    }

    void and_zero_x(Cpu &cpu) {
        uint8_t value = cpu.get_zero_x_value();
        bitwise_and(cpu, cpu.get_a(), value);
    }

    void and_absolute(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_value();
        bitwise_and(cpu, cpu.get_a(), value);
    }

    void and_absolute_x(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_x_value();
        bitwise_and(cpu, cpu.get_a(), value);
    }

    void and_absolute_y(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_y_value();
        bitwise_and(cpu, cpu.get_a(), value);
    }

    void and_indirect_x(Cpu &cpu) {
        uint8_t value = cpu.get_indirect_x_value();
        bitwise_and(cpu, cpu.get_a(), value);
    }

    void and_indirect_y(Cpu &cpu) {
        uint8_t value = cpu.get_indirect_y_value();
        bitwise_and(cpu, cpu.get_a(), value);
    }

    void bitwise_eor(Cpu &cpu, Register<uint8_t> &a, uint8_t value) {
        uint8_t result = a.get_value() ^ value;
        a.set_value(result);

        cpu.get_program_status().set_zero(result == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(result, 7));
    }

    void eor_immediate(Cpu &cpu) {
        uint8_t value = cpu.get_u8();
        bitwise_eor(cpu, cpu.get_a(), value);
    }

    void eor_zero(Cpu &cpu) {
        uint8_t value = cpu.get_zero_value();
        bitwise_eor(cpu, cpu.get_a(), value);
    }

    void eor_zero_x(Cpu &cpu) {
        uint8_t value = cpu.get_zero_x_value();
        bitwise_eor(cpu, cpu.get_a(), value);
    }

    void eor_absolute(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_value();
        bitwise_eor(cpu, cpu.get_a(), value);
    }

    void eor_absolute_x(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_x_value();
        bitwise_eor(cpu, cpu.get_a(), value);
    }

    void eor_absolute_y(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_y_value();
        bitwise_eor(cpu, cpu.get_a(), value);
    }

    void eor_indirect_x(Cpu &cpu) {
        uint8_t value = cpu.get_indirect_x_value();
        bitwise_eor(cpu, cpu.get_a(), value);
    }

    void eor_indirect_y(Cpu &cpu) {
        uint8_t value = cpu.get_indirect_y_value();
        bitwise_eor(cpu, cpu.get_a(), value);
    }

    void bitwise_ora(Cpu &cpu, Register<uint8_t> &a, uint8_t value) {
        uint8_t result = a.get_value() | value;
        a.set_value(result);

        cpu.get_program_status().set_zero(result == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(result, 7));
    }

    void ora_immediate(Cpu &cpu) {
        uint8_t value = cpu.get_u8();
        bitwise_ora(cpu, cpu.get_a(), value);
    }

    void ora_zero(Cpu &cpu) {
        uint8_t value = cpu.get_zero_value();
        bitwise_ora(cpu, cpu.get_a(), value);
    }

    void ora_zero_x(Cpu &cpu) {
        uint8_t value = cpu.get_zero_x_value();
        bitwise_ora(cpu, cpu.get_a(), value);
    }

    void ora_absolute(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_value();
        bitwise_ora(cpu, cpu.get_a(), value);
    }

    void ora_absolute_x(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_x_value();
        bitwise_ora(cpu, cpu.get_a(), value);
    }

    void ora_absolute_y(Cpu &cpu) {
        uint8_t value = cpu.get_absolute_y_value();
        bitwise_ora(cpu, cpu.get_a(), value);
    }

    void ora_indirect_x(Cpu &cpu) {
        uint8_t value = cpu.get_indirect_x_value();
        bitwise_ora(cpu, cpu.get_a(), value);
    }

    void ora_indirect_y(Cpu &cpu) {
        uint8_t value = cpu.get_indirect_y_value();
        bitwise_ora(cpu, cpu.get_a(), value);
    }

    void rol(Cpu &cpu, Register<uint8_t> &reg) {
        uint8_t value = reg.get_value();
        bool carry = utils::get_nth_bit(value, 7);

        value <<= 1u;
        value = cpu.get_program_status().is_carry_set() ?
                    utils::set_nth_bit(value, 0) :
                    utils::clear_nth_bit(value, 0);
        reg.set_value(value);

        cpu.get_program_status().set_carry(carry);
        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(value, 7));
    }

    void rol(Cpu &cpu, uint16_t address) {
        uint8_t value = cpu.get_memory().get_u8(address);
        bool carry = utils::get_nth_bit(value, 7);

        value <<= 1u;
        value = cpu.get_program_status().is_carry_set() ?
                utils::set_nth_bit(value, 0) :
                utils::clear_nth_bit(value, 0);

        cpu.get_memory().set_u8(address, value);

        cpu.get_program_status().set_carry(carry);
        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(value, 7));
    }

    void rol_acc(Cpu &cpu) {
        rol(cpu, cpu.get_a());
    }

    void rol_zero(Cpu &cpu) {
        uint16_t address = cpu.get_u8();
        rol(cpu, address);
    }

    void rol_zero_x(Cpu &cpu) {
        auto address = cpu.get_zero_x_address();
        rol(cpu, address);
    }

    void rol_abs(Cpu &cpu) {
        auto address = cpu.get_u16();
        rol(cpu, address);
    }

    void rol_abs_x(Cpu &cpu) {
        auto address = cpu.get_absolute_x_address();
        rol(cpu, address);
    }

    void ror(Cpu &cpu, Register<uint8_t> &reg) {
        uint8_t value = reg.get_value();
        bool carry = utils::get_nth_bit(value, 0);

        value >>= 1u;
        value = cpu.get_program_status().is_carry_set() ?
                utils::set_nth_bit(value, 7) :
                utils::clear_nth_bit(value, 7);
        reg.set_value(value);

        cpu.get_program_status().set_carry(carry);
        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(value, 7));
    }

    void ror(Cpu &cpu, uint16_t address) {
        uint8_t value = cpu.get_memory().get_u8(address);
        bool carry = utils::get_nth_bit(value, 0);

        value >>= 1u;
        value = cpu.get_program_status().is_carry_set() ?
                utils::set_nth_bit(value, 7) :
                utils::clear_nth_bit(value, 7);
        cpu.get_memory().set_u8(address, value);

        cpu.get_program_status().set_carry(carry);
        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(value, 7));
    }

    void ror_acc(Cpu &cpu) {
        ror(cpu, cpu.get_a());
    }

    void ror_zero(Cpu &cpu) {
        uint16_t address = cpu.get_u8();
        ror(cpu, address);
    }

    void ror_zero_x(Cpu &cpu) {
        auto address = cpu.get_zero_x_address();
        ror(cpu, address);
    }

    void ror_abs(Cpu &cpu) {
        auto address = cpu.get_u16();
        ror(cpu, address);
    }

    void ror_abs_x(Cpu &cpu) {
        auto address = cpu.get_absolute_x_address();
        ror(cpu, address);
    }

}
