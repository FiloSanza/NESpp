#ifndef NESPP_BITS_H
#define NESPP_BITS_H

#include <cstdint>

namespace nespp::utils {

    template <typename T>
    T set_nth_bit(T value, uint8_t idx) {
        value |= (1u << idx);
        return value;
    }

    template <typename T>
    T clear_nth_bit(T value, uint8_t idx) {
        value &= ~(1u << idx);
        return value;
    }

    template <typename T>
    bool get_nth_bit(T value, uint8_t idx) {
        T bit = (1u << idx) & value;
        return bit != 0;
    }

}

#endif //NESPP_BITS_H
