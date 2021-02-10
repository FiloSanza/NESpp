#ifndef NESPP_JUMP_OPCODES_HANDLERS_H
#define NESPP_JUMP_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcodes.h"
#include "../cpu.h"

namespace nespp::jump_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void jmp(Cpu &cpu, uint16_t address);

    void jmp_absolute(Cpu &cpu);
    void jmp_immediate(Cpu &cpu);
    void jsr(Cpu &cpu);
    void rts(Cpu &cpu);

}

#endif //NESPP_JUMP_OPCODES_HANDLERS_H
