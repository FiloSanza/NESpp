#ifndef NESPP_STORE_OPCODES_HANDLERS_H
#define NESPP_STORE_OPCODES_HANDLERS_H

#include "../register/register.h"
#include "opcodes.h"
#include "../cpu.h"

#include <map>
#include <functional>

namespace nespp::store_opcodes {
    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void store(Cpu &cpu, uint8_t value, uint16_t address);
    void store(Cpu &cpu, Register<uint8_t> &reg, uint16_t address);

    void sta_zero(Cpu &cpu);
    void sta_zero_x(Cpu &cpu);
    void sta_absolute(Cpu &cpu);
    void sta_absolute_x(Cpu &cpu);
    void sta_absolute_y(Cpu &cpu);
    void sta_indirect_x(Cpu &cpu);
    void sta_indirect_y(Cpu &cpu);
    void stx_zero(Cpu &cpu);
    void stx_zero_y(Cpu &cpu);
    void stx_absolute(Cpu &cpu);
    void sty_zero(Cpu &cpu);
    void sty_zero_x(Cpu &cpu);
    void sty_absolute(Cpu &cpu);
}

#endif //NESPP_STORE_OPCODES_HANDLERS_H
