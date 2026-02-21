#ifndef DECODE_LUT_H
#define DECODE_LUT_H

#include <stdint.h>
#include "cpu.h"
#include "addrmode.h"

typedef struct  {
    void (*operate)(CpuStateTypedef* cpu, uint16_t addr);    // Указатель на функцию команды (LDA, ADC...)
    RetAddress (*addrmode)(CpuStateTypedef* cpu); // Указатель на функцию получения адреса
    uint8_t cycles;        // Базовое количество циклов
} Instruction;

#endif
