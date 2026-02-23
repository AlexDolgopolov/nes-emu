#include "decode_lut.h"


Instruction opcode_lut[256];

void decode_lut_init(CpuStateTypedef* cpu){
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
    opcode_lut[0x0A].operate = opcode_AND_A;
    opcode_lut[0x0A].addrmode = addrmode_IMP;
    opcode_lut[0x0A].cycles = 2;

    opcode_lut[0x06].operate = opcode_AND;
    opcode_lut[0x06].addrmode = addrmode_ZP;
    opcode_lut[0x06].cycles = 5;

    opcode_lut[0x16].operate = opcode_AND;
    opcode_lut[0x16].addrmode = addrmode_ZPX;
    opcode_lut[0x16].cycles = 6;

    opcode_lut[0x0E].operate = opcode_AND;
    opcode_lut[0x0E].addrmode = addrmode_ABS;
    opcode_lut[0x0E].cycles = 6;

    opcode_lut[0x1E].operate = opcode_AND;
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
    opcode_lut[0xE6].addrmode = addrmode_ZP
    opcode_lut[0xE6].cycles = 5;

    opcode_lut[0xF6].operate = opcode_INC;
    opcode_lut[0xF6].addrmode = addrmode_ZPX
    opcode_lut[0xF6].cycles = 6;

    opcode_lut[0xEE].operate = opcode_INC;
    opcode_lut[0xEE].addrmode = addrmode_ABS
    opcode_lut[0xEE].cycles = 6;

    opcode_lut[0xFE].operate = opcode_INC;
    opcode_lut[0xFE].addrmode = addrmode_ABSX
    opcode_lut[0xFE].cycles = 7;
    //INX
    opcode_lut[0xE8].operate = opcode_INX;
    opcode_lut[0xE8].addrmode = addrmode_IMP
    opcode_lut[0xE8].cycles = 2;
    //INY
    opcode_lut[0xC8].operate = opcode_INY;
    opcode_lut[0xC8].addrmode = addrmode_IMP
    opcode_lut[0xC8].cycles = 2;
    //JMP
    opcode_lut[0x4C].operate = opcode_JMP;
    opcode_lut[0x4C].addrmode = addrmode_ABS
    opcode_lut[0x4C].cycles = 3;

    opcode_lut[0x6C].operate = opcode_JMP;
    opcode_lut[0x6C].addrmode = addrmode_IND
    opcode_lut[0x6C].cycles = 5;
    //JSR
    opcode_lut[0x20].operate = opcode_JSR;
    opcode_lut[0x20].addrmode = addrmode_ABS
    opcode_lut[0x20].cycles = 6;
    //LDA
    opcode_lut[0xA9].operate = opcode_LDA;
    opcode_lut[0xA9].addrmode = addrmode_IMM;
    opcode_lut[0xA9].cycles = 2;

    opcode_lut[0xA5].operate = opcode_LDA;
    opcode_lut[0xA5].addrmode = addrmode_ZP
    opcode_lut[0xA5].cycles = 3;

    opcode_lut[0xB5].operate = opcode_LDA;
    opcode_lut[0xB5].addrmode = addrmode_ZPX;
    opcode_lut[0xB5].cycles = 4;

    opcode_lut[0xAD].operate = opcode_LDA;
    opcode_lut[0xAD].addrmode = addrmode_ABS
    opcode_lut[0xAD].cycles = 4;

    opcode_lut[0xBD].operate = opcode_LDA;
    opcode_lut[0xBD].addrmode = addrmode_ABSX
    opcode_lut[0xBD].cycles = 4;

    opcode_lut[0xB9].operate = opcode_LDA;
    opcode_lut[0xB9].addrmode = addrmode_ABSY
    opcode_lut[0xB9].cycles = 4;

    opcode_lut[0xA1].operate = opcode_LDA;
    opcode_lut[0xA1].addrmode = addrmode_INDX
    opcode_lut[0xA1].cycles = 6;

    opcode_lut[0xB1].operate = opcode_LDA;
    opcode_lut[0xB1].addrmode = addrmode_INDY
    opcode_lut[0xB1].cycles = 5;


}
