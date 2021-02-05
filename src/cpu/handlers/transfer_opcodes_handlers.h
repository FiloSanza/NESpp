#ifndef NESPP_TRANSFER_OPCODES_HANDLERS_H
#define NESPP_TRANSFER_OPCODES_HANDLERS_H

#include "../../utils/bits.h"
#include "../register/register.h"
#include "opcode_handlers.h"

#include <map>
#include <functional>

namespace nespp::transfer_opcodes {
    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers();

    template <typename T, typename U>
    void transfer(Cpu& cpu, Register<T> &source, Register<U> &dest, bool update_flags);

    void tax(Cpu& cpu);
    void tay(Cpu& cpu);
    void tsx(Cpu& cpu);
    void txa(Cpu& cpu);
    void txs(Cpu& cpu);
    void tya(Cpu& cpu);
}

#endif //NESPP_TRANSFER_OPCODES_HANDLERS_H
