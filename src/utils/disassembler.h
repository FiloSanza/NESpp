#ifndef NESPP_DISASSEMBLER_H
#define NESPP_DISASSEMBLER_H

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <string>
#include <map>
#include "../cpu/handlers/opcodes.h"
#include "../cpu/cpu.h"
#include "bits.h"

namespace nespp::disassembler {

    static std::map<uint32_t, std::string> get_disasm_table() {
        auto table = std::map<uint32_t, std::string>();

        table.emplace(0x69, "ADC_IMM");
        table.emplace(0x65, "ADC_ZERO");
        table.emplace(0x75, "ADC_ZERO_X");
        table.emplace(0x6d, "ADC_ABS");
        table.emplace(0x7d, "ADC_ABS_X");
        table.emplace(0x79, "ADC_ABS_Y");
        table.emplace(0x61, "ADC_IND_X");
        table.emplace(0x71, "ADC_IND_Y");
        table.emplace(0x29, "AND_IMM");
        table.emplace(0x25, "AND_ZERO");
        table.emplace(0x35, "AND_ZERO_X");
        table.emplace(0x2d, "AND_ABS");
        table.emplace(0x3d, "AND_ABS_X");
        table.emplace(0x39, "AND_ABS_Y");
        table.emplace(0x21, "AND_IND_X");
        table.emplace(0x31, "AND_IND_Y");
        table.emplace(0x0A, "ASL_ACC");
        table.emplace(0x06, "ASL_ZERO");
        table.emplace(0x16, "ASL_ZERO_X");
        table.emplace(0x0e, "ASL_ABS");
        table.emplace(0x1e, "ASL_ABS_X");
        table.emplace(0x90, "BCC");
        table.emplace(0xb0, "BCS");
        table.emplace(0xf0, "BEQ");
        table.emplace(0x24, "BIT_ZERO");
        table.emplace(0x2c, "BIT_ABS");
        table.emplace(0x30, "BMI");
        table.emplace(0xd0, "BNE");
        table.emplace(0x10, "BPL");
        table.emplace(0x00, "BRK");
        table.emplace(0x50, "BVC");
        table.emplace(0x70, "BVS");
        table.emplace(0x18, "CLC");
        table.emplace(0xd8, "CLD");
        table.emplace(0x58, "CLI");
        table.emplace(0xb8, "CLV");
        table.emplace(0xc9, "CMP_IMM");
        table.emplace(0xc5, "CMP_ZERO");
        table.emplace(0xd5, "CMP_ZERO_X");
        table.emplace(0xcd, "CMP_ABS");
        table.emplace(0xdd, "CMP_ABS_X");
        table.emplace(0xd9, "CMP_ABS_Y");
        table.emplace(0xc1, "CMP_IND_X");
        table.emplace(0xd1, "CMP_IND_Y");
        table.emplace(0xe0, "CPX_IMM");
        table.emplace(0xe4, "CPX_ZERO");
        table.emplace(0xec, "CPX_ABS");
        table.emplace(0xc0, "CPY_IMM");
        table.emplace(0xc4, "CPY_ZERO");
        table.emplace(0xcc, "CPY_ABS");
        table.emplace(0xc6, "DEC_ZERO");
        table.emplace(0xd6, "DEC_ZERO_X");
        table.emplace(0xce, "DEC_ABS");
        table.emplace(0xde, "DEC_ABS_X");
        table.emplace(0xca, "DEX");
        table.emplace(0x88, "DEY");
        table.emplace(0x49, "EOR_IMM");
        table.emplace(0x45, "EOR_ZERO");
        table.emplace(0x55, "EOR_ZERO_X");
        table.emplace(0x4d, "EOR_ABS");
        table.emplace(0x5d, "EOR_ABS_X");
        table.emplace(0x59, "EOR_ABS_Y");
        table.emplace(0x41, "EOR_IND_X");
        table.emplace(0x51, "EOR_IND_Y");
        table.emplace(0xe6, "INC_ZERO");
        table.emplace(0xf6, "INC_ZERO_X");
        table.emplace(0xee, "INC_ABS");
        table.emplace(0xfe, "INC_ABS_X");
        table.emplace(0xe8, "INX");
        table.emplace(0xc8, "INY");
        table.emplace(0x4c, "JMP_ABS");
        table.emplace(0x6c, "JMP_IND");
        table.emplace(0x20, "JSR");
        table.emplace(0xa9, "LDA_IMM");
        table.emplace(0xa5, "LDA_ZERO");
        table.emplace(0xb5, "LDA_ZERO_X");
        table.emplace(0xad, "LDA_ABS");
        table.emplace(0xbd, "LDA_ABS_X");
        table.emplace(0xb9, "LDA_ABS_Y");
        table.emplace(0xa1, "LDA_IND_X");
        table.emplace(0xb1, "LDA_IND_Y");
        table.emplace(0xa2, "LDX_IMM");
        table.emplace(0xa6, "LDX_ZERO");
        table.emplace(0xb6, "LDX_ZERO_Y");
        table.emplace(0xae, "LDX_ABS");
        table.emplace(0xbe, "LDX_ABS_Y");
        table.emplace(0xa0, "LDY_IMM");
        table.emplace(0xa4, "LDY_ZERO");
        table.emplace(0xb4, "LDY_ZERO_X");
        table.emplace(0xac, "LDY_ABS");
        table.emplace(0xbc, "LDY_ABS_X");
        table.emplace(0x4a, "LSR_ACC");
        table.emplace(0x46, "LSR_ZERO");
        table.emplace(0x56, "LSR_ZERO_X");
        table.emplace(0x4e, "LSR_ABS");
        table.emplace(0x5e, "LSR_ABS_X");
        table.emplace(0xea, "NOP");
        table.emplace(0x09, "ORA_IMM");
        table.emplace(0x05, "ORA_ZERO");
        table.emplace(0x15, "ORA_ZERO_X");
        table.emplace(0x0d, "ORA_ABS");
        table.emplace(0x1d, "ORA_ABS_X");
        table.emplace(0x19, "ORA_ABS_Y");
        table.emplace(0x01, "ORA_IND_X");
        table.emplace(0x11, "ORA_IND_Y");
        table.emplace(0x48, "PHA");
        table.emplace(0x08, "PHP");
        table.emplace(0x68, "PLA");
        table.emplace(0x28, "PLP");
        table.emplace(0x2a, "ROL_ACC");
        table.emplace(0x26, "ROL_ZERO");
        table.emplace(0x36, "ROL_ZERO_X");
        table.emplace(0x2e, "ROL_ABS");
        table.emplace(0x3e, "ROL_ABS_X");
        table.emplace(0x6a, "ROR_ACC");
        table.emplace(0x66, "ROR_ZERO");
        table.emplace(0x76, "ROR_ZERO_X");
        table.emplace(0x6e, "ROR_ABS");
        table.emplace(0x7e, "ROR_ABS_X");
        table.emplace(0x40, "RTI");
        table.emplace(0x60, "RTS");
        table.emplace(0xe9, "SBC_IMM");
        table.emplace(0xe5, "SBC_ZERO");
        table.emplace(0xf5, "SBC_ZERO_X");
        table.emplace(0xed, "SBC_ABS");
        table.emplace(0xfd, "SBC_ABS_X");
        table.emplace(0xf9, "SBC_ABS_Y");
        table.emplace(0xe1, "SBC_IND_X");
        table.emplace(0xf1, "SBC_IND_Y");
        table.emplace(0x38, "SEC");
        table.emplace(0xf8, "SED");
        table.emplace(0x78, "SEI");
        table.emplace(0x85, "STA_ZERO");
        table.emplace(0x95, "STA_ZERO_X");
        table.emplace(0x8d, "STA_ABS");
        table.emplace(0x9d, "STA_ABS_X");
        table.emplace(0x99, "STA_ABS_Y");
        table.emplace(0x81, "STA_IND_X");
        table.emplace(0x91, "STA_IND_Y");
        table.emplace(0x86, "STX_ZERO");
        table.emplace(0x96, "STX_ZERO_Y");
        table.emplace(0x8e, "STX_ABS");
        table.emplace(0x84, "STY_ZERO");
        table.emplace(0x94, "STY_ZERO_X");
        table.emplace(0x8c, "STY_ABS");
        table.emplace(0xaa, "TAX");
        table.emplace(0xa8, "TAY");
        table.emplace(0xba, "TSX");
        table.emplace(0x8a, "TXA");
        table.emplace(0x9a, "TXS");
        table.emplace(0x98, "TYA");

        return table;
    }

    static std::map<uint32_t, uint8_t> get_opcode_size_table() {
        auto table = std::map<uint32_t, uint8_t>();

        table.emplace(Opcodes::ADC_IMM, 2);
        table.emplace(Opcodes::ADC_ZERO, 2);
        table.emplace(Opcodes::ADC_ZERO_X, 2);
        table.emplace(Opcodes::ADC_ABS, 3);
        table.emplace(Opcodes::ADC_ABS_X, 3);
        table.emplace(Opcodes::ADC_ABS_Y, 3);
        table.emplace(Opcodes::ADC_IND_X, 2);
        table.emplace(Opcodes::ADC_IND_Y, 2);
        table.emplace(Opcodes::AND_IMM, 2);
        table.emplace(Opcodes::AND_ZERO, 2);
        table.emplace(Opcodes::AND_ZERO_X, 2);
        table.emplace(Opcodes::AND_ABS, 3);
        table.emplace(Opcodes::AND_ABS_X, 3);
        table.emplace(Opcodes::AND_ABS_Y, 3);
        table.emplace(Opcodes::AND_IND_X, 2);
        table.emplace(Opcodes::AND_IND_Y, 2);
        table.emplace(Opcodes::ASL_ACC, 1);
        table.emplace(Opcodes::ASL_ZERO, 2);
        table.emplace(Opcodes::ASL_ZERO_X, 2);
        table.emplace(Opcodes::ASL_ABS, 3);
        table.emplace(Opcodes::ASL_ABS_X, 3);
        table.emplace(Opcodes::BCC, 2);
        table.emplace(Opcodes::BCS, 2);
        table.emplace(Opcodes::BEQ, 2);
        table.emplace(Opcodes::BIT_ZERO, 2);
        table.emplace(Opcodes::BIT_ABS, 3);
        table.emplace(Opcodes::BMI, 2);
        table.emplace(Opcodes::BNE, 2);
        table.emplace(Opcodes::BPL, 2);
        table.emplace(Opcodes::BRK, 1);
        table.emplace(Opcodes::BVC, 2);
        table.emplace(Opcodes::BVS, 2);
        table.emplace(Opcodes::CLC, 1);
        table.emplace(Opcodes::CLD, 1);
        table.emplace(Opcodes::CLI, 1);
        table.emplace(Opcodes::CLV, 1);
        table.emplace(Opcodes::CMP_IMM, 2);
        table.emplace(Opcodes::CMP_ZERO, 2);
        table.emplace(Opcodes::CMP_ZERO_X, 2);
        table.emplace(Opcodes::CMP_ABS, 3);
        table.emplace(Opcodes::CMP_ABS_X, 3);
        table.emplace(Opcodes::CMP_ABS_Y, 3);
        table.emplace(Opcodes::CMP_IND_X, 2);
        table.emplace(Opcodes::CMP_IND_Y, 2);
        table.emplace(Opcodes::CPX_IMM, 2);
        table.emplace(Opcodes::CPX_ZERO, 2);
        table.emplace(Opcodes::CPX_ABS, 3);
        table.emplace(Opcodes::CPY_IMM, 2);
        table.emplace(Opcodes::CPY_ZERO, 2);
        table.emplace(Opcodes::CPY_ABS, 3);
        table.emplace(Opcodes::DEC_ZERO, 2);
        table.emplace(Opcodes::DEC_ZERO_X, 2);
        table.emplace(Opcodes::DEC_ABS, 3);
        table.emplace(Opcodes::DEC_ABS_X, 3);
        table.emplace(Opcodes::DEX, 1);
        table.emplace(Opcodes::DEY, 1);
        table.emplace(Opcodes::EOR_IMM, 2);
        table.emplace(Opcodes::EOR_ZERO, 2);
        table.emplace(Opcodes::EOR_ZERO_X, 2);
        table.emplace(Opcodes::EOR_ABS, 3);
        table.emplace(Opcodes::EOR_ABS_X, 3);
        table.emplace(Opcodes::EOR_ABS_Y, 3);
        table.emplace(Opcodes::EOR_IND_X, 2);
        table.emplace(Opcodes::EOR_IND_Y, 2);
        table.emplace(Opcodes::INC_ZERO, 2);
        table.emplace(Opcodes::INC_ZERO_X, 2);
        table.emplace(Opcodes::INC_ABS, 3);
        table.emplace(Opcodes::INC_ABS_X, 3);
        table.emplace(Opcodes::INX, 1);
        table.emplace(Opcodes::INY, 1);
        table.emplace(Opcodes::JMP_ABS, 3);
        table.emplace(Opcodes::JMP_IND, 2);
        table.emplace(Opcodes::JSR, 3);
        table.emplace(Opcodes::LDA_IMM, 2);
        table.emplace(Opcodes::LDA_ZERO, 2);
        table.emplace(Opcodes::LDA_ZERO_X, 2);
        table.emplace(Opcodes::LDA_ABS, 3);
        table.emplace(Opcodes::LDA_ABS_X, 3);
        table.emplace(Opcodes::LDA_ABS_Y, 3);
        table.emplace(Opcodes::LDA_IND_X, 2);
        table.emplace(Opcodes::LDA_IND_Y, 2);
        table.emplace(Opcodes::LDX_IMM, 2);
        table.emplace(Opcodes::LDX_ZERO, 2);
        table.emplace(Opcodes::LDX_ZERO_Y, 2);
        table.emplace(Opcodes::LDX_ABS, 3);
        table.emplace(Opcodes::LDX_ABS_Y, 3);
        table.emplace(Opcodes::LDY_IMM, 2);
        table.emplace(Opcodes::LDY_ZERO, 2);
        table.emplace(Opcodes::LDY_ZERO_X, 2);
        table.emplace(Opcodes::LDY_ABS, 3);
        table.emplace(Opcodes::LDY_ABS_X, 3);
        table.emplace(Opcodes::LSR_ACC, 1);
        table.emplace(Opcodes::LSR_ZERO, 2);
        table.emplace(Opcodes::LSR_ZERO_X, 2);
        table.emplace(Opcodes::LSR_ABS, 3);
        table.emplace(Opcodes::LSR_ABS_X, 3);
        table.emplace(Opcodes::NOP, 1);
        table.emplace(Opcodes::ORA_IMM, 2);
        table.emplace(Opcodes::ORA_ZERO, 2);
        table.emplace(Opcodes::ORA_ZERO_X, 2);
        table.emplace(Opcodes::ORA_ABS, 3);
        table.emplace(Opcodes::ORA_ABS_X, 3);
        table.emplace(Opcodes::ORA_ABS_Y, 3);
        table.emplace(Opcodes::ORA_IND_X, 2);
        table.emplace(Opcodes::ORA_IND_Y, 2);
        table.emplace(Opcodes::PHA, 1);
        table.emplace(Opcodes::PHP, 1);
        table.emplace(Opcodes::PLA, 1);
        table.emplace(Opcodes::PLP, 1);
        table.emplace(Opcodes::ROL_ACC, 1);
        table.emplace(Opcodes::ROL_ZERO, 2);
        table.emplace(Opcodes::ROL_ZERO_X, 2);
        table.emplace(Opcodes::ROL_ABS, 3);
        table.emplace(Opcodes::ROL_ABS_X, 3);
        table.emplace(Opcodes::ROR_ACC, 1);
        table.emplace(Opcodes::ROR_ZERO, 2);
        table.emplace(Opcodes::ROR_ZERO_X, 2);
        table.emplace(Opcodes::ROR_ABS, 3);
        table.emplace(Opcodes::ROR_ABS_X, 3);
        table.emplace(Opcodes::RTI, 1);
        table.emplace(Opcodes::RTS, 1);
        table.emplace(Opcodes::SBC_IMM, 2);
        table.emplace(Opcodes::SBC_ZERO, 2);
        table.emplace(Opcodes::SBC_ZERO_X, 2);
        table.emplace(Opcodes::SBC_ABS, 3);
        table.emplace(Opcodes::SBC_ABS_X, 3);
        table.emplace(Opcodes::SBC_ABS_Y, 3);
        table.emplace(Opcodes::SBC_IND_X, 2);
        table.emplace(Opcodes::SBC_IND_Y, 2);
        table.emplace(Opcodes::SEC, 1);
        table.emplace(Opcodes::SED, 1);
        table.emplace(Opcodes::SEI, 1);
        table.emplace(Opcodes::STA_ZERO, 2);
        table.emplace(Opcodes::STA_ZERO_X, 2);
        table.emplace(Opcodes::STA_ABS, 3);
        table.emplace(Opcodes::STA_ABS_X, 3);
        table.emplace(Opcodes::STA_ABS_Y, 3);
        table.emplace(Opcodes::STA_IND_X, 2);
        table.emplace(Opcodes::STA_IND_Y, 2);
        table.emplace(Opcodes::STX_ZERO, 2);
        table.emplace(Opcodes::STX_ZERO_Y, 2);
        table.emplace(Opcodes::STX_ABS, 3);
        table.emplace(Opcodes::STY_ZERO, 2);
        table.emplace(Opcodes::STY_ZERO_X, 2);
        table.emplace(Opcodes::STY_ABS, 3);
        table.emplace(Opcodes::TAX, 1);
        table.emplace(Opcodes::TAY, 1);
        table.emplace(Opcodes::TSX, 1);
        table.emplace(Opcodes::TXA, 1);
        table.emplace(Opcodes::TXS, 1);
        table.emplace(Opcodes::TYA, 1);

        return table;
    };

    static std::string disasm(uint8_t opcode, Cpu &cpu) {
        static auto table = get_disasm_table();
        static auto opcode_size = get_opcode_size_table();

        std::stringstream stream;

        stream << bits::int_to_hex(opcode, 2).substr(2) << " ";

        switch (opcode_size[opcode]) {
            case 1:
                stream << "\t" << table[opcode].substr(0, 3) << "\t\t\t";
                break;
            case 2: {
                auto addr = cpu.get_program_counter().get_value();
                auto value = cpu.get_memory().get_u8(addr);

                stream << bits::int_to_hex(value, 2).substr(2) << "\t" <<
                    table[opcode] << " " <<
                    bits::int_to_hex(value) << "\t\t";

                break;
            }
            case 3: {
                auto addr = cpu.get_program_counter().get_value();
                auto value = cpu.get_memory().get_u16(addr);

                stream << bits::int_to_hex(bits::get_low_u8(value), 2).substr(2) << " " <<
                    bits::int_to_hex(bits::get_high_u8(value), 2).substr(2) << "\t" <<
                    table[opcode] << " " <<
                    bits::int_to_hex(value) << "\t\t";

                break;
            }
        }

        return stream.str();
    }

}


#endif //NESPP_DISASSEMBLER_H
