#include "store_opcodes_handlers.h"

namespace nespp::store_opcodes {

    std::map<uint8_t, std::function<void(Cpu &)>> get_handlers() {
        auto handlers = std::map<uint8_t, std::function<void(Cpu &)>>();

        handlers.emplace(Opcodes::STA_ZERO, sta_zero);
        handlers.emplace(Opcodes::STA_ZERO_X, sta_zero_x);
        handlers.emplace(Opcodes::STA_ABS, sta_absolute);
        handlers.emplace(Opcodes::STA_ABS_X, sta_absolute_x);
        handlers.emplace(Opcodes::STA_ABS_Y, sta_absolute_y);
        handlers.emplace(Opcodes::STA_IND_X, sta_indirect_x);
        handlers.emplace(Opcodes::STA_IND_Y, sta_indirect_y);

        return handlers;
    }

    void sta(Cpu &cpu, Register<uint8_t> &reg) {

    }

    void sta_zero(Cpu &cpu) {

    }

    void sta_zero_x(Cpu &cpu) {

    }

    void sta_absolute(Cpu &cpu) {

    }

    void sta_absolute_x(Cpu &cpu) {

    }

    void sta_absolute_y(Cpu &cpu) {

    }

    void sta_indirect_x(Cpu &cpu) {

    }

    void sta_indirect_y(Cpu &cpu) {

    }
}