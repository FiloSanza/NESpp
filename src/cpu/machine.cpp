#include "machine.h"

namespace nespp {

    Machine::Machine(std::vector<uint8_t> &data, uint16_t load_at) {
        cpu = std::make_unique<Cpu>(data, load_at);
    }

    //Execute the next instruction
    //TODO: Add accurate cycle count
    void Machine::execute() {
        auto opcode = cpu->get_u8();
        handlers.handle_opcode(*cpu, opcode);
    }

    Cpu &Machine::get_cpu() {
        return *cpu;
    }

}