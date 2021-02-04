#include "cpu.h"

namespace nespp {

    uint64_t Cpu::get_cycle_count() const {
        return cycle_count;
    }

    void Cpu::inc_cycle_count(uint64_t value) {
        cycle_count += value;
    }

    ProgramCounter &Cpu::get_program_counter() {
        return *pc;
    }

    ProgramStatus &Cpu::get_program_status() {
        return *ps;
    }

    StackPointer &Cpu::get_stack_pointer() {
        return *sp;
    }

    Register<uint8_t> &Cpu::get_a() {
        return *a;
    }

    Register<uint8_t> &Cpu::get_x() {
        return *x;
    }

    Register<uint8_t> &Cpu::get_y() {
        return *y;
    }

    Memory &Cpu::get_memory() {
        return *memory;
    }

    Stack &Cpu::get_stack() {
        return *stack;
    }

    uint16_t Cpu::get_u16() {
        //uint16_t casts to avoid overflows
        auto low = (uint16_t)get_u8();
        auto high = (uint16_t)get_u8();
        uint16_t value = high << 8 | low;

        return value;
    }

    uint8_t Cpu::get_u8() {
        uint8_t value = memory->get_u8(pc->get_value());
        pc->inc();
        return value;
    }

}