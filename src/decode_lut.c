#include "decode_lut.h"


Instruction opcode_lut[256] = {
    [0x69] = {
        .operate = opcode_ADC,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0x65] = {
        .operate = opcode_ADC,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0x75] = {
        .operate = opcode_ADC,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0x6D] = {
        .operate = opcode_ADC,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0x7D] = {
        .operate = opcode_ADC,
        .addrmode = addrmode_ABSX,
        .cycles = 4
    },
    [0x79] = {
        .operate = opcode_ADC,
        .addrmode = addrmode_ABSY,
        .cycles = 4
    },
    [0x61] = {
        .operate = opcode_ADC,
        .addrmode = addrmode_INDX,
        .cycles = 6
    },
    [0x71] = {
        .operate = opcode_ADC,
        .addrmode = addrmode_INDY,
        .cycles = 5
    },
    // AND
    [0x29] = {
        .operate = opcode_AND,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0x25] = {
        .operate = opcode_AND,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0x35] = {
        .operate = opcode_AND,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0x2D] = {
        .operate = opcode_AND,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0x3D] = {
        .operate = opcode_AND,
        .addrmode = addrmode_ABSX,
        .cycles = 4
    },
    [0x39] = {
        .operate = opcode_AND,
        .addrmode = addrmode_ABSY,
        .cycles = 4
    },
    [0x21] = {
        .operate = opcode_AND,
        .addrmode = addrmode_INDX,
        .cycles = 6
    },
    [0x31] = {
        .operate = opcode_AND,
        .addrmode = addrmode_INDY,
        .cycles = 5
        },
    // ASL
    [0x0A] = {
        .operate = opcode_ASL_A,
        .addrmode = addrmode_IMP,
        .cycles = 2
    },
    [0x06] = {
        .operate = opcode_ASL,
        .addrmode = addrmode_ZP,
        .cycles = 5
    },
    [0x16] = {
        .operate = opcode_ASL,
        .addrmode = addrmode_ZPX,
        .cycles = 6
    },
    [0x0E] = {
        .operate = opcode_ASL,
        .addrmode = addrmode_ABS,
        .cycles = 6
    },
    [0x1E] = {
        .operate = opcode_ASL,
        .addrmode = addrmode_ABSX,
        .cycles = 7
    },
    // BCC
    [0x90] = {
        .operate = opcode_BCC,
        .addrmode = addrmode_REL,
        .cycles = 2
    },
    // BCS
    [0xB0] = {
        .operate = opcode_BCS,
        .addrmode = addrmode_REL,
        .cycles = 2
        },
    // BEQ
    [0xF0] = {
        .operate = opcode_BEQ,
        .addrmode = addrmode_REL,
        .cycles = 2
        },
    // BIT
    [0x24] = {
        .operate = opcode_BIT,
        .addrmode = addrmode_ZP,
        .cycles = 2
    },
    [0x2C] = {
        .operate = opcode_BIT,
        .addrmode = addrmode_ABS,
        .cycles = 3
        },
    // BMI
    [0x30] = {
        .operate = opcode_BMI,
        .addrmode = addrmode_REL,
        .cycles = 2
        },
    // BNE
    [0xD0] = {
        .operate = opcode_BNE,
        .addrmode = addrmode_REL,
        .cycles = 2
        },
    // BPL
    [0x10] = {
        .operate = opcode_BPL,
        .addrmode = addrmode_REL,
        .cycles = 2
        },
    // BRK
    [0x00] = {
        .operate  = opcode_BRK,
        .addrmode = addrmode_IMP,
        .cycles = 7
        },
    // BVC
    [0x50] = {
        .operate = opcode_BVC,
        .addrmode = addrmode_REL,
        .cycles = 2
        },
    // BVS
    [0x70] = {
        .operate = opcode_BVS,
        .addrmode = addrmode_REL,
        .cycles = 2
        },
    // CLC
    [0x18] = {
        .operate = opcode_CLC,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    // CLD
    [0xD8] = {
        .operate = opcode_CLD,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    // CLI
    [0x58] = {
        .operate = opcode_CLI,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    // CLV
    [0xB8] = {
        .operate = opcode_CLV,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    // CMP
    [0xC9] = {
        .operate = opcode_CMP,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0xC5] = {
        .operate = opcode_CMP,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0xD5] = {
        .operate = opcode_CMP,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0xCD] = {
        .operate = opcode_CMP,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0xDD] = {
        .operate = opcode_CMP,
        .addrmode = addrmode_ABSX,
        .cycles = 4
    },
    [0xD9] = {
        .operate = opcode_CMP,
        .addrmode = addrmode_ABSY,
        .cycles = 4
    },
    [0xC1] = {
        .operate = opcode_CMP,
        .addrmode = addrmode_INDX,
        .cycles = 6
    },
    [0xD1] = {
        .operate = opcode_CMP,
        .addrmode = addrmode_INDY,
        .cycles = 5
        },
    //CPX
    [0xE0] = {
        .operate = opcode_CPX,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0xE4] = {
        .operate = opcode_CPX,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0xEC] = {
        .operate = opcode_CPX,
        .addrmode = addrmode_ABS,
        .cycles = 4
        },
    //CPY
    [0xC0] = {
        .operate = opcode_CPY,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0xC4] = {
        .operate = opcode_CPY,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0xCC] = {
        .operate = opcode_CPY,
        .addrmode = addrmode_ABS,
        .cycles = 4
        },
    //DEC
    [0xC6] = {
        .operate = opcode_DEC,
        .addrmode = addrmode_ZP,
        .cycles = 5
    },
    [0xD6] = {
        .operate = opcode_DEC,
        .addrmode = addrmode_ZPX,
        .cycles = 6
    },
    [0xCE] = {
        .operate = opcode_DEC,
        .addrmode = addrmode_ABS,
        .cycles = 6
    },
    [0xDE] = {
        .operate = opcode_DEC,
        .addrmode = addrmode_ABSX,
        .cycles = 7
        },
    //DEX
    [0xCA] = {
        .operate = opcode_DEX,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    //DEY
    [0x88] = {
        .operate = opcode_DEY,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    //EOR
    [0x49] = {
        .operate = opcode_EOR,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0x45] = {
        .operate = opcode_EOR,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0x55] = {
        .operate = opcode_EOR,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0x4D] = {
        .operate = opcode_EOR,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0x5D] = {
        .operate = opcode_EOR,
        .addrmode = addrmode_ABSX,
        .cycles = 4
    },
    [0x59] = {
        .operate = opcode_EOR,
        .addrmode = addrmode_ABSY,
        .cycles = 4
    },
    [0x41] = {
        .operate = opcode_EOR,
        .addrmode = addrmode_INDX,
        .cycles = 6
    },
    [0x51] = {
        .operate = opcode_EOR,
        .addrmode = addrmode_INDY,
        .cycles = 5
        },
    //INC
    [0xE6] = {
        .operate = opcode_INC,
        .addrmode = addrmode_ZP,
        .cycles = 5
    },
    [0xF6] = {
        .operate = opcode_INC,
        .addrmode = addrmode_ZPX,
        .cycles = 6
    },
    [0xEE] = {
        .operate = opcode_INC,
        .addrmode = addrmode_ABS,
        .cycles = 6
    },
    [0xFE] = {
        .operate = opcode_INC,
        .addrmode = addrmode_ABSX,
        .cycles = 7
        },
    //INX
    [0xE8] = {
        .operate = opcode_INX,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    //INY
    [0xC8] = {
        .operate = opcode_INY,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    //JMP
    [0x4C] = {
        .operate = opcode_JMP,
        .addrmode = addrmode_ABS,
        .cycles = 3
    },
    [0x6C] = {
        .operate = opcode_JMP,
        .addrmode = addrmode_IND,
        .cycles = 5
        },
    //JSR
    [0x20] = {
        .operate = opcode_JSR,
        .addrmode = addrmode_ABS,
        .cycles = 6
        },
    //LDA
    [0xA9] = {
        .operate = opcode_LDA,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0xA5] = {
        .operate = opcode_LDA,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0xB5] = {
        .operate = opcode_LDA,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0xAD] = {
        .operate = opcode_LDA,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0xBD] = {
        .operate = opcode_LDA,
        .addrmode = addrmode_ABSX,
        .cycles = 4
    },
    [0xB9] = {
        .operate = opcode_LDA,
        .addrmode = addrmode_ABSY,
        .cycles = 4
    },
    [0xA1] = {
        .operate = opcode_LDA,
        .addrmode = addrmode_INDX,
        .cycles = 6
    },
    [0xB1] = {
        .operate = opcode_LDA,
        .addrmode = addrmode_INDY,
        .cycles = 5
        },
    // LDX
    [0xA2] = {
        .operate = opcode_LDX,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0xA6] = {
        .operate = opcode_LDX,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0xB6] = {
        .operate = opcode_LDX,
        .addrmode = addrmode_ZPY,
        .cycles = 4
    },
    [0xAE] = {
        .operate = opcode_LDX,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0xBE] = {
        .operate = opcode_LDX,
        .addrmode = addrmode_ABSY,
        .cycles = 4
        },
    // LDY
    [0xA0] = {
        .operate = opcode_LDY,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0xA4] = {
        .operate = opcode_LDY,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0xB4] = {
        .operate = opcode_LDY,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0xAC] = {
        .operate = opcode_LDY,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0xBC] = {
        .operate = opcode_LDY,
        .addrmode = addrmode_ABSX,
        .cycles = 4
        },
    // LSR
    [0x4A] = {
        .operate = opcode_LSR_A,
        .addrmode = addrmode_IMP,
        .cycles = 2
    },
    [0x46] = {
        .operate = opcode_LSR,
        .addrmode = addrmode_ZP,
        .cycles = 5
    },
    [0x56] = {
        .operate = opcode_LSR,
        .addrmode = addrmode_ZPX,
        .cycles = 6
    },
    [0x4E] = {
        .operate = opcode_LSR,
        .addrmode = addrmode_ABS,
        .cycles = 6
    },
    [0x5E] = {
        .operate = opcode_LSR,
        .addrmode = addrmode_ABSX,
        .cycles = 7
        },
    // NOP
    [0xEA] = {
        .operate = opcode_NOP,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    // ORA
    [0x09] = {
        .operate = opcode_ORA,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0x05] = {
        .operate = opcode_ORA,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0x15] = {
        .operate = opcode_ORA,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0x0D] = {
        .operate = opcode_ORA,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0x1D] = {
        .operate = opcode_ORA,
        .addrmode = addrmode_ABSX,
        .cycles = 4
    },
    [0x19] = {
        .operate = opcode_ORA,
        .addrmode = addrmode_ABSY,
        .cycles = 4
    },
    [0x01] = {
        .operate = opcode_ORA,
        .addrmode = addrmode_INDX,
        .cycles = 6
    },
    [0x11] = {
        .operate = opcode_ORA,
        .addrmode = addrmode_INDY,
        .cycles = 5
        },
    // PHA
    [0x48] = {
        .operate = opcode_PHA,
        .addrmode = addrmode_IMP,
        .cycles = 3
        },
    // PHP
    [0x08] = {
        .operate = opcode_PHP,
        .addrmode = addrmode_IMP,
        .cycles = 3
        },
    // PLA
    [0x68] = {
        .operate = opcode_PLA,
        .addrmode = addrmode_IMP,
        .cycles = 4
        },
    // PLP
    [0x28] = {
        .operate = opcode_PLP,
        .addrmode = addrmode_IMP,
        .cycles = 4
        },
    // ROL
    [0x2A] = {
        .operate = opcode_ROL_A,
        .addrmode = addrmode_IMP,
        .cycles = 2
    },
    [0x26] = {
        .operate = opcode_ROL,
        .addrmode = addrmode_ZP,
        .cycles = 5
    },
    [0x36] = {
        .operate = opcode_ROL,
        .addrmode = addrmode_ZPX,
        .cycles = 6
    },
    [0x2E] = {
        .operate = opcode_ROL,
        .addrmode = addrmode_ABS,
        .cycles = 6
    },
    [0x3E] = {
        .operate = opcode_ROL,
        .addrmode = addrmode_ABSX,
        .cycles = 7
        },
    // ROR
    [0x6A] = {
        .operate = opcode_ROR_A,
        .addrmode = addrmode_IMP,
        .cycles = 2
    },
    [0x66] = {
        .operate = opcode_ROR,
        .addrmode = addrmode_ZP,
        .cycles = 5
    },
    [0x76] = {
        .operate = opcode_ROR,
        .addrmode = addrmode_ZPX,
        .cycles = 6
    },
    [0x6E] = {
        .operate = opcode_ROR,
        .addrmode = addrmode_ABS,
        .cycles = 6
    },
    [0x7E] = {
        .operate = opcode_ROR,
        .addrmode = addrmode_ABSX,
        .cycles = 7
        },
    // RTI
    [0x40] = {
        .operate = opcode_RTI,
        .addrmode = addrmode_IMP,
        .cycles = 6
        },
    // RTS
    [0x60] = {
        .operate = opcode_RTS,
        .addrmode = addrmode_IMP,
        .cycles = 6
        },
    // SBC
    [0xE9] = {
        .operate = opcode_SBC,
        .addrmode = addrmode_IMM,
        .cycles = 2
    },
    [0xE5] = {
        .operate = opcode_SBC,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0xF5] = {
        .operate = opcode_SBC,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0xED] = {
        .operate = opcode_SBC,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0xFD] = {
        .operate = opcode_SBC,
        .addrmode = addrmode_ABSX,
        .cycles = 4
    },
    [0xF9] = {
        .operate = opcode_SBC,
        .addrmode = addrmode_ABSY,
        .cycles = 4
    },
    [0xE1] = {
        .operate = opcode_SBC,
        .addrmode = addrmode_INDX,
        .cycles = 6
    },
    [0xF1] = {
        .operate = opcode_SBC,
        .addrmode = addrmode_INDY,
        .cycles = 5
        },
    // SEC
    [0x38] = {
        .operate = opcode_SEC,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    // SED
    [0xF8] = {
        .operate = opcode_SED,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    // SEI
    [0x78] = {
        .operate = opcode_SEI,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    // STA
    [0x85] = {
        .operate = opcode_STA,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0x95] = {
        .operate = opcode_STA,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0x8D] = {
        .operate = opcode_STA,
        .addrmode = addrmode_ABS,
        .cycles = 4
    },
    [0x9D] = {
        .operate = opcode_STA,
        .addrmode = addrmode_ABSX,
        .cycles = 5
    },
    [0x99] = {
        .operate = opcode_STA,
        .addrmode = addrmode_ABSY,
        .cycles = 5
    },
    [0x81] = {
        .operate = opcode_STA,
        .addrmode = addrmode_INDX,
        .cycles = 6
    },
    [0x91] = {
        .operate = opcode_STA,
        .addrmode = addrmode_INDY,
        .cycles = 6
        },
    // STX
    [0x86] = {
        .operate = opcode_STX,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0x96] = {
        .operate = opcode_STX,
        .addrmode = addrmode_ZPY,
        .cycles = 4
    },
    [0x8E] = {
        .operate = opcode_STX,
        .addrmode = addrmode_ABS,
        .cycles = 4
        },
    // STY
    [0x84] = {
        .operate = opcode_STY,
        .addrmode = addrmode_ZP,
        .cycles = 3
    },
    [0x94] = {
        .operate = opcode_STY,
        .addrmode = addrmode_ZPX,
        .cycles = 4
    },
    [0x8C] = {
        .operate = opcode_STY,
        .addrmode = addrmode_ABS,
        .cycles = 4
        },
    //TAX
    [0xAA] = {
        .operate = opcode_TAX,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    //TAY
    [0xA8] = {
        .operate = opcode_TAY,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    //TSX
    [0xBA] = {
        .operate = opcode_TSX,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    //TXA
    [0x8A] = {
        .operate = opcode_TXA,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    //TXS
    [0x9A] = {
        .operate = opcode_TXS,
        .addrmode = addrmode_IMP,
        .cycles = 2
        },
    //TYA
    [0x98] = {
        .operate = opcode_TYA,
        .addrmode = addrmode_IMP,
        .cycles = 2
    }
};

Instruction get_instruction(uint8_t idx){
    return opcode_lut[idx];
}

