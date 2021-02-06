#include "flag_opcodes_handlers.h"

namespace nespp::flags_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::SEC, sec);
        handlers.emplace(Opcodes::SED, sed);
        handlers.emplace(Opcodes::SEI, sei);
        handlers.emplace(Opcodes::CLC, clc);
        handlers.emplace(Opcodes::CLD, cld);
        handlers.emplace(Opcodes::CLI, cli);
        handlers.emplace(Opcodes::CLV, clv);

        return handlers;
    }

    void sec(Cpu &cpu) {
        cpu.get_program_status().set_carry(true);
    }

    void sed(Cpu &cpu) {
        cpu.get_program_status().set_decimal_mode(true);
    }

    void sei(Cpu &cpu) {
        cpu.get_program_status().set_interrupt(true);
    }

    void clc(Cpu &cpu) {
        cpu.get_program_status().set_carry(false);
    }

    void cld(Cpu &cpu) {
        cpu.get_program_status().set_decimal_mode(false);
    }

    void cli(Cpu &cpu) {
        cpu.get_program_status().set_interrupt(false);
    }

    void clv(Cpu &cpu) {
        cpu.get_program_status().set_overflow(false);
    }
}