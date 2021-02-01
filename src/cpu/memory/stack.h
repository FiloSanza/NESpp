#ifndef NESPP_STACK_H
#define NESPP_STACK_H

#include "../register/stack_pointer.h"
#include "memory.h"

namespace nespp {

    constexpr uint16_t STACK_POINTER_START = 0x1ff;

    class Stack {
    private:
        StackPointer& sp;
        Memory& memory;
    public:
        Stack() = delete;

        Stack(StackPointer& sp, Memory& memory);

        void push(uint8_t value);
        uint8_t pop();
    };

}

#endif //NESPP_STACK_H
