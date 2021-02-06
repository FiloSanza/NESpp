#ifndef NESPP_STACK_H
#define NESPP_STACK_H

#include "../register/stack_pointer.h"
#include "memory.h"

namespace nespp {

    constexpr uint16_t STACK_POINTER_START = 0xff;
    constexpr uint16_t STACK_PAGE = 1;

    class Stack {
    public:
        Stack() = delete;
        Stack(StackPointer& sp, Memory& memory);

        void push(uint8_t value);

        uint8_t pop();
    private:
        StackPointer& sp;
        Memory& memory;
    };

}

#endif //NESPP_STACK_H
