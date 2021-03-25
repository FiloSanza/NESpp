#ifndef NESPP_BRANCH_OPCODES_HANDLERS_H
#define NESPP_BRANCH_OPCODES_HANDLERS_H

#include <map>
#include <functional>
#include "opcodes.h"
#include "../cpu.h"

namespace nespp::branch_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void branch(Cpu &cpu, uint16_t offset);

    void bcc(Cpu &cpu);
    void bcs(Cpu &cpu);
    void beq(Cpu &cpu);
    void bne(Cpu &cpu);
    void bmi(Cpu &cpu);
    void bpl(Cpu &cpu);
    void bvc(Cpu &cpu);
    void bvs(Cpu &cpu);

}

#endif //NESPP_BRANCH_OPCODES_HANDLERS_H
