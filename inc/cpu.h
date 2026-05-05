/*
 * NES-emu
 * Copyright (C) 2026 Alex Dolgopolov
 *
 * This file is part of NES-emu.
 *
 * NES-emu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NES-emu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with NES-emu. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct{
    uint8_t C : 1;
    uint8_t Z : 1;
    uint8_t I : 1;
    uint8_t D : 1;
    uint8_t B : 1;
    uint8_t one : 1;
    uint8_t V : 1;
    uint8_t N : 1;
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
void set_wait_cycle(uint16_t wc_value);
void cpu_tick(CpuStateTypedef* cpu);

#endif
