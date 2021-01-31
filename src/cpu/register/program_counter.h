#ifndef NESPP_PROGRAM_COUNTER_H
#define NESPP_PROGRAM_COUNTER_H

#include "register.h"

namespace nespp {
    class ProgramCounter : public Register<uint16_t> {
        void inc();
        void jump(uint16_t offset);
    };
}

#endif //NESPP_PROGRAM_COUNTER_H
