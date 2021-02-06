#ifndef NESPP_STACK_POINTER_H
#define NESPP_STACK_POINTER_H

#include <cstdint>
#include "register.h"
#include "../../utils/bits.h"

namespace nespp {

    class StackPointer : public Register<uint8_t> {
    public:
        StackPointer();

        void inc();
        void dec();
    };

}

#endif //NESPP_STACK_POINTER_H
