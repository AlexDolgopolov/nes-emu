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

#ifndef ADDRMODE_H
#define ADDRMODE_H

#include <stdint.h>
#include <stdbool.h>
#include "cpu.h"
#include "6502_mem.h"

typedef struct {
    uint16_t address;
    bool page_crossing;
    uint8_t pc_inc;
} RetAddress;



RetAddress addrmode_IMP(CpuStateTypedef* cpu);
RetAddress addrmode_IMM(CpuStateTypedef* cpu);
#define addrmode_REL addrmode_IMM
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
