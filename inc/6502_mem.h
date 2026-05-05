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

#ifndef CPU_MEM_H
#define CPU_MEM_H

#include <stdint.h>
#include "ppu.h"
#include "oam_dma.h"

uint8_t read_ram(uint16_t addr);
void write_ram(uint16_t addr, uint8_t val);
void push_stack(uint8_t* sp, uint8_t data);
uint8_t pop_stack(uint8_t* sp);

#endif
