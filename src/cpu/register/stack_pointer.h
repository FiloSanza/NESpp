#ifndef NESPP_STACK_POINTER_H
#define NESPP_STACK_POINTER_H

#include <cstdint>
#include "register.h"

namespace nespp {

    class StackPointer : public Register<uint16_t> {
        void inc();
        void dec();
    };

}

#endif //NESPP_STACK_POINTER_H
