#ifndef NESPP_BITWISE_OPCODES_HANDLERS_H
#define NESPP_BITWISE_OPCODES_HANDLERS_H

#include "opcode_handlers.h"

namespace nespp::bitwise_opcodes {
    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void bitwise_and(Cpu &cpu, Register<uint8_t> &a, uint8_t value);
    void and_immediate(Cpu &cpu);
    void and_zero(Cpu &cpu);
    void and_zero_x(Cpu &cpu);
    void and_absolute(Cpu &cpu);
    void and_absolute_x(Cpu &cpu);
    void and_absolute_y(Cpu &cpu);
    void and_indirect_x(Cpu &cpu);
    void and_indirect_y(Cpu &cpu);
    void eor_immediate(Cpu &cpu);

    void bitwise_eor(Cpu &cpu, Register<uint8_t> &a, uint8_t value);
    void eor_zero(Cpu &cpu);
    void eor_zero_x(Cpu &cpu);
    void eor_absolute(Cpu &cpu);
    void eor_absolute_x(Cpu &cpu);
    void eor_absolute_y(Cpu &cpu);
    void eor_indirect_x(Cpu &cpu);
    void eor_indirect_y(Cpu &cpu);
    void ora_immediate(Cpu &cpu);

    void bitwise_ora(Cpu &cpu, Register<uint8_t> &a, uint8_t value);
    void ora_zero(Cpu &cpu);
    void ora_zero_x(Cpu &cpu);
    void ora_absolute(Cpu &cpu);
    void ora_absolute_x(Cpu &cpu);
    void ora_absolute_y(Cpu &cpu);
    void ora_indirect_x(Cpu &cpu);
    void ora_indirect_y(Cpu &cpu);

    void rol(Cpu &cpu, Register<uint8_t> &reg);
    void rol(Cpu &cpu, uint16_t address);

    void rol_accumulator(Cpu &cpu);
    void rol_zero(Cpu &cpu);
    void rol_zero_x(Cpu &cpu);
    void rol_absolute(Cpu &cpu);
    void rol_absolute_x(Cpu &cpu);
    void rol_absolute_y(Cpu &cpu);
    void rol_indirect_x(Cpu &cpu);
    void rol_indirect_y(Cpu &cpu);

    void ror(Cpu &cpu, Register<uint8_t> &reg);
    void ror(Cpu &cpu, uint16_t address);

    void ror_accumulator(Cpu &cpu);
    void ror_zero(Cpu &cpu);
    void ror_zero_x(Cpu &cpu);
    void ror_absolute(Cpu &cpu);
    void ror_absolute_x(Cpu &cpu);

    void bit(Cpu &cpu, uint8_t value);

    void bit_zero(Cpu &cpu);
    void bit_absolute(Cpu &cpu);

    void asl(Cpu &cpu, Register<uint8_t> &reg);
    void asl(Cpu &cpu, uint16_t address);

    void asl_accumulator(Cpu &cpu);
    void asl_zero(Cpu &cpu);
    void asl_zero_x(Cpu &cpu);
    void asl_absolute(Cpu &cpu);
    void asl_absolute_x(Cpu &cpu);

    void lsr(Cpu &cpu, Register<uint8_t> &reg);
    void lsr(Cpu &cpu, uint16_t address);

    void lsr_accumulator(Cpu &cpu);
    void lsr_zero(Cpu &cpu);
    void lsr_zero_x(Cpu &cpu);
    void lsr_absolute(Cpu &cpu);
    void lsr_absolute_x(Cpu &cpu);

}

#endif //NESPP_BITWISE_OPCODES_HANDLERS_H
