#ifndef NESPP_STACK_OPCODES_HANDLERS_H
#define NESPP_STACK_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcodes.h"
#include "../cpu.h"

namespace nespp::stack_opcodes {
    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void pha(Cpu &cpu);
    void php(Cpu &cpu);
    void pla(Cpu &cpu);
    void plp(Cpu &cpu);
}

#endif //NESPP_STACK_OPCODES_HANDLERS_H
