#include "memory.h"

namespace nespp {

    Memory::Memory() {
        memory.resize(MEM_SIZE, 0x0);
        callback_on_write = {};
        callback_on_read = {};
    }

    void Memory::set_u8(uint16_t address, uint8_t value) {
        memory[address] = value;
    }

    uint8_t Memory::get_u8(uint16_t address) {
        return memory[address];
    }

    bool Memory::cross_page_boundary(uint16_t address, uint8_t size = 8) {
        uint16_t end = address + size - 1;
        uint16_t page_start = address & 0xFF00;
        uint16_t page_end = end & 0xFF00;

        return page_start == page_end;
    }

    void Memory::add_callback_on_write(std::function<void(uint16_t, uint8_t)> callback) {
        callback_on_write.push_back(callback);
    }

    void Memory::add_callback_on_read(std::function<void(uint16_t, uint8_t)> callback) {
        callback_on_read.push_back(callback);
    }

    void Memory::reset_callbacks() {
        callback_on_read.clear();
        callback_on_write.clear();
    }

}