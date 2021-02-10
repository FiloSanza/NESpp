#include "jump_opcodes_handlers.h"

namespace nespp::jump_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::JMP_ABS, jmp_absolute);
        handlers.emplace(Opcodes::JMP_IND, jmp_immediate);
        handlers.emplace(Opcodes::JSR, jsr);
        handlers.emplace(Opcodes::RTS, rts);

        return handlers;
    }

    void jmp(Cpu &cpu, uint16_t address) {
        cpu.get_program_counter().set_value(address);
    }

    void jsr(nespp::Cpu &cpu) {
        auto abs_addr = cpu.get_u16();
        auto address = cpu.get_memory().get_u16(abs_addr);
        auto old_pc = cpu.get_program_counter().get_value();

        cpu.get_stack().push(utils::get_high_u8(old_pc));
        cpu.get_stack().push(utils::get_low_u8(old_pc));

        jmp(cpu, address);
    }

    void rts(nespp::Cpu &cpu) {
        auto low_pc = cpu.get_stack().pop();
        auto high_pc = cpu.get_stack().pop();

        auto pc = utils::merge_u8(low_pc, high_pc);

        jmp(cpu, pc);
    }

    void jmp_absolute(Cpu &cpu) {
        auto abs_addr = cpu.get_u16();
        auto address = cpu.get_memory().get_u16(abs_addr);
        jmp(cpu, address);
    }

    void jmp_immediate(Cpu &cpu) {
        auto address = cpu.get_u16();
        jmp(cpu, address);
    }

}
