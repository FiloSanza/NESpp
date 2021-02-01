#include "stack_pointer.h"

namespace nespp {
    StackPointer::StackPointer() : Register<uint16_t>("SP") {}

    void StackPointer::inc() {
        value++;
    }

    void StackPointer::dec() {
        value--;
    }
}