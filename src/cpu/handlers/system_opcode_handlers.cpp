#include "system_opcode_handlers.h"

namespace nespp::system_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers =  std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::BRK, brk);
        handlers.emplace(Opcodes::RTI, rti);
        handlers.emplace(Opcodes::NOP, nop);

        return handlers;
    }

    void nop(Cpu &cpu) { }

    void brk(Cpu &cpu) {
        uint16_t pc = cpu.get_program_status().get_value().to_ulong();
        auto &ps = cpu.get_program_status();

        cpu.get_stack().push(utils::get_high_u8(pc));
        cpu.get_stack().push(utils::get_low_u8(pc));

        ps.set_break(true);
        cpu.get_stack().push(ps.get_value().to_ulong());

        uint8_t low = cpu.get_memory().get_u8(0xfffe);
        uint8_t high = cpu.get_memory().get_u8(0xffff);

        uint16_t new_pc = utils::merge_u8(low, high);
        cpu.get_program_counter().set_value(new_pc);
    }

    void rti(Cpu &cpu) {
        auto ps = cpu.get_stack().pop();
        cpu.get_program_status().set_value(ps);

        auto pc_low = cpu.get_stack().pop();
        auto pc_high = cpu.get_stack().pop();

        cpu.get_program_counter().set_value(utils::merge_u8(pc_low, pc_high));
    }
}