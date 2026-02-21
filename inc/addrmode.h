#ifndef ADDRMODE_H
#define ADDRMODE_H

#include <stdint.h>
#include <stdbool.h>
#include "cpu.h"

typedef struct {
    uint16_t address;
    bool page_crossing;
} RetAddress;

typedef struct  {
    void (*operate)(void);    // Указатель на функцию команды (LDA, ADC...)
    RetAddress (*addrmode)(CpuStateTypedef* cpu); // Указатель на функцию получения адреса
    uint8_t cycles;        // Базовое количество циклов
} Instruction;

RetAddress addrmode_IMP(CpuStateTypedef* cpu);
RetAddress addrmode_IMM(CpuStateTypedef* cpu);
RetAddress addrmode_ABS(CpuStateTypedef* cpu);
RetAddress addrmode_ABSX(CpuStateTypedef* cpu);
RetAddress addrmode_ABSY(CpuStateTypedef* cpu);
RetAddress addrmode_ZP(CpuStateTypedef* cpu);
RetAddress addrmode_ZPX(CpuStateTypedef* cpu);
RetAddress addrmode_ZPY(CpuStateTypedef* cpu);
RetAddress addrmode_REL(CpuStateTypedef* cpu);
RetAddress addrmode_IND(CpuStateTypedef* cpu);
RetAddress addrmode_INDX(CpuStateTypedef* cpu);
RetAddress addrmode_INDY(CpuStateTypedef* cpu);


#endif
