#include "stack.h"

namespace nespp {

    Stack::Stack(StackPointer& sp, Memory& memory) : sp(sp), memory(memory) {
        sp.set_value(STACK_POINTER_START);
    }

    void Stack::push(uint8_t value) {
        memory.set_u8_from_page(STACK_PAGE, sp.get_value(), value);
        sp.dec();                                       //the stack grows towards the low addresses
    }

    uint8_t Stack::pop() {
        uint8_t value = memory.get_u8_from_page(STACK_PAGE, sp.get_value());
        sp.inc();
        return value;
    }
}