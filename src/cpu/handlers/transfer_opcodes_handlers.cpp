#include "transfer_opcodes_handlers.h"

namespace nespp::transfer_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::TAX, tax);
        handlers.emplace(Opcodes::TAY, tay);
        handlers.emplace(Opcodes::TSX, tsx);
        handlers.emplace(Opcodes::TXA, txa);
        handlers.emplace(Opcodes::TXS, txs);
        handlers.emplace(Opcodes::TYA, tya);

        return handlers;
    }

    template <typename T, typename U>
    void transfer(Cpu& cpu, Register<T> &source, Register<U> &dest, bool update_flags) {
        auto value = source.get_value();
        dest.set_value(value);

        if(!update_flags) return;

        auto ps = cpu.get_program_status();
        ps.set_negative(utils::get_nth_bit(value, 7));
        ps.set_zero(value == 0);
    }

    void tax(Cpu &cpu) {
        transfer(cpu, cpu.get_x(), cpu.get_a(), true);
    }

    void tay(nespp::Cpu &cpu) {
        transfer(cpu, cpu.get_y(), cpu.get_a(), true);
    }

    void tsx(nespp::Cpu &cpu) {
        transfer(cpu, cpu.get_x(), cpu.get_stack_pointer(), true);
    }

    void txa(nespp::Cpu &cpu) {
        transfer(cpu, cpu.get_a(), cpu.get_x(), true);
    }

    void txs(nespp::Cpu &cpu) {
        transfer(cpu, cpu.get_stack_pointer(), cpu.get_x(), false);
    }

    void tya(Cpu &cpu) {
        transfer(cpu, cpu.get_y(), cpu.get_a(), true);
    }
}