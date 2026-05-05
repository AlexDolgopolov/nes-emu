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

#ifndef BOOT_H
#define BOOT_H

#include <stdint.h>
#include <stdbool.h>
#include <ppu.h>

typedef enum{
	NO_MAPPER,
	UNKNOWN
} MapperType;

typedef struct{
	uint8_t prg_rom_size;
	uint8_t chr_rom_size;
	PPUScrollingType scrolling;
	uint32_t sram_size;
	MapperType mapper;
} RomMetaDataType;

void boot(const char* path);

#endif