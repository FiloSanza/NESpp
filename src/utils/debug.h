#ifndef NESPP_DEBUG_H
#define NESPP_DEBUG_H

#include <iomanip>
#include <iostream>
#include <cstdint>

namespace nespp::debug {
    static void print_memory_read_stderr(uint16_t addr, uint16_t value) {
        std::cerr << "Read @ 0x" << std::hex << std::setw(4) << std::setfill('0') << addr << " value 0x" << std::hex << std::setw(4) << std::setfill('0') << value << "\n";
    }

    static void print_memory_write_stderr(uint16_t addr, uint16_t value) {
        std::cerr << "Write @ 0x" << std::hex << std::setw(4) << std::setfill('0') << addr << " value 0x" << std::hex << std::setw(4) << std::setfill('0') << value << "\n";
    }
}

#endif //NESPP_DEBUG_H
