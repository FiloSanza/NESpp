#ifndef NESPP_COMPARE_OPCODES_HANDLERS_H
#define NESPP_COMPARE_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcode_handlers.h"

namespace nespp::compare_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void cmp(Cpu &cpu, Register<uint8_t>& reg, uint8_t value);

    void cmp_imm(Cpu &cpu);
    void cmp_zero(Cpu &cpu);
    void cmp_zero_x(Cpu &cpu);
    void cmp_abs(Cpu &cpu);
    void cmp_abs_x(Cpu &cpu);
    void cmp_abs_y(Cpu &cpu);
    void cmp_ind_x(Cpu &cpu);
    void cmp_ind_y(Cpu &cpu);
    void cpx_imm(Cpu &cpu);
    void cpx_zero(Cpu &cpu);
    void cpx_abs(Cpu &cpu);
    void cpy_imm(Cpu &cpu);
    void cpy_zero(Cpu &cpu);
    void cpy_abs(Cpu &cpu);

}

#endif //NESPP_COMPARE_OPCODES_HANDLERS_H
