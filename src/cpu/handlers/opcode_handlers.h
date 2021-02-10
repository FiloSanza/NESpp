#ifndef NESPP_OPCODE_HANDLERS_H
#define NESPP_OPCODE_HANDLERS_H

#include "../cpu.h"
#include "transfer_opcodes_handlers.h"
#include "store_opcodes_handlers.h"
#include "flag_opcodes_handlers.h"
#include "bitwise_opcodes_handlers.h"
#include "branch_opcodes_handlers.h"
#include "stack_opcodes_handlers.h"
#include "compare_opcodes_handlers.h"
#include "math_opcodes_handlers.h"
#include "jump_opcodes_handlers.h"
#include "opcodes.h"
#include <map>
#include <functional>
#include <stdexcept>

namespace nespp {

    class OpcodeHandlers {
    public:
        OpcodeHandlers();
        void handle_opcode(Cpu &cpu, uint8_t opcode);

    private:
        std::map<uint8_t, std::function<void(Cpu &)>> handlers;
    };

}

#endif //NESPP_OPCODE_HANDLERS_H
