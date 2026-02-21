#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct{
    uint8_t N : 1;
    uint8_t V : 1;
    uint8_t one : 1;
    uint8_t B : 1;
    uint8_t D : 1;
    uint8_t I : 1;
    uint8_t Z : 1;
    uint8_t C : 1;
} PBitTypedef;

typedef struct{
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint16_t PC;
    uint8_t S;
    union{
        uint8_t P_val;
        PBitTypedef P_bit;
    };
    // number of dummy cycles
    int halt_cycle;
} CpuStateTypedef;

void cpu_powerup(CpuStateTypedef* cpu);
void cpu_reset(CpuStateTypedef* cpu);


#endif
