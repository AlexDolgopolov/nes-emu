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

#ifndef DECODE_LUT_H
#define DECODE_LUT_H

#include <stdint.h>
#include "cpu.h"
#include "addrmode.h"
#include "opcode_handle.h"

typedef struct  {
    uint8_t (*operate)(CpuStateTypedef* cpu, uint16_t addr);    // Указатель на функцию команды (LDA, ADC...)
    RetAddress (*addrmode)(CpuStateTypedef* cpu); // Указатель на функцию получения адреса
    uint8_t cycles;        // Базовое количество циклов
} Instruction;

Instruction get_instruction(uint8_t idx);

#endif
