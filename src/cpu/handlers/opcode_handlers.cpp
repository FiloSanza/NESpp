#include "opcode_handlers.h"

namespace nespp {

    OpcodeHandlers::OpcodeHandlers() {
        handlers.merge(transfer_opcodes::get_handlers());
        handlers.merge(store_opcodes::get_handlers());
        handlers.merge(flags_opcodes::get_handlers());
        handlers.merge(bitwise_opcodes::get_handlers());
        handlers.merge(branch_opcodes::get_handlers());
        handlers.merge(stack_opcodes::get_handlers());
        handlers.merge(compare_opcodes::get_handlers());
        handlers.merge(math_opcodes::get_handlers());
        handlers.merge(jump_opcodes::get_handlers());
        handlers.merge(load_opcodes::get_handlers());
    }

    void OpcodeHandlers::handle_opcode(Cpu &cpu, uint8_t opcode) {
        auto handler = handlers.find(opcode);

        if(handler == handlers.end())
            throw std::domain_error("Opcode " + std::to_string(opcode) + " handler not found.");

        handler->second(cpu);
    }

}


