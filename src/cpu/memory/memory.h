#ifndef NESPP_MEMORY_H
#define NESPP_MEMORY_H

#include <vector>
#include <cstdint>
#include <functional>

namespace nespp {

    constexpr uint32_t MEM_SIZE = 0x10000;  //64K
    constexpr uint32_t PAGE_SIZE = 0x100;           //256B

    class Memory {
    private:
        std::vector<uint8_t> memory;
        std::vector<std::function<void(uint16_t, uint16_t)>> callback_on_write;
        std::vector<std::function<void(uint16_t, uint16_t)>> callback_on_read;
    public:
        Memory();

        void set_u8(uint16_t address, uint8_t value);
        uint8_t get_u8(uint16_t address);

        //return true if the page boundary is crossed reading/writing "size" bits starting from "address"
        bool cross_page_boundary(uint16_t address, uint8_t size);

        void add_callback_on_write(std::function<void(uint16_t, uint8_t)> callback);
        void add_callback_on_read(std::function<void(uint16_t, uint8_t)> callback);
        void reset_callbacks();
    };

}

#endif //NESPP_MEMORY_H
