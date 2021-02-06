#include "stack_pointer.h"

namespace nespp {
    StackPointer::StackPointer() : Register<uint8_t>("SP") {

    }

    void StackPointer::inc() {
        value++;
    }

    void StackPointer::dec() {
        value--;
    }

}