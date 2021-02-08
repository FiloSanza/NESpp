#ifndef NESPP_SYSTEM_OPCODE_HANDLERS_H
#define NESPP_SYSTEM_OPCODE_HANDLERS_H

#include <map>
#include <functional>
#include "opcode_handlers.h"

namespace nespp::system_opcodes {
    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    void nop(Cpu &cpu);
    void brk(Cpu &cpu);
}


#endif //NESPP_SYSTEM_OPCODE_HANDLERS_H
