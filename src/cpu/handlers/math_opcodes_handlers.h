#ifndef NESPP_MATH_OPCODES_HANDLERS_H
#define NESPP_MATH_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcode_handlers.h"

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

}


#endif //NESPP_MATH_OPCODES_HANDLERS_H
