#include <fstream>

#include "utils/disassembler.h"
#include "utils/debug.h"
#include "cpu/machine.h"

namespace nespp::nestest {
    constexpr char NESTEST_NES_PATH[] = "res/nestest/nestest.nes";
    constexpr uint16_t NESTEST_LOAD_ADDR_1 = 0x8000;
    constexpr uint16_t NESTEST_LOAD_ADDR_2 = 0xc000;
    constexpr uint8_t NESTEST_EXIT_ADDR_LOW = 0x02;
    constexpr uint8_t NESTEST_EXIT_ADDR_HIGH = 0x03;
    constexpr uint16_t NESTEST_PC_START = 0xc000;

    uint16_t run_nestest() {
        std::ifstream file(NESTEST_NES_PATH, std::ios::binary);

        if(!file.is_open()) {
            std::cerr << "Could not open the file: " << NESTEST_NES_PATH << std::endl;
            return -1;
        }

        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});
        std::vector<uint8_t> rom(buffer.begin() + 0x10, buffer.begin() + 0x4010);    //Ignore ines header

        auto machine = Machine(rom, NESTEST_LOAD_ADDR_1);
        machine.get_cpu().get_memory().load(rom, NESTEST_LOAD_ADDR_2);

        machine.get_cpu().get_program_counter().set_value(NESTEST_PC_START);

        auto before_exec_debug = [](Machine &machine, uint8_t opcode) {
            std::stringstream stream;

            stream << bits::int_to_hex(machine.get_cpu().get_program_counter().get_value() - 1).substr(2) << " ";
            //stream << disassembler::disasm(opcode, machine.get_cpu());

            //std::cerr << "PC before: " << bits::int_to_hex(machine.get_cpu().get_program_counter().get_value()) << "\n";
            stream << machine.get_cpu().dump();

            std::cerr << stream.str() << "\n";
        };

        //auto after_exec_debug = [](Machine &machine, uint8_t _) {
        //    //machine.get_cpu().dump();
        //    std::cerr << "PC after: " << bits::int_to_hex(machine.get_cpu().get_program_counter().get_value()) << "\n";
        //    //std::cerr << "_________________________" << std::endl;
        //};

        machine.get_cpu().get_memory().add_callback_on_write(debug::print_memory_write_stderr);
        machine.get_cpu().get_memory().add_callback_on_read(debug::print_memory_read_stderr);

        machine.add_before_exec_callback(before_exec_debug);
        //machine.add_after_exec_callback(after_exec_debug);

        //detect infinite loop to stop
        long long idx = 0;
        uint16_t last_pc[4] = {0, 1, 2, 3};
        while(true) {
            if(last_pc[0] == last_pc[2] && last_pc[1] == last_pc[3]) break;

            machine.execute();

            last_pc[idx % 4] = machine.get_cpu().get_program_counter().get_value();
            idx++;
        }

        auto exit_code_low = machine.get_cpu().get_memory().get_u8(NESTEST_EXIT_ADDR_LOW);
        auto exit_code_high = machine.get_cpu().get_memory().get_u8(NESTEST_EXIT_ADDR_HIGH);
        auto exit_code = bits::merge_u8(exit_code_low, exit_code_high);

        return exit_code;
    }
}