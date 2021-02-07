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
}

#endif //NESPP_BITWISE_OPCODES_HANDLERS_H
