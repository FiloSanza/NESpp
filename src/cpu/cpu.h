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
        Cpu();

    private:
        std::unique_ptr<Memory> memory;
        std::unique_ptr<Stack> stack;
        std::unique_ptr<ProgramCounter> pc;
        std::unique_ptr<ProgramStatus> ps;
        std::unique_ptr<Register<uint8_t>> a;
        std::unique_ptr<Register<uint8_t>> x;
        std::unique_ptr<Register<uint8_t>> y;
        long long cycle_count;
    };
}

#endif //NESPP_CPU_H
