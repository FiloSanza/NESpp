#include "machine.h"

namespace nespp {

    Machine::Machine(std::vector<uint8_t> &data, uint16_t load_at) {
        cpu = std::make_unique<Cpu>(data, load_at);
    }

    //Execute the next instruction
    //TODO: Add accurate cycle count
    void Machine::execute() {
        if(cpu->is_end_of_program()) {
            throw std::runtime_error("End of ROM reached");
        }

        auto opcode = cpu->get_u8();

        for(auto &f : before_exec_callbacks) {
            f(*this, opcode);
        }

        handlers.handle_opcode(*cpu, opcode);

        for(auto &f : after_exec_callbacks)
            f(*this, opcode);
    }

    Cpu &Machine::get_cpu() {
        return *cpu;
    }

    void Machine::add_before_exec_callback(std::function<void(Machine &, uint8_t)> func) {
        before_exec_callbacks.push_back(func);
    }

    void Machine::add_after_exec_callback(std::function<void(Machine &, uint8_t)> func) {
        after_exec_callbacks.push_back(func);
    }

    void Machine::reset_callbacks() {
        before_exec_callbacks.clear();
        after_exec_callbacks.clear();
    }

}