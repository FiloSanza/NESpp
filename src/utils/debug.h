#ifndef NESPP_DEBUG_H
#define NESPP_DEBUG_H

#include <iomanip>
#include <iostream>
#include <cstdint>
#include "bits.h"

namespace nespp::debug {
    static void print_memory_read_stderr(uint16_t addr, uint16_t value) {
        std::cout << "Read @ " << bits::int_to_hex(addr) << " value " << bits::int_to_hex(value) << "\n";
    }

    static void print_memory_write_stderr(uint16_t addr, uint16_t value) {
        std::cout << "Write @ " << bits::int_to_hex(addr) << " value " << bits::int_to_hex(value) << "\n";
    }
}

#endif //NESPP_DEBUG_H
