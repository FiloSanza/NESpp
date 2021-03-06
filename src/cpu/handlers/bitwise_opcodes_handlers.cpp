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

        handlers.emplace(Opcodes::ROL_ACC, rol_accumulator);
        handlers.emplace(Opcodes::ROL_ZERO, rol_zero);
        handlers.emplace(Opcodes::ROL_ZERO_X, rol_zero_x);
        handlers.emplace(Opcodes::ROL_ABS, rol_absolute);
        handlers.emplace(Opcodes::ROL_ABS_X, rol_absolute_x);

        handlers.emplace(Opcodes::ROR_ACC, ror_accumulator);
        handlers.emplace(Opcodes::ROR_ZERO, ror_zero);
        handlers.emplace(Opcodes::ROR_ZERO_X, ror_zero_x);
        handlers.emplace(Opcodes::ROR_ABS, ror_absolute);
        handlers.emplace(Opcodes::ROR_ABS_X, ror_absolute_x);

        handlers.emplace(Opcodes::BIT_ABS, bit_absolute);
        handlers.emplace(Opcodes::BIT_ZERO, bit_zero);

        handlers.emplace(Opcodes::ASL_ACC, asl_accumulator);
        handlers.emplace(Opcodes::ASL_ZERO, asl_zero);
        handlers.emplace(Opcodes::ASL_ZERO_X, asl_zero_x);
        handlers.emplace(Opcodes::ASL_ABS, asl_absolute);
        handlers.emplace(Opcodes::ASL_ABS_X, asl_absolute_x);

        handlers.emplace(Opcodes::LSR_ACC, lsr_accumulator);
        handlers.emplace(Opcodes::LSR_ZERO, lsr_zero);
        handlers.emplace(Opcodes::LSR_ZERO_X, lsr_zero_x);
        handlers.emplace(Opcodes::LSR_ABS, lsr_absolute);
        handlers.emplace(Opcodes::LSR_ABS_X, lsr_absolute_x);

        return handlers;
    }

    void bitwise_and(Cpu &cpu, Register<uint8_t> &a, uint8_t value) {
        uint8_t result = a.get_value() & value;
        a.set_value(result);

        cpu.get_program_status().set_zero(result == 0);
        cpu.get_program_status().set_negative(bits::get_nth_bit(result, 7));
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
        cpu.get_program_status().set_negative(bits::get_nth_bit(result, 7));
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
        cpu.get_program_status().set_negative(bits::get_nth_bit(result, 7));
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
        bool carry = bits::get_nth_bit(value, 7);

        value <<= 1u;
        value = cpu.get_program_status().is_carry_set() ?
                bits::set_nth_bit(value, 0) :
                bits::clear_nth_bit(value, 0);
        reg.set_value(value);

        cpu.get_program_status().set_carry(carry);
        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(bits::get_nth_bit(value, 7));
    }

    void rol(Cpu &cpu, uint16_t address) {
        uint8_t value = cpu.get_memory().get_u8(address);
        bool carry = bits::get_nth_bit(value, 7);

        value <<= 1u;
        value = cpu.get_program_status().is_carry_set() ?
                bits::set_nth_bit(value, 0) :
                bits::clear_nth_bit(value, 0);

        cpu.get_memory().set_u8(address, value);

        cpu.get_program_status().set_carry(carry);
        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(bits::get_nth_bit(value, 7));
    }

    void rol_accumulator(Cpu &cpu) {
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

    void rol_absolute(Cpu &cpu) {
        auto address = cpu.get_u16();
        rol(cpu, address);
    }

    void rol_absolute_x(Cpu &cpu) {
        auto address = cpu.get_absolute_x_address();
        rol(cpu, address);
    }

    void rol_absolute_y(Cpu &cpu) {
        auto address = cpu.get_absolute_y_address();
        rol(cpu, address);
    }

    void rol_indirect_x(Cpu &cpu) {
        auto address = cpu.get_indirect_x_address();
        rol(cpu, address);
    }

    void rol_indirect_y(Cpu &cpu) {
        auto address = cpu.get_indirect_y_address();
        rol(cpu, address);
    }

    void ror(Cpu &cpu, Register<uint8_t> &reg) {
        uint8_t value = reg.get_value();
        bool carry = bits::get_nth_bit(value, 0);

        value >>= 1u;
        value = cpu.get_program_status().is_carry_set() ?
                bits::set_nth_bit(value, 7) :
                bits::clear_nth_bit(value, 7);
        reg.set_value(value);

        cpu.get_program_status().set_carry(carry);
        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(bits::get_nth_bit(value, 7));
    }

    void ror(Cpu &cpu, uint16_t address) {
        uint8_t value = cpu.get_memory().get_u8(address);
        bool carry = bits::get_nth_bit(value, 0);

        value >>= 1u;
        value = cpu.get_program_status().is_carry_set() ?
                bits::set_nth_bit(value, 7) :
                bits::clear_nth_bit(value, 7);
        cpu.get_memory().set_u8(address, value);

        cpu.get_program_status().set_carry(carry);
        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(bits::get_nth_bit(value, 7));
    }

    void ror_accumulator(Cpu &cpu) {
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

    void ror_absolute(Cpu &cpu) {
        auto address = cpu.get_u16();
        ror(cpu, address);
    }

    void ror_absolute_x(Cpu &cpu) {
        auto address = cpu.get_absolute_x_address();
        ror(cpu, address);
    }

    void bit(Cpu &cpu, uint8_t value) {
        auto result = value & cpu.get_a().get_value();
        auto &ps = cpu.get_program_status();

        ps.set_zero(result == 0);
        ps.set_overflow(bits::get_nth_bit(value, 6));
        ps.set_negative(bits::get_nth_bit(value, 7));
    }

    void bit_absolute(Cpu &cpu) {
        auto value = cpu.get_absolute_value();
        bit(cpu, value);
    }

    void bit_zero(Cpu &cpu) {
        auto value = cpu.get_zero_value();
        bit(cpu, value);
    }

    void asl(Cpu &cpu, Register<uint8_t> &reg) {
        auto &ps = cpu.get_program_status();
        uint8_t value = reg.get_value();

        ps.set_carry(bits::get_nth_bit(value, 7));
        ps.set_negative(bits::get_nth_bit(value, 6));

        value <<= 1;

        ps.set_zero(value == 0);
        reg.set_value(value);
    }

    void asl(Cpu &cpu, uint16_t address) {
        auto &ps = cpu.get_program_status();
        uint8_t value = cpu.get_memory().get_u8(address);

        ps.set_carry(bits::get_nth_bit(value, 7));
        ps.set_negative(bits::get_nth_bit(value, 6));

        value <<= 1;

        ps.set_zero(value == 0);
        cpu.get_memory().set_u8(address, value);
    }

    void asl_accumulator(Cpu &cpu) {
        asl(cpu, cpu.get_a());
    }

    void asl_zero(Cpu &cpu) {
        auto address = cpu.get_u8();
        asl(cpu, address);
    }

    void asl_zero_x(Cpu &cpu) {
        auto address = cpu.get_zero_x_address();
        asl(cpu, address);
    }

    void asl_absolute(Cpu &cpu) {
        auto address = cpu.get_u16();
        asl(cpu, address);
    }

    void asl_absolute_x(Cpu &cpu) {
        auto address = cpu.get_absolute_x_address();
        asl(cpu, address);
    }

    void lsr(Cpu &cpu, Register<uint8_t> &reg) {
        auto value = reg.get_value();
        auto &ps = cpu.get_program_status();

        ps.set_carry(bits::get_nth_bit(value, 0));
        ps.set_zero(value == 0x01);

        value >>= 1u;
        reg.set_value(value);

        ps.set_negative(bits::get_nth_bit(value, 7));
    }

    void lsr(Cpu &cpu, uint16_t address) {
        auto value = cpu.get_memory().get_u8(address);
        auto &ps = cpu.get_program_status();

        ps.set_carry(bits::get_nth_bit(value, 0));
        ps.set_zero(value == 0x01);

        value >>= 1u;
        cpu.get_memory().set_u8(address, value);

        ps.set_negative(bits::get_nth_bit(value, 7));
    }

    void lsr_accumulator(Cpu &cpu) {
        lsr(cpu, cpu.get_a());
    }

    void lsr_zero(Cpu &cpu) {
        auto address = cpu.get_u8();
        lsr(cpu, address);
    }

    void lsr_zero_x(Cpu &cpu) {
        auto address = cpu.get_zero_x_address();
        lsr(cpu, address);
    }

    void lsr_absolute(Cpu &cpu) {
        auto address = cpu.get_u16();
        lsr(cpu, address);
    }

    void lsr_absolute_x(Cpu &cpu) {
        auto address = cpu.get_absolute_x_address();
        lsr(cpu, address);
    }

}
