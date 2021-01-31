//
// Created by filip on 31/01/2021.
//

#include "program_status.h"

namespace nespp {
    bool ProgramStatus::is_carry_set() {
        return value[Flags::Carry];
    }
    bool ProgramStatus::is_zero_set() {
        return value[Flags::Zero];
    }
    bool ProgramStatus::is_interrupt_set() {
        return value[Flags::Interrupt];
    }
    bool ProgramStatus::is_decimal_mode_set() {
        return value[Flags::DecimalMode];
    }
    bool ProgramStatus::is_break_set() {
        return value[Flags::Break];
    }
    bool ProgramStatus::is_overflow_set() {
        return value[Flags::Overflow];
    }
    bool ProgramStatus::is_negative_set() {
        return value[Flags::Negative];
    }

    void ProgramStatus::set_carry(bool value) {
        this->value[Flags::Carry] = value;
    }
    void ProgramStatus::set_zero(bool value) {
        this->value[Flags::Zero] = value;
    }
    void ProgramStatus::set_interrupt(bool value) {
        this->value[Flags::Interrupt] = value;
    }
    void ProgramStatus::set_decimal_mode(bool value) {
        this->value[Flags::DecimalMode] = value;
    }
    void ProgramStatus::set_break(bool value) {
        this->value[Flags::Break] = value;
    }
    void ProgramStatus::set_overflow(bool value) {
        this->value[Flags::Overflow] = value;
    }
    void ProgramStatus::set_negative(bool value) {
        this->value[Flags::Negative] = value;
    }
}