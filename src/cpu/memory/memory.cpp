#include "memory.h"

namespace nespp {

    Memory::Memory() {
        memory.resize(MEM_SIZE, 0x0);
        callback_on_write = {};
        callback_on_read = {};
    }

    void Memory::set_u8(uint16_t address, uint8_t value) {
        for(auto &f : callback_on_write)
            f(address, memory[address]);

        memory[address] = value;
    }

    uint8_t Memory::get_u8(uint16_t address) {
        for(auto &f : callback_on_read)
            f(address, memory[address]);

        return memory[address];
    }

    bool Memory::cross_page_boundary(uint16_t address, uint8_t size = 8) {
        uint16_t end = address + size - 1;
        uint16_t page_start = address & (uint16_t)0xFF00;
        uint16_t page_end = end & (uint16_t)0xFF00;

        return page_start == page_end;
    }

    void Memory::add_callback_on_write(const std::function<void(uint16_t, uint8_t)>& callback) {
        callback_on_write.emplace_back(callback);
    }

    void Memory::add_callback_on_read(const std::function<void(uint16_t, uint8_t)>& callback) {
        callback_on_read.emplace_back(callback);
    }

    void Memory::reset_callbacks() {
        callback_on_read.clear();
        callback_on_write.clear();
    }

    void Memory::load(const std::vector<uint8_t>& data, uint16_t address) {
        //TODO: use std::format when available
        if(address + data.size() >= memory.size())
            throw std::out_of_range("Error trying to load " + std::to_string(data.size()) + " bytes at " + std::to_string(address) + " to memory, memory size is " + std::to_string(memory.size()));

        for(size_t i=0; i<data.size(); i++)
            set_u8(i + address, data[i]);
    }

    void Memory::set_u8_from_page(uint8_t page, uint8_t offset, uint8_t value) {
        set_u8(get_u8_from_page(page, offset), value);
    }

    uint8_t Memory::get_u8_from_page(uint8_t page, uint8_t offset) {
        return get_u8(get_page_address(page, offset));
    }

    uint16_t Memory::get_page_address(uint8_t page, uint8_t offset) {
        uint16_t address = page;
        address = address << 8u | offset;
        return address;
    }

}