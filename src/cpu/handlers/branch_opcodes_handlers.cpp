#include "branch_opcodes_handlers.h"

namespace nespp::branch_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::BCC, bcc);
        handlers.emplace(Opcodes::BCS, bcs);
        handlers.emplace(Opcodes::BEQ, beq);
        handlers.emplace(Opcodes::BNE, bne);
        handlers.emplace(Opcodes::BMI, bmi);
        handlers.emplace(Opcodes::BPL, bpl);
        handlers.emplace(Opcodes::BVC, bvc);
        handlers.emplace(Opcodes::BVS, bvs);

        return handlers;
    }

    void branch(Cpu &cpu, uint16_t offset) {
        auto pc = cpu.get_program_counter().get_value();

        cpu.inc_cycle_count(1);
        if(Memory::cross_page_boundary(pc, pc + offset))
            cpu.inc_cycle_count(1);

        cpu.get_program_counter().jump(offset);
    }

    void bcc(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(!cpu.get_program_status().is_carry_set())
            branch(cpu, offset);
    }

    void bcs(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(cpu.get_program_status().is_carry_set())
            branch(cpu, offset);
    }

    void beq(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(cpu.get_program_status().is_zero_set())
            branch(cpu, offset);
    }

    void bne(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(!cpu.get_program_status().is_zero_set())
            branch(cpu, offset);
    }

    void bmi(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(cpu.get_program_status().is_negative_set())
            branch(cpu, offset);
    }

    void bpl(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(!cpu.get_program_status().is_negative_set())
            branch(cpu, offset);
    }

    void bvc(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(!cpu.get_program_status().is_overflow_set())
            branch(cpu, offset);
    }

    void bvs(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(cpu.get_program_status().is_overflow_set())
            branch(cpu, offset);
    }
}