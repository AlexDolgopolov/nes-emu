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

#include "oam_dma.h"
#include "debug.h"


void write_oam_dma(uint8_t arg){
	DEBUG("DMA START WORKING FOR 256 CPU CYCLES\n");
	uint16_t start_addr = arg << 8;
	for(uint16_t i=0;i<256;i++){
		write_oam_data((uint8_t)i, read_ram(start_addr+i));	
	}
	set_wait_cycle(513);
}