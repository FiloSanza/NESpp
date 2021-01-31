//
// Created by filip on 31/01/2021.
//

#ifndef NESPP_PROGRAM_STATUS_H
#define NESPP_PROGRAM_STATUS_H

#include "register.h"
#include <bitset>

constexpr int FLAG_NUM = 7;

namespace nespp {

    enum Flags {
        Carry = 0,
        Zero = 1,
        Interrupt = 2,
        DecimalMode = 3,
        Break = 4,
        Overflow = 5,
        Negative = 6
    };

    class ProgramStatus : public Register<std::bitset<FLAG_NUM>>{
    public:
        bool is_carry_set();
        bool is_zero_set();
        bool is_interrupt_set();
        bool is_decimal_mode_set();
        bool is_break_set();
        bool is_overflow_set();
        bool is_negative_set();

        void set_carry(bool value);
        void set_zero(bool value);
        void set_interrupt(bool value);
        void set_decimal_mode(bool value);
        void set_break(bool value);
        void set_overflow(bool value);
        void set_negative(bool value);
    };

}

#endif //NESPP_PROGRAM_STATUS_H
