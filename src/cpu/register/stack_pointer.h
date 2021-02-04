#ifndef NESPP_STACK_POINTER_H
#define NESPP_STACK_POINTER_H

#include <cstdint>
#include "register.h"
#include "../../utils/bits.h"

namespace nespp {

    class StackPointer : public Register<uint16_t> {
    public:
        StackPointer();

        void inc();
        void dec();

        void set_value(uint16_t value) override;
    };

}

#endif //NESPP_STACK_POINTER_H
