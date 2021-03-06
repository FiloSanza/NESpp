#ifndef NESPP_BITS_H
#define NESPP_BITS_H

#include <cstdint>
#include <string>
#include <iomanip>

namespace nespp::bits {

    template <typename T>
    static T set_nth_bit(T value, uint8_t idx) {
        value |= (1u << idx);
        return value;
    }

    template <typename T>
    static T clear_nth_bit(T value, uint8_t idx) {
        value &= ~(1u << idx);
        return value;
    }

    template <typename T>
    bool get_nth_bit(T value, uint8_t idx) {
        T bit = (1u << idx) & value;
        return bit != 0;
    }

    template<typename T>
    std::string int_to_hex(T val, int width = 4) {
        std::stringstream stream;
        stream << "0x" << std::uppercase << std::setfill('0') << std::setw(width) << std::hex << (int)val;
        return stream.str();
    }

    static uint8_t get_low_u8(uint16_t value) {
        uint8_t result = value & 0xff;
        return result;
    }

    static uint8_t get_high_u8(uint16_t value) {
        uint8_t result = (value >> 8u) & 0xff;
        return result;
    }

    static uint16_t merge_u8(uint8_t low, uint8_t high) {
        uint16_t result = high;
        result = (result << 8u) | low;
        return result;
    }
}

#endif //NESPP_BITS_H
