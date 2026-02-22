#ifndef ADDRMODE_H
#define ADDRMODE_H

#include <stdint.h>
#include <stdbool.h>
#include "cpu.h"
#include "6502_mem.h"

typedef struct {
    uint16_t address;
    bool page_crossing;
} RetAddress;



RetAddress addrmode_IMP(CpuStateTypedef* cpu);
RetAddress addrmode_IMM(CpuStateTypedef* cpu);
RetAddress addrmode_ABS(CpuStateTypedef* cpu);
RetAddress addrmode_ABSX(CpuStateTypedef* cpu);
RetAddress addrmode_ABSY(CpuStateTypedef* cpu);
RetAddress addrmode_ZP(CpuStateTypedef* cpu);
RetAddress addrmode_ZPX(CpuStateTypedef* cpu);
RetAddress addrmode_ZPY(CpuStateTypedef* cpu);
RetAddress addrmode_IND(CpuStateTypedef* cpu);
RetAddress addrmode_INDX(CpuStateTypedef* cpu);
RetAddress addrmode_INDY(CpuStateTypedef* cpu);


#endif
