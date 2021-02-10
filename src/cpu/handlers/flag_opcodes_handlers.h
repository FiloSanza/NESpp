#ifndef NESPP_FLAG_OPCODES_HANDLERS_H
#define NESPP_FLAG_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcodes.h"
#include "../cpu.h"

namespace nespp::flags_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void sec(Cpu &cpu);
    void sed(Cpu &cpu);
    void sei(Cpu &cpu);
    void clc(Cpu &cpu);
    void cld(Cpu &cpu);
    void cli(Cpu &cpu);
    void clv(Cpu &cpu);

}

#endif //NESPP_FLAG_OPCODES_HANDLERS_H
