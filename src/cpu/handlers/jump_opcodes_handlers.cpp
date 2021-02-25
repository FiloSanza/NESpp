#include "jump_opcodes_handlers.h"

namespace nespp::jump_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::JMP_ABS, jmp_absolute);
        handlers.emplace(Opcodes::JMP_IND, jmp_indirect);
        handlers.emplace(Opcodes::JSR, jsr);
        handlers.emplace(Opcodes::RTS, rts);

        return handlers;
    }

    void jmp(Cpu &cpu, uint16_t address) {
        cpu.get_program_counter().set_value(address);
    }

    void jsr(nespp::Cpu &cpu) {
        auto address = cpu.get_u16();
        auto old_pc = cpu.get_program_counter().get_value() - 1;

        cpu.get_stack().push(bits::get_high_u8(old_pc));
        cpu.get_stack().push(bits::get_low_u8(old_pc));

        jmp(cpu, address);
    }

    void rts(nespp::Cpu &cpu) {
        auto low_pc = cpu.get_stack().pop();
        auto high_pc = cpu.get_stack().pop();

        auto pc = bits::merge_u8(low_pc, high_pc) + 1;

        jmp(cpu, pc);
    }

    void jmp_absolute(Cpu &cpu) {
        auto address = cpu.get_u16();
        jmp(cpu, address);
    }

    void jmp_indirect(Cpu &cpu) {
        auto indirect_addr = cpu.get_u16();
        auto address = cpu.get_memory().get_u16_bug(indirect_addr);
        jmp(cpu, address);
    }

}
