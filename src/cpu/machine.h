#ifndef NESPP_MACHINE_H
#define NESPP_MACHINE_H

#include <memory>
#include <functional>
#include <stdexcept>
#include "cpu.h"
#include "handlers/opcode_handlers.h"

namespace nespp {

    class Machine {
    public:
        Machine(std::vector<uint8_t> &data, uint16_t load_at);

        Cpu &get_cpu();

        void execute();

        void add_before_exec_callback(const std::function<void(Machine &, uint8_t)>& func);
        void add_after_exec_callback(const std::function<void(Machine &, uint8_t)>& func);
        void reset_callbacks();

    private:
        std::vector<std::function<void(Machine &, uint8_t)>> before_exec_callbacks;
        std::vector<std::function<void(Machine &, uint8_t)>> after_exec_callbacks;

        std::unique_ptr<Cpu> cpu;
        OpcodeHandlers handlers;
    };

}

#endif //NESPP_MACHINE_H
