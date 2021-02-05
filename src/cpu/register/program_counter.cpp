#include "program_counter.h"

namespace nespp {

    ProgramCounter::ProgramCounter() : Register<uint16_t>("PC") {

    }

    void ProgramCounter::inc() {
        value++;
    }

    void ProgramCounter::jump(uint16_t offset) {
        value += offset;
    }

}