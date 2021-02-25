import sys

opcodes = {
    0x69: ("ADC_IMM", 2),
    0x65: ("ADC_ZERO", 2),
    0x75: ("ADC_ZERO_X", 2),
    0x6d: ("ADC_ABS", 3),
    0x7d: ("ADC_ABS_X", 3),
    0x79: ("ADC_ABS_Y", 3),
    0x61: ("ADC_IND_X", 2),
    0x71: ("ADC_IND_Y", 2),
    0x29: ("AND_IMM", 2),
    0x25: ("AND_ZERO", 2),
    0x35: ("AND_ZERO_X", 2),
    0x2d: ("AND_ABS", 3),
    0x3d: ("AND_ABS_X", 3),
    0x39: ("AND_ABS_Y", 3),
    0x21: ("AND_IND_X", 2),
    0x31: ("AND_IND_Y", 2),
    0x0A: ("ASL_ACC", 1),
    0x06: ("ASL_ZERO", 2),
    0x16: ("ASL_ZERO_X", 2),
    0x0e: ("ASL_ABS", 3),
    0x1e: ("ASL_ABS_X", 3),
    0x90: ("BCC", 2),
    0xb0: ("BCS", 2),
    0xf0: ("BEQ", 2),
    0x24: ("BIT_ZERO", 2),
    0x2c: ("BIT_ABS", 3),
    0x30: ("BMI", 2),
    0xd0: ("BNE", 2),
    0x10: ("BPL", 2),
    0x00: ("BRK", 1),
    0x50: ("BVC", 2),
    0x70: ("BVS", 2),
    0x18: ("CLC", 1),
    0xd8: ("CLD", 1),
    0x58: ("CLI", 1),
    0xb8: ("CLV", 1),
    0xc9: ("CMP_IMM", 2),
    0xc5: ("CMP_ZERO", 2),
    0xd5: ("CMP_ZERO_X", 2),
    0xcd: ("CMP_ABS", 3),
    0xdd: ("CMP_ABS_X", 3),
    0xd9: ("CMP_ABS_Y", 3),
    0xc1: ("CMP_IND_X", 2),
    0xd1: ("CMP_IND_Y", 2),
    0xe0: ("CPX_IMM", 2),
    0xe4: ("CPX_ZERO", 2),
    0xec: ("CPX_ABS", 3),
    0xc0: ("CPY_IMM", 2),
    0xc4: ("CPY_ZERO", 2),
    0xcc: ("CPY_ABS", 3),
    0xc6: ("DEC_ZERO", 2),
    0xd6: ("DEC_ZERO_X", 2),
    0xce: ("DEC_ABS", 3),
    0xde: ("DEC_ABS_X", 3),
    0xca: ("DEX", 1),
    0x88: ("DEY", 1),
    0x49: ("EOR_IMM", 2),
    0x45: ("EOR_ZERO", 2),
    0x55: ("EOR_ZERO_X", 2),
    0x4d: ("EOR_ABS", 3),
    0x5d: ("EOR_ABS_X", 3),
    0x59: ("EOR_ABS_Y", 3),
    0x41: ("EOR_IND_X", 2),
    0x51: ("EOR_IND_Y", 2),
    0xe6: ("INC_ZERO", 2),
    0xf6: ("INC_ZERO_X", 2),
    0xee: ("INC_ABS", 3),
    0xfe: ("INC_ABS_X", 3),
    0xe8: ("INX", 1),
    0xc8: ("INY", 1),
    0x4c: ("JMP_ABS", 3),
    0x6c: ("JMP_IND", 2),
    0x20: ("JSR", 3),
    0xa9: ("LDA_IMM", 2),
    0xa5: ("LDA_ZERO", 2),
    0xb5: ("LDA_ZERO_X", 2),
    0xad: ("LDA_ABS", 3),
    0xbd: ("LDA_ABS_X", 3),
    0xb9: ("LDA_ABS_Y", 3),
    0xa1: ("LDA_IND_X", 2),
    0xb1: ("LDA_IND_Y", 2),
    0xa2: ("LDX_IMM", 2),
    0xa6: ("LDX_ZERO", 2),
    0xb6: ("LDX_ZERO_Y", 2),
    0xae: ("LDX_ABS", 3),
    0xbe: ("LDX_ABS_Y", 3),
    0xa0: ("LDY_IMM", 2),
    0xa4: ("LDY_ZERO", 2),
    0xb4: ("LDY_ZERO_X", 2),
    0xac: ("LDY_ABS", 3),
    0xbc: ("LDY_ABS_X", 3),
    0x4a: ("LSR_ACC", 1),
    0x46: ("LSR_ZERO", 2),
    0x56: ("LSR_ZERO_X", 2),
    0x4e: ("LSR_ABS", 3),
    0x5e: ("LSR_ABS_X", 3),
    0xea: ("NOP", 1),
    0x09: ("ORA_IMM", 2),
    0x05: ("ORA_ZERO", 2),
    0x15: ("ORA_ZERO_X", 2),
    0x0d: ("ORA_ABS", 3),
    0x1d: ("ORA_ABS_X", 3),
    0x19: ("ORA_ABS_Y", 3),
    0x01: ("ORA_IND_X", 2),
    0x11: ("ORA_IND_Y", 2),
    0x48: ("PHA", 1),
    0x08: ("PHP", 1),
    0x68: ("PLA", 1),
    0x28: ("PLP", 1),
    0x2a: ("ROL_ACC", 1),
    0x26: ("ROL_ZERO", 2),
    0x36: ("ROL_ZERO_X", 2),
    0x2e: ("ROL_ABS", 3),
    0x3e: ("ROL_ABS_X", 3),
    0x6a: ("ROR_ACC", 1),
    0x66: ("ROR_ZERO", 2),
    0x76: ("ROR_ZERO_X", 2),
    0x6e: ("ROR_ABS", 3),
    0x7e: ("ROR_ABS_X", 3),
    0x40: ("RTI", 1),
    0x60: ("RTS", 1),
    0xe9: ("SBC_IMM", 2),
    0xe5: ("SBC_ZERO", 2),
    0xf5: ("SBC_ZERO_X", 2),
    0xed: ("SBC_ABS", 3),
    0xfd: ("SBC_ABS_X", 3),
    0xf9: ("SBC_ABS_Y", 3),
    0xe1: ("SBC_IND_X", 2),
    0xf1: ("SBC_IND_Y", 2),
    0x38: ("SEC", 1),
    0xf8: ("SED", 1),
    0x78: ("SEI", 1),
    0x85: ("STA_ZERO", 2),
    0x95: ("STA_ZERO_X", 2),
    0x8d: ("STA_ABS", 3),
    0x9d: ("STA_ABS_X", 3),
    0x99: ("STA_ABS_Y", 3),
    0x81: ("STA_IND_X", 2),
    0x91: ("STA_IND_Y", 2),
    0x86: ("STX_ZERO", 2),
    0x96: ("STX_ZERO_Y", 2),
    0x8e: ("STX_ABS", 3),
    0x84: ("STY_ZERO", 2),
    0x94: ("STY_ZERO_X", 2),
    0x8c: ("STY_ABS", 3),
    0xaa: ("TAX", 1),
    0xa8: ("TAY", 1),
    0xba: ("TSX", 1),
    0x8a: ("TXA", 1),
    0x9a: ("TXS", 1),
    0x98: ("TYA", 1)
}

def unknown(data, idx):
    print(f"0x{offset:04x}: UNKNOWN")

def disasm_24bit_instr(data, idx):
    print(f"0x{offset:04x}: 0x{data[idx]:04x} - {opcodes[data[idx]][0]} 0x{data[idx+2]:x}{data[idx+1]:x}")

def disasm_16bit_instr(data, idx):
    print(f"0x{offset:04x}: 0x{data[idx]:04x} - {opcodes[data[idx]][0]} 0x{data[idx+1]:x}")

def disasm_8bit_instr(data, idx):
    print(f"0x{offset:04x}: 0x{data[idx]:04x} - {opcodes[data[idx]][0]}")

def disasm_unknown(data, idx):
    print(f"0x{offset:04x}: 0x{data[idx]:04x} - UNKNOWN")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("No file path provided.")
        exit(1)

    rom_path = sys.argv[1]
    print(f"Rom {rom_path}")

    with open(rom_path, "rb") as rom:
        data = rom.read()
        data = data[0x10:]
        print(f"{len(data)=}")
        idx = 0
        while idx < len(data):
            (offset, value) = idx, data[idx]

            if value not in opcodes:
                disasm_unknown(data, idx)
                idx += 1
            elif opcodes[value][1] == 1:
                disasm_8bit_instr(data, idx)
                idx += 1
            elif opcodes[value][1] == 2:
                disasm_16bit_instr(data, idx)
                idx += 2
            elif opcodes[value][1] == 3:
                disasm_24bit_instr(data, idx)
                idx += 3
            else:
                raise Exception("Wrong opcode size")