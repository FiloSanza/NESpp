#ifndef NESPP_CPU_H
#define NESPP_CPU_H

#include <memory>
#include "memory/memory.h"
#include "memory/stack.h"
#include "register/stack_pointer.h"
#include "register/register.h"
#include "register/program_counter.h"
#include "register/program_status.h"

namespace nespp {
    constexpr uint16_t PROGRAM_COUNTER_START = 0x600;

    class Cpu {
    public:
        Cpu() = delete;
        Cpu(std::vector<uint8_t>& rom, uint16_t load_at);

        uint8_t get_u8();
        uint16_t get_u16();

        [[nodiscard]] uint64_t get_cycle_count() const;
        void inc_cycle_count(uint64_t value);

        ProgramCounter& get_program_counter();
        ProgramStatus& get_program_status();
        StackPointer& get_stack_pointer();
        Register<uint8_t>& get_a();
        Register<uint8_t>& get_x();
        Register<uint8_t>& get_y();
        Memory& get_memory();
        Stack& get_stack();

    private:
        std::unique_ptr<Memory> memory;
        std::unique_ptr<Stack> stack;
        std::unique_ptr<ProgramCounter> pc;
        std::unique_ptr<ProgramStatus> ps;
        std::unique_ptr<StackPointer> sp;
        std::unique_ptr<Register<uint8_t>> a;
        std::unique_ptr<Register<uint8_t>> x;
        std::unique_ptr<Register<uint8_t>> y;

        uint64_t cycle_count;
        uint16_t rom_size;
        uint16_t rom_address;
    };
}

#endif //NESPP_CPU_H
