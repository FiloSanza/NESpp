#ifndef NESPP_MATH_OPCODES_HANDLERS_H
#define NESPP_MATH_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcodes.h"
#include "../cpu.h"

namespace nespp::math_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void dec_memory(Cpu &cpu, uint16_t address);

    void dec_zero(Cpu &cpu);
    void dec_zero_x(Cpu &cpu);
    void dec_abs(Cpu &cpu);
    void dec_abs_x(Cpu &cpu);

    void dec_register(Cpu &cpu, Register<uint8_t> &reg);

    void dex(Cpu &cpu);
    void dey(Cpu &cpu);

    void inc_memory(Cpu &cpu, uint16_t address);

    void inc_zero(Cpu &cpu);
    void inc_zero_x(Cpu &cpu);
    void inc_abs(Cpu &cpu);
    void inc_abs_x(Cpu &cpu);

    void inc_register(Cpu &cpu, Register<uint8_t> &reg);

    void inx(Cpu &cpu);
    void iny(Cpu &cpu);

    void adc(Cpu &cpu, Register<uint8_t> &reg, uint16_t value);

    void adc_immediate(Cpu &cpu);
    void adc_zero(Cpu &cpu);
    void adc_zero_x(Cpu &cpu);
    void adc_absolute(Cpu &cpu);
    void adc_absolute_x(Cpu &cpu);
    void adc_absolute_y(Cpu &cpu);
    void adc_indirect_x(Cpu &cpu);
    void adc_indirect_y(Cpu &cpu);

    void sbc(Cpu &cpu, Register<uint8_t> &reg, uint16_t value);

    void sbc_immediate(Cpu &cpu);
    void sbc_zero(Cpu &cpu);
    void sbc_zero_x(Cpu &cpu);
    void sbc_absolute(Cpu &cpu);
    void sbc_absolute_x(Cpu &cpu);
    void sbc_absolute_y(Cpu &cpu);
    void sbc_indirect_x(Cpu &cpu);
    void sbc_indirect_y(Cpu &cpu);
}


#endif //NESPP_MATH_OPCODES_HANDLERS_H
