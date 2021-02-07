#include "stack_opcodes_handlers.h"

namespace nespp::stack_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers =  std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::PHA, pha);
        handlers.emplace(Opcodes::PHP, php);
        handlers.emplace(Opcodes::PLA, pla);
        handlers.emplace(Opcodes::PLP, plp);

        return handlers;
    }

    void pha(Cpu &cpu) {
        auto value = cpu.get_a().get_value();
        cpu.get_stack().push(value);
    }

    void php(Cpu &cpu) {
        auto value = (uint8_t)cpu.get_program_status().get_value().to_ulong();
        cpu.get_stack().push(value);
    }

    void pla(Cpu &cpu) {
        auto value = cpu.get_stack().pop();
        cpu.get_a().set_value(value);

        cpu.get_program_status().set_zero(value == 0);
        cpu.get_program_status().set_negative(utils::get_nth_bit(value, 7));
    }

    void plp(Cpu &cpu) {
        auto value = cpu.get_stack().pop();
        cpu.get_program_status().set_value(value);
    }
}