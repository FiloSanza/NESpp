#include "program_counter.h"

namespace nespp {

    void ProgramCounter::inc() {
        value++;
    }

    void ProgramCounter::jump(uint16_t offset) {
        value += offset;
    }

}