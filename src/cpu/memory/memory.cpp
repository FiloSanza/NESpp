#include "memory.h"

#include <iostream>

namespace nespp {

    Memory::Memory() {
        memory.resize(MEM_SIZE, 0x0);
        callback_on_write = {};
        callback_on_read = {};
    }

    //TODO: add out of memory checks + tests
    void Memory::set_u8(uint16_t address, uint8_t value) {
        for(auto &f : callback_on_write)
            f(address, value);

        memory[address] = value;
    }

    //TODO: add out of memory checks + tests
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
        if(address + data.size() > memory.size())
            throw std::out_of_range("Error trying to load " + std::to_string(data.size()) + " bytes at " + std::to_string(address) + " to memory, memory size is " + std::to_string(memory.size()));

        for(size_t i=0; i<data.size(); i++)
            set_u8(i + address, data[i]);
    }

    void Memory::set_u8_from_page(uint8_t page, uint8_t offset, uint8_t value) {
        set_u8(get_page_address(page, offset), value);
    }

    uint8_t Memory::get_u8_from_page(uint8_t page, uint8_t offset) {
        return get_u8(get_page_address(page, offset));
    }

    uint16_t Memory::get_page_address(uint8_t page, uint8_t offset) {
        uint16_t address = page;
        address = address << 8u | offset;
        return address;
    }

    void Memory::set_u16(uint16_t address, uint16_t value) {
        uint8_t low = value & 0xff;
        uint8_t high = (value >> 8) & 0xff;

        set_u8(address, low);
        set_u8(address + 1, high);
    }

    uint16_t Memory::get_u16(uint16_t address) {
        uint16_t value = get_u8(address + 1);
        value = (value << 8u) | get_u8(address);

        return value;
    }

    uint16_t Memory::get_u16_bug(uint16_t address) {
        auto lo_addr = address;
        auto hi_addr = (lo_addr & 0xff00) | ((lo_addr + 1) & 0x00ff);

        std::cout << "BUGGY MEMORY READ @ " << bits::int_to_hex(address) << " indirect is " << bits::int_to_hex(lo_addr) << " " << bits::int_to_hex(hi_addr) << "\n";

        auto lo = get_u8(lo_addr);
        auto hi = get_u8(hi_addr);

        return bits::merge_u8(lo, hi);
    }

    void Memory::set_u16_from_page(uint8_t page, uint8_t offset, uint16_t value) {
        set_u16(get_page_address(page, offset), value);
    }

    uint16_t Memory::get_u16_from_page(uint8_t page, uint8_t offset) {
        return get_u16(get_page_address(page, offset));
    }

}