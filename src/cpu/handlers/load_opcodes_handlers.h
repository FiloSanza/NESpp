#ifndef NESPP_LOAD_OPCODES_HANDLERS_H
#define NESPP_LOAD_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcodes.h"
#include "../cpu.h"

namespace nespp::load_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void load(Cpu &cpu, Register<uint8_t> &reg, uint8_t value);

    void lda_immediate(Cpu &cpu);
    void lda_zero(Cpu &cpu);
    void lda_zero_x(Cpu &cpu);
    void lda_absolute(Cpu &cpu);
    void lda_absolute_x(Cpu &cpu);
    void lda_absolute_y(Cpu &cpu);
    void lda_indirect_x(Cpu &cpu);
    void lda_indirect_y(Cpu &cpu);

    void ldx_immediate(Cpu &cpu);
    void ldx_zero(Cpu &cpu);
    void ldx_zero_y(Cpu &cpu);
    void ldx_absolute(Cpu &cpu);
    void ldx_absolute_y(Cpu &cpu);

    void ldy_immediate(Cpu &cpu);
    void ldy_zero(Cpu &cpu);
    void ldy_zero_x(Cpu &cpu);
    void ldy_absolute(Cpu &cpu);
    void ldy_absolute_x(Cpu &cpu);

}

#endif //NESPP_LOAD_OPCODES_HANDLERS_H
