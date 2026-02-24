#include "decode_lut.h"


Instruction opcode_lut[256];

void decode_lut_init(CpuStateTypedef* cpu){
    for(int i=0;i<256;i++){
        opcode_lut[i].operate = opcode_ILL;
        opcode_lut[i].addrmode = addrmode_IMP;
        opcode_lut[i].cycles = 0;
    }
    // ADC
    opcode_lut[0x69].operate = opcode_ADC;
    opcode_lut[0x69].addrmode = addrmode_IMM;
    opcode_lut[0x69].cycles = 2;

    opcode_lut[0x65].operate = opcode_ADC;
    opcode_lut[0x65].addrmode = addrmode_ZP;
    opcode_lut[0x65].cycles = 3;

    opcode_lut[0x75].operate = opcode_ADC;
    opcode_lut[0x75].addrmode = addrmode_ZPX;
    opcode_lut[0x75].cycles = 4;

    opcode_lut[0x6D].operate = opcode_ADC;
    opcode_lut[0x6D].addrmode = addrmode_ABS;
    opcode_lut[0x6D].cycles = 4;

    opcode_lut[0x7D].operate = opcode_ADC;
    opcode_lut[0x7D].addrmode = addrmode_ABSX;
    opcode_lut[0x7D].cycles = 4;

    opcode_lut[0x79].operate = opcode_ADC;
    opcode_lut[0x79].addrmode = addrmode_ABSY;
    opcode_lut[0x79].cycles = 4;

    opcode_lut[0x61].operate = opcode_ADC;
    opcode_lut[0x61].addrmode = addrmode_INDX;
    opcode_lut[0x61].cycles = 6;

    opcode_lut[0x71].operate = opcode_ADC;
    opcode_lut[0x71].addrmode = addrmode_INDY;
    opcode_lut[0x71].cycles = 5;
    // AND
    opcode_lut[0x29].operate = opcode_AND;
    opcode_lut[0x29].addrmode = addrmode_IMM;
    opcode_lut[0x29].cycles = 2;

    opcode_lut[0x25].operate = opcode_AND;
    opcode_lut[0x25].addrmode = addrmode_ZP;
    opcode_lut[0x25].cycles = 3;

    opcode_lut[0x35].operate = opcode_AND;
    opcode_lut[0x35].addrmode = addrmode_ZPX;
    opcode_lut[0x35].cycles = 4;

    opcode_lut[0x2D].operate = opcode_AND;
    opcode_lut[0x2D].addrmode = addrmode_ABS;
    opcode_lut[0x2D].cycles = 4;

    opcode_lut[0x3D].operate = opcode_AND;
    opcode_lut[0x3D].addrmode = addrmode_ABSX;
    opcode_lut[0x3D].cycles = 4;

    opcode_lut[0x39].operate = opcode_AND;
    opcode_lut[0x39].addrmode = addrmode_ABSY;
    opcode_lut[0x39].cycles = 4;

    opcode_lut[0x21].operate = opcode_AND;
    opcode_lut[0x21].addrmode = addrmode_INDX;
    opcode_lut[0x21].cycles = 6;

    opcode_lut[0x31].operate = opcode_AND;
    opcode_lut[0x31].addrmode = addrmode_INDY;
    opcode_lut[0x31].cycles = 5;
    // ASL
    opcode_lut[0x0A].operate = opcode_ASL_A;
    opcode_lut[0x0A].addrmode = addrmode_IMP;
    opcode_lut[0x0A].cycles = 2;

    opcode_lut[0x06].operate = opcode_ASL;
    opcode_lut[0x06].addrmode = addrmode_ZP;
    opcode_lut[0x06].cycles = 5;

    opcode_lut[0x16].operate = opcode_ASL;
    opcode_lut[0x16].addrmode = addrmode_ZPX;
    opcode_lut[0x16].cycles = 6;

    opcode_lut[0x0E].operate = opcode_ASL;
    opcode_lut[0x0E].addrmode = addrmode_ABS;
    opcode_lut[0x0E].cycles = 6;

    opcode_lut[0x1E].operate = opcode_ASL;
    opcode_lut[0x1E].addrmode = addrmode_ABSX;
    opcode_lut[0x1E].cycles = 7;
    // BCC
    opcode_lut[0x90].operate = opcode_BCC;
    opcode_lut[0x90].addrmode = addrmode_REL;
    opcode_lut[0x90].cycles = 2;
    // BCS
    opcode_lut[0xB0].operate = opcode_BCS;
    opcode_lut[0xB0].addrmode = addrmode_REL;
    opcode_lut[0xB0].cycles = 2;
    // BEQ
    opcode_lut[0xF0].operate = opcode_BEQ;
    opcode_lut[0xF0].addrmode = addrmode_REL;
    opcode_lut[0xF0].cycles = 2;
    // BIT
    opcode_lut[0x24].operate = opcode_BIT;
    opcode_lut[0x24].addrmode = addrmode_ZP;
    opcode_lut[0x24].cycles = 2;

    opcode_lut[0x2C].operate = opcode_BIT;
    opcode_lut[0x2C].addrmode = addrmode_ABS;
    opcode_lut[0x2C].cycles = 3;
    // BMI
    opcode_lut[0x30].operate = opcode_BMI;
    opcode_lut[0x30].addrmode = addrmode_REL;
    opcode_lut[0x30].cycles = 2;
    // BNE
    opcode_lut[0xD0].operate = opcode_BNE;
    opcode_lut[0xD0].addrmode = addrmode_REL;
    opcode_lut[0xD0].cycles = 2;
    // BPL
    opcode_lut[0x10].operate = opcode_BPL;
    opcode_lut[0x10].addrmode = addrmode_REL;
    opcode_lut[0x10].cycles = 2;
    // BRK
    opcode_lut[0x00].operate  = opcode_BRK;
    opcode_lut[0x00].addrmode = addrmode_IMP;
    opcode_lut[0x00].cycles = 7;
    // BVC
    opcode_lut[0x50].operate = opcode_BVC;
    opcode_lut[0x50].addrmode = addrmode_REL;
    opcode_lut[0x50].cycles = 2;
    // BVS
    opcode_lut[0x70].operate = opcode_BVS;
    opcode_lut[0x70].addrmode = addrmode_REL;
    opcode_lut[0x70].cycles = 2;
    // CLC
    opcode_lut[0x18].operate = opcode_CLC;
    opcode_lut[0x18].addrmode = addrmode_IMP;
    opcode_lut[0x18].cycles = 2;
    // CLD
    opcode_lut[0xD8].operate = opcode_CLD;
    opcode_lut[0xD8].addrmode = addrmode_IMP;
    opcode_lut[0xD8].cycles = 2;
    // CLI
    opcode_lut[0x58].operate = opcode_CLI;
    opcode_lut[0x58].addrmode = addrmode_IMP;
    opcode_lut[0x58].cycles = 2;
    // CLV
    opcode_lut[0xB8].operate = opcode_CLV;
    opcode_lut[0xB8].addrmode = addrmode_IMP;
    opcode_lut[0xB8].cycles = 2;
    // CMP
    opcode_lut[0xC9].operate = opcode_CMP;
    opcode_lut[0xC9].addrmode = addrmode_IMM;
    opcode_lut[0xC9].cycles = 2;

    opcode_lut[0xC5].operate = opcode_CMP;
    opcode_lut[0xC5].addrmode = addrmode_ZP;
    opcode_lut[0xC5].cycles = 3;

    opcode_lut[0xD5].operate = opcode_CMP;
    opcode_lut[0xD5].addrmode = addrmode_ZPX;
    opcode_lut[0xD5].cycles = 4;

    opcode_lut[0xCD].operate = opcode_CMP;
    opcode_lut[0xCD].addrmode = addrmode_ABS;
    opcode_lut[0xCD].cycles = 4;

    opcode_lut[0xDD].operate = opcode_CMP;
    opcode_lut[0xDD].addrmode = addrmode_ABSX;
    opcode_lut[0xDD].cycles = 4;

    opcode_lut[0xD9].operate = opcode_CMP;
    opcode_lut[0xD9].addrmode = addrmode_ABSY;
    opcode_lut[0xD9].cycles = 4;

    opcode_lut[0xC1].operate = opcode_CMP;
    opcode_lut[0xC1].addrmode = addrmode_INDX;
    opcode_lut[0xC1].cycles = 6;

    opcode_lut[0xD1].operate = opcode_CMP;
    opcode_lut[0xD1].addrmode = addrmode_INDY;
    opcode_lut[0xD1].cycles = 5;
    //CPX
    opcode_lut[0xE0].operate = opcode_CPX;
    opcode_lut[0xE0].addrmode = addrmode_IMM;
    opcode_lut[0xE0].cycles = 2;

    opcode_lut[0xE4].operate = opcode_CPX;
    opcode_lut[0xE4].addrmode = addrmode_ZP;
    opcode_lut[0xE4].cycles = 3;

    opcode_lut[0xEC].operate = opcode_CPX;
    opcode_lut[0xEC].addrmode = addrmode_ABS;
    opcode_lut[0xEC].cycles = 4;
    //CPY
    opcode_lut[0xC0].operate = opcode_CPY;
    opcode_lut[0xC0].addrmode = addrmode_IMM;
    opcode_lut[0xC0].cycles = 2;

    opcode_lut[0xC4].operate = opcode_CPY;
    opcode_lut[0xC4].addrmode = addrmode_ZP;
    opcode_lut[0xC4].cycles = 3;

    opcode_lut[0xCC].operate = opcode_CPY;
    opcode_lut[0xCC].addrmode = addrmode_ABS;
    opcode_lut[0xCC].cycles = 4;
    //DEC
    opcode_lut[0xC6].operate = opcode_DEC;
    opcode_lut[0xC6].addrmode = addrmode_ZP;
    opcode_lut[0xC6].cycles = 5;

    opcode_lut[0xD6].operate = opcode_DEC;
    opcode_lut[0xD6].addrmode = addrmode_ZPX;
    opcode_lut[0xD6].cycles = 6;

    opcode_lut[0xCE].operate = opcode_DEC;
    opcode_lut[0xCE].addrmode = addrmode_ABS;
    opcode_lut[0xCE].cycles = 6;

    opcode_lut[0xDE].operate = opcode_DEC;
    opcode_lut[0xDE].addrmode = addrmode_ABSX;
    opcode_lut[0xDE].cycles = 7;
    //DEX
    opcode_lut[0xCA].operate = opcode_DEX;
    opcode_lut[0xCA].addrmode = addrmode_IMP;
    opcode_lut[0xCA].cycles = 2;
    //DEY
    opcode_lut[0x88].operate = opcode_DEY;
    opcode_lut[0x88].addrmode = addrmode_IMP;
    opcode_lut[0x88].cycles = 2;
    //EOR
    opcode_lut[0x49].operate = opcode_EOR;
    opcode_lut[0x49].addrmode = addrmode_IMM;
    opcode_lut[0x49].cycles = 2;

    opcode_lut[0x45].operate = opcode_EOR;
    opcode_lut[0x45].addrmode = addrmode_ZP;
    opcode_lut[0x45].cycles = 3;

    opcode_lut[0x55].operate = opcode_EOR;
    opcode_lut[0x55].addrmode = addrmode_ZPX;
    opcode_lut[0x55].cycles = 4;

    opcode_lut[0x4D].operate = opcode_EOR;
    opcode_lut[0x4D].addrmode = addrmode_ABS;
    opcode_lut[0x4D].cycles = 4;

    opcode_lut[0x5D].operate = opcode_EOR;
    opcode_lut[0x5D].addrmode = addrmode_ABSX;
    opcode_lut[0x5D].cycles = 4;

    opcode_lut[0x59].operate = opcode_EOR;
    opcode_lut[0x59].addrmode = addrmode_ABSY;
    opcode_lut[0x59].cycles = 4;

    opcode_lut[0x41].operate = opcode_EOR;
    opcode_lut[0x41].addrmode = addrmode_INDX;
    opcode_lut[0x41].cycles = 6;

    opcode_lut[0x51].operate = opcode_EOR;
    opcode_lut[0x51].addrmode = addrmode_INDY;
    opcode_lut[0x51].cycles = 5;
    //INC
    opcode_lut[0xE6].operate = opcode_INC;
    opcode_lut[0xE6].addrmode = addrmode_ZP;
    opcode_lut[0xE6].cycles = 5;

    opcode_lut[0xF6].operate = opcode_INC;
    opcode_lut[0xF6].addrmode = addrmode_ZPX;
    opcode_lut[0xF6].cycles = 6;

    opcode_lut[0xEE].operate = opcode_INC;
    opcode_lut[0xEE].addrmode = addrmode_ABS;
    opcode_lut[0xEE].cycles = 6;

    opcode_lut[0xFE].operate = opcode_INC;
    opcode_lut[0xFE].addrmode = addrmode_ABSX;
    opcode_lut[0xFE].cycles = 7;
    //INX
    opcode_lut[0xE8].operate = opcode_INX;
    opcode_lut[0xE8].addrmode = addrmode_IMP;
    opcode_lut[0xE8].cycles = 2;
    //INY
    opcode_lut[0xC8].operate = opcode_INY;
    opcode_lut[0xC8].addrmode = addrmode_IMP;
    opcode_lut[0xC8].cycles = 2;
    //JMP
    opcode_lut[0x4C].operate = opcode_JMP;
    opcode_lut[0x4C].addrmode = addrmode_ABS;
    opcode_lut[0x4C].cycles = 3;

    opcode_lut[0x6C].operate = opcode_JMP;
    opcode_lut[0x6C].addrmode = addrmode_IND;
    opcode_lut[0x6C].cycles = 5;
    //JSR
    opcode_lut[0x20].operate = opcode_JSR;
    opcode_lut[0x20].addrmode = addrmode_ABS;
    opcode_lut[0x20].cycles = 6;
    //LDA
    opcode_lut[0xA9].operate = opcode_LDA;
    opcode_lut[0xA9].addrmode = addrmode_IMM;
    opcode_lut[0xA9].cycles = 2;

    opcode_lut[0xA5].operate = opcode_LDA;
    opcode_lut[0xA5].addrmode = addrmode_ZP;
    opcode_lut[0xA5].cycles = 3;

    opcode_lut[0xB5].operate = opcode_LDA;
    opcode_lut[0xB5].addrmode = addrmode_ZPX;
    opcode_lut[0xB5].cycles = 4;

    opcode_lut[0xAD].operate = opcode_LDA;
    opcode_lut[0xAD].addrmode = addrmode_ABS;
    opcode_lut[0xAD].cycles = 4;

    opcode_lut[0xBD].operate = opcode_LDA;
    opcode_lut[0xBD].addrmode = addrmode_ABSX;
    opcode_lut[0xBD].cycles = 4;

    opcode_lut[0xB9].operate = opcode_LDA;
    opcode_lut[0xB9].addrmode = addrmode_ABSY;
    opcode_lut[0xB9].cycles = 4;

    opcode_lut[0xA1].operate = opcode_LDA;
    opcode_lut[0xA1].addrmode = addrmode_INDX;
    opcode_lut[0xA1].cycles = 6;

    opcode_lut[0xB1].operate = opcode_LDA;
    opcode_lut[0xB1].addrmode = addrmode_INDY;
    opcode_lut[0xB1].cycles = 5;
    // LDX
    opcode_lut[0xA2].operate = opcode_LDX;
    opcode_lut[0xA2].addrmode = addrmode_IMM;
    opcode_lut[0xA2].cycles = 2;

    opcode_lut[0xA6].operate = opcode_LDX;
    opcode_lut[0xA6].addrmode = addrmode_ZP;
    opcode_lut[0xA6].cycles = 3;

    opcode_lut[0xB6].operate = opcode_LDX;
    opcode_lut[0xB6].addrmode = addrmode_ZPY;
    opcode_lut[0xB6].cycles = 4;

    opcode_lut[0xAE].operate = opcode_LDX;
    opcode_lut[0xAE].addrmode = addrmode_ABS;
    opcode_lut[0xAE].cycles = 4;

    opcode_lut[0xBE].operate = opcode_LDX;
    opcode_lut[0xBE].addrmode = addrmode_ABSY;
    opcode_lut[0xBE].cycles = 4;
    // LDY
    opcode_lut[0xA0].operate = opcode_LDY;
    opcode_lut[0xA0].addrmode = addrmode_IMM;
    opcode_lut[0xA0].cycles = 2;

    opcode_lut[0xA4].operate = opcode_LDY;
    opcode_lut[0xA4].addrmode = addrmode_ZP;
    opcode_lut[0xA4].cycles = 3;

    opcode_lut[0xB4].operate = opcode_LDY;
    opcode_lut[0xB4].addrmode = addrmode_ZPY;
    opcode_lut[0xB4].cycles = 4;

    opcode_lut[0xAC].operate = opcode_LDY;
    opcode_lut[0xAC].addrmode = addrmode_ABS;
    opcode_lut[0xAC].cycles = 4;

    opcode_lut[0xBC].operate = opcode_LDY;
    opcode_lut[0xBC].addrmode = addrmode_ABSY;
    opcode_lut[0xBC].cycles = 4;
    // LSR
    opcode_lut[0x4A].operate = opcode_LSR_A;
    opcode_lut[0x4A].addrmode = addrmode_IMP;
    opcode_lut[0x4A].cycles = 2;

    opcode_lut[0x46].operate = opcode_LSR;
    opcode_lut[0x46].addrmode = addrmode_ZP;
    opcode_lut[0x46].cycles = 5;

    opcode_lut[0x56].operate = opcode_LSR;
    opcode_lut[0x56].addrmode = addrmode_ZPX;
    opcode_lut[0x56].cycles = 6;

    opcode_lut[0x4E].operate = opcode_LSR;
    opcode_lut[0x4E].addrmode = addrmode_ABS;
    opcode_lut[0x4E].cycles = 6;

    opcode_lut[0x5E].operate = opcode_LSR;
    opcode_lut[0x5E].addrmode = addrmode_ABSX;
    opcode_lut[0x5E].cycles = 7;
    // NOP
    opcode_lut[0xEA].operate = opcode_NOP;
    opcode_lut[0xEA].addrmode = addrmode_IMP;
    opcode_lut[0xEA].cycles = 2;
    // ORA
    opcode_lut[0x09].operate = opcode_ORA;
    opcode_lut[0x09].addrmode = addrmode_IMM;
    opcode_lut[0x09].cycles = 2;

    opcode_lut[0x05].operate = opcode_ORA;
    opcode_lut[0x05].addrmode = addrmode_ZP;
    opcode_lut[0x05].cycles = 3;

    opcode_lut[0x15].operate = opcode_ORA;
    opcode_lut[0x15].addrmode = addrmode_ZPX;
    opcode_lut[0x15].cycles = 4;

    opcode_lut[0x0D].operate = opcode_ORA;
    opcode_lut[0x0D].addrmode = addrmode_ABS;
    opcode_lut[0x0D].cycles = 4;

    opcode_lut[0x1D].operate = opcode_ORA;
    opcode_lut[0x1D].addrmode = addrmode_ABSX;
    opcode_lut[0x1D].cycles = 4;

    opcode_lut[0x19].operate = opcode_ORA;
    opcode_lut[0x19].addrmode = addrmode_ABSY;
    opcode_lut[0x19].cycles = 4;

    opcode_lut[0x01].operate = opcode_ORA;
    opcode_lut[0x01].addrmode = addrmode_INDX;
    opcode_lut[0x01].cycles = 6;

    opcode_lut[0x11].operate = opcode_ORA;
    opcode_lut[0x11].addrmode = addrmode_INDY;
    opcode_lut[0x11].cycles = 5;
    // PHA
    opcode_lut[0x48].operate = opcode_PHA;
    opcode_lut[0x48].addrmode = addrmode_IMP;
    opcode_lut[0x48].cycles = 3;
    // PHP
    opcode_lut[0x08].operate = opcode_PHP;
    opcode_lut[0x08].addrmode = addrmode_IMP;
    opcode_lut[0x08].cycles = 3;
    // PLA
    opcode_lut[0x68].operate = opcode_PLA;
    opcode_lut[0x68].addrmode = addrmode_IMP;
    opcode_lut[0x68].cycles = 4;
    // PLP
    opcode_lut[0x28].operate = opcode_PLP;
    opcode_lut[0x28].addrmode = addrmode_IMP;
    opcode_lut[0x28].cycles = 4;
    // ROL
    opcode_lut[0x2A].operate = opcode_ROL_A;
    opcode_lut[0x2A].addrmode = addrmode_IMP;
    opcode_lut[0x2A].cycles = 2;

    opcode_lut[0x26].operate = opcode_ROL;
    opcode_lut[0x26].addrmode = addrmode_ZP;
    opcode_lut[0x26].cycles = 5;

    opcode_lut[0x36].operate = opcode_ROL;
    opcode_lut[0x36].addrmode = addrmode_ZPX;
    opcode_lut[0x36].cycles = 6;

    opcode_lut[0x2E].operate = opcode_ROL;
    opcode_lut[0x2E].addrmode = addrmode_ABS;
    opcode_lut[0x2E].cycles = 6;

    opcode_lut[0x3E].operate = opcode_ROL;
    opcode_lut[0x3E].addrmode = addrmode_ABSX;
    opcode_lut[0x3E].cycles = 7;
    // ROR
    opcode_lut[0x6A].operate = opcode_ROR_A;
    opcode_lut[0x6A].addrmode = addrmode_IMP;
    opcode_lut[0x6A].cycles = 2;

    opcode_lut[0x66].operate = opcode_ROR;
    opcode_lut[0x66].addrmode = addrmode_ZP;
    opcode_lut[0x66].cycles = 5;

    opcode_lut[0x76].operate = opcode_ROR;
    opcode_lut[0x76].addrmode = addrmode_ZPX;
    opcode_lut[0x76].cycles = 6;

    opcode_lut[0x6E].operate = opcode_ROR;
    opcode_lut[0x6E].addrmode = addrmode_ABS;
    opcode_lut[0x6E].cycles = 6;

    opcode_lut[0x7E].operate = opcode_ROR;
    opcode_lut[0x7E].addrmode = addrmode_ABSX;
    opcode_lut[0x7E].cycles = 7;
    // RTI
    opcode_lut[0x40].operate = opcode_RTI;
    opcode_lut[0x40].addrmode = addrmode_IMP;
    opcode_lut[0x40].cycles = 6;
    // RTS
    opcode_lut[0x60].operate = opcode_RTS;
    opcode_lut[0x60].addrmode = addrmode_IMP;
    opcode_lut[0x60].cycles = 6;
    // SBC
    opcode_lut[0xE9].operate = opcode_SBC;
    opcode_lut[0xE9].addrmode = addrmode_IMM;
    opcode_lut[0xE9].cycles = 2;

    opcode_lut[0xE5].operate = opcode_SBC;
    opcode_lut[0xE5].addrmode = addrmode_ZP;
    opcode_lut[0xE5].cycles = 3;

    opcode_lut[0xF5].operate = opcode_SBC;
    opcode_lut[0xF5].addrmode = addrmode_ZPX;
    opcode_lut[0xF5].cycles = 4;

    opcode_lut[0xED].operate = opcode_SBC;
    opcode_lut[0xED].addrmode = addrmode_ABS;
    opcode_lut[0xED].cycles = 4;

    opcode_lut[0xFD].operate = opcode_SBC;
    opcode_lut[0xFD].addrmode = addrmode_ABSX;
    opcode_lut[0xFD].cycles = 4;

    opcode_lut[0xF9].operate = opcode_SBC;
    opcode_lut[0xF9].addrmode = addrmode_ABSY;
    opcode_lut[0xF9].cycles = 4;

    opcode_lut[0xE1].operate = opcode_SBC;
    opcode_lut[0xE1].addrmode = addrmode_INDX;
    opcode_lut[0xE1].cycles = 6;

    opcode_lut[0xF1].operate = opcode_SBC;
    opcode_lut[0xF1].addrmode = addrmode_INDY;
    opcode_lut[0xF1].cycles = 5;
    // SEC
    opcode_lut[0x38].operate = opcode_SEC;
    opcode_lut[0x38].addrmode = addrmode_IMP;
    opcode_lut[0x38].cycles = 2;
    // SED
    opcode_lut[0xF8].operate = opcode_SED;
    opcode_lut[0xF8].addrmode = addrmode_IMP;
    opcode_lut[0xF8].cycles = 2;
    // SEI
    opcode_lut[0x78].operate = opcode_SEI;
    opcode_lut[0x78].addrmode = addrmode_IMP;
    opcode_lut[0x78].cycles = 2;
    // STA
    opcode_lut[0x85].operate = opcode_STA;
    opcode_lut[0x85].addrmode = addrmode_ZP;
    opcode_lut[0x85].cycles = 3;

    opcode_lut[0x95].operate = opcode_STA;
    opcode_lut[0x95].addrmode = addrmode_ZPX;
    opcode_lut[0x95].cycles = 4;

    opcode_lut[0x8D].operate = opcode_STA;
    opcode_lut[0x8D].addrmode = addrmode_ABS;
    opcode_lut[0x8D].cycles = 4;

    opcode_lut[0x9D].operate = opcode_STA;
    opcode_lut[0x9D].addrmode = addrmode_ABSX;
    opcode_lut[0x9D].cycles = 5;

    opcode_lut[0x99].operate = opcode_STA;
    opcode_lut[0x99].addrmode = addrmode_ABSY;
    opcode_lut[0x99].cycles = 5;

    opcode_lut[0x81].operate = opcode_STA;
    opcode_lut[0x81].addrmode = addrmode_INDX;
    opcode_lut[0x81].cycles = 6;

    opcode_lut[0x91].operate = opcode_STA;
    opcode_lut[0x91].addrmode = addrmode_INDY;
    opcode_lut[0x91].cycles = 6;
    // STX
    opcode_lut[0x86].operate = opcode_STX;
    opcode_lut[0x86].addrmode = addrmode_ZP;
    opcode_lut[0x86].cycles = 3;

    opcode_lut[0x96].operate = opcode_STX;
    opcode_lut[0x96].addrmode = addrmode_ZPY;
    opcode_lut[0x96].cycles = 4;

    opcode_lut[0x8E].operate = opcode_STX;
    opcode_lut[0x8E].addrmode = addrmode_ABS;
    opcode_lut[0x8E].cycles = 4;
    // STY
    opcode_lut[0x84].operate = opcode_STY;
    opcode_lut[0x84].addrmode = addrmode_ZP;
    opcode_lut[0x84].cycles = 3;

    opcode_lut[0x94].operate = opcode_STY;
    opcode_lut[0x94].addrmode = addrmode_ZPY;
    opcode_lut[0x94].cycles = 4;

    opcode_lut[0x8C].operate = opcode_STY;
    opcode_lut[0x8C].addrmode = addrmode_ABS;
    opcode_lut[0x8C].cycles = 4;
    //TAX
    opcode_lut[0xAA].operate = opcode_TAX;
    opcode_lut[0xAA].addrmode = addrmode_IMP;
    opcode_lut[0xAA].cycles = 2;
    //TAY
    opcode_lut[0xA8].operate = opcode_TAY;
    opcode_lut[0xA8].addrmode = addrmode_IMP;
    opcode_lut[0xA8].cycles = 2;
    //TSX
    opcode_lut[0xBA].operate = opcode_TSX;
    opcode_lut[0xBA].addrmode = addrmode_IMP;
    opcode_lut[0xBA].cycles = 2;
    //TXA
    opcode_lut[0x8A].operate = opcode_TXA;
    opcode_lut[0x8A].addrmode = addrmode_IMP;
    opcode_lut[0x8A].cycles = 2;
    //TXS
    opcode_lut[0x9A].operate = opcode_TXS;
    opcode_lut[0x9A].addrmode = addrmode_IMP;
    opcode_lut[0x9A].cycles = 2;
    //TYA
    opcode_lut[0x98].operate = opcode_TYA;
    opcode_lut[0x98].addrmode = addrmode_IMP;
    opcode_lut[0x98].cycles = 2;
}
