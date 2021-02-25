#ifndef NESPP_MEMORY_H
#define NESPP_MEMORY_H

#include <vector>
#include <cstdint>
#include <functional>
#include <stdexcept>

#include "utils/bits.h"

namespace nespp {

    constexpr uint32_t MEM_SIZE = 0x10000;  //64K
    constexpr uint32_t PAGE_SIZE = 0x100;           //256B

    class Memory {
    public:
        Memory();
        void load(const std::vector<uint8_t>& data, uint16_t address);

        void set_u8(uint16_t address, uint8_t value);
        uint8_t get_u8(uint16_t address);

        void set_u16(uint16_t address, uint16_t value);
        uint16_t get_u16(uint16_t address);
        uint16_t get_u16_bug(uint16_t address);

        void set_u8_from_page(uint8_t page, uint8_t offset, uint8_t value);
        uint8_t get_u8_from_page(uint8_t page, uint8_t offset);

        void set_u16_from_page(uint8_t page, uint8_t offset, uint16_t value);
        uint16_t get_u16_from_page(uint8_t page, uint8_t offset);

        void add_callback_on_write(const std::function<void(uint16_t, uint8_t)>& callback);
        void add_callback_on_read(const std::function<void(uint16_t, uint8_t)>& callback);
        void reset_callbacks();
        
        //return true if the page boundary is crossed reading/writing "size" bits starting from "address"
        static bool cross_page_boundary(uint16_t address, uint8_t size);
    private:
        std::vector<uint8_t> memory;
        std::vector<std::function<void(uint16_t, uint16_t)>> callback_on_write;
        std::vector<std::function<void(uint16_t, uint16_t)>> callback_on_read;

        static uint16_t get_page_address(uint8_t page, uint8_t offset);
    };

}

#endif //NESPP_MEMORY_H
