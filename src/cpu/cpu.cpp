#include "cpu.h"

namespace nespp {

    Cpu::Cpu(std::vector<uint8_t> &rom, uint16_t load_at) {
        pc = std::make_unique<ProgramCounter>();
        ps = std::make_unique<ProgramStatus>();
        sp = std::make_unique<StackPointer>();
        a = std::make_unique<Register<uint8_t>>("A");
        x = std::make_unique<Register<uint8_t>>("X");
        y = std::make_unique<Register<uint8_t>>("Y");
        memory = std::make_unique<Memory>();
        stack = std::make_unique<Stack>(*sp, *memory);

        memory->load(rom, load_at);

        cycle_count = 0;
        rom_size = rom.size();
        rom_address = load_at;
        pc->set_value(rom_address);

        ps->set_value(0x24);

    }

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
        uint16_t value = high << 8u | low;

        return value;
    }

    uint8_t Cpu::get_u8() {
        uint8_t value = memory->get_u8(pc->get_value());
        pc->inc();
        return value;
    }

    uint16_t Cpu::get_zero_x_address() {
        uint16_t address = get_u8() + x->get_value();
        address &= 0xffu;
        return address;
    }

    uint16_t Cpu::get_zero_y_address() {
        uint16_t address = get_u8() + y->get_value();
        address &= 0xffu;
        return address;
    }

    uint16_t Cpu::get_absolute_x_address() {
        return get_u16() + x->get_value();
    }

    uint16_t Cpu::get_absolute_y_address() {
        return get_u16() + y->get_value();
    }

    uint16_t Cpu::get_indirect_x_address() {
        uint16_t indirect_address = get_u8() + x->get_value();
        indirect_address &= 0xffu;
        uint16_t address = memory->get_u16_bug(indirect_address);

        return address;
    }

    uint16_t Cpu::get_indirect_y_address() {
        uint16_t indirect_address = get_u8();
        uint16_t address = memory->get_u16_bug(indirect_address) + y->get_value();
        return address;
    }

    uint8_t Cpu::get_zero_value() {
        auto address = get_u8();
        return memory->get_u8(address);
    }

    uint8_t Cpu::get_zero_x_value() {
        auto address = get_zero_x_address();
        return memory->get_u8(address);
    }

    uint8_t Cpu::get_zero_y_value() {
        auto address = get_zero_y_address();
        return memory->get_u8(address);
    }

    uint8_t Cpu::get_absolute_value() {
        auto address = get_u16();
        return memory->get_u8(address);
    }

    uint8_t Cpu::get_absolute_x_value() {
        auto address = get_absolute_x_address();
        return memory->get_u8(address);
    }

    uint8_t Cpu::get_absolute_y_value() {
        auto address = get_absolute_y_address();
        return memory->get_u8(address);
    }

    uint8_t Cpu::get_indirect_x_value() {
        auto address = get_indirect_x_address();
        return memory->get_u8(address);
    }

    uint8_t Cpu::get_indirect_y_value() {
        auto address = get_indirect_y_address();
        return memory->get_u8(address);
    }

    std::string Cpu::dump() {
        std::stringstream stream;

        stream << a->get_name() << ":" << bits::int_to_hex(a->get_value(), 2).substr(2) << " ";
        stream << x->get_name() << ":" << bits::int_to_hex(x->get_value(), 2).substr(2) << " ";
        stream << y->get_name() << ":" << bits::int_to_hex(y->get_value(), 2).substr(2) << " ";
        stream << "P:" << bits::int_to_hex(ps->get_value().to_ulong(), 2).substr(2) << " ";
        stream << sp->get_name() << ":" << bits::int_to_hex(sp->get_value(), 2).substr(2) << " ";

        return stream.str();
    }

    bool Cpu::is_end_of_program() {
        return false;
    }

}