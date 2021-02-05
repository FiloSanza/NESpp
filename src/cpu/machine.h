#ifndef NESPP_MACHINE_H
#define NESPP_MACHINE_H

#include <memory>
#include "cpu.h"
#include "handlers/opcode_handlers.h"

namespace nespp {

    class Machine {
    public:
        Machine(std::vector<uint8_t> &data, uint16_t load_at);

        Cpu &get_cpu();

        void execute();

    private:
        std::unique_ptr<Cpu> cpu;
        OpcodeHandlers handlers;
    };

}

#endif //NESPP_MACHINE_H
