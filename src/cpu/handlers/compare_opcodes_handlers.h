#ifndef NESPP_COMPARE_OPCODES_HANDLERS_H
#define NESPP_COMPARE_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcodes.h"
#include "../cpu.h"

namespace nespp::compare_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void cmp(Cpu &cpu, Register<uint8_t>& reg, uint8_t value);

    void cmp_imm(Cpu &cpu);
    void cmp_zero(Cpu &cpu);
    void cmp_zero_x(Cpu &cpu);
    void cmp_absolute(Cpu &cpu);
    void cmp_absolute_x(Cpu &cpu);
    void cmp_absolute_y(Cpu &cpu);
    void cmp_indirect_x(Cpu &cpu);
    void cmp_indirect_y(Cpu &cpu);
    void cpx_immediate(Cpu &cpu);
    void cpx_zero(Cpu &cpu);
    void cpx_absolute(Cpu &cpu);
    void cpy_immediate(Cpu &cpu);
    void cpy_zero(Cpu &cpu);
    void cpy_absolute(Cpu &cpu);

}

#endif //NESPP_COMPARE_OPCODES_HANDLERS_H
