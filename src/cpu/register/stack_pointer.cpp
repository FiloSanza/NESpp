#include "stack_pointer.h"

namespace nespp {
    StackPointer::StackPointer() : Register<uint16_t>("SP") {

    }

    void StackPointer::inc() {
        value++;
    }

    void StackPointer::dec() {
        value--;
    }

    void StackPointer::set_value(uint16_t value) {
        //make sure that the most significant byte is 0b00000001
        //TODO: use 8 bit sp and get from memory using page 1 instead of the higher byte
        for(int i=15; i>8; i--)
            value = utils::clear_nth_bit(value, i);
        value = utils::set_nth_bit(value, 8);
        Register::set_value(value);
    }
}