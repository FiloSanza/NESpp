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

    void bcc(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(!cpu.get_program_status().is_carry_set())
            cpu.get_program_counter().jump(offset);
    }

    void bcs(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(cpu.get_program_status().is_carry_set())
            cpu.get_program_counter().jump(offset);
    }

    void beq(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(cpu.get_program_status().is_zero_set())
            cpu.get_program_counter().jump(offset);
    }

    void bne(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(!cpu.get_program_status().is_zero_set())
            cpu.get_program_counter().jump(offset);
    }

    void bmi(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(cpu.get_program_status().is_negative_set())
            cpu.get_program_counter().jump(offset);
    }

    void bpl(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(!cpu.get_program_status().is_negative_set())
            cpu.get_program_counter().jump(offset);
    }

    void bvc(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(!cpu.get_program_status().is_overflow_set())
            cpu.get_program_counter().jump(offset);
    }

    void bvs(Cpu &cpu) {
        auto offset = cpu.get_u8();
        if(cpu.get_program_status().is_overflow_set())
            cpu.get_program_counter().jump(offset);
    }
}