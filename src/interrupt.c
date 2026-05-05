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

#include "interrupt.h"
#include <stdio.h>
#include "debug.h"

bool nmi = false;

void check_interrupt(CpuStateTypedef* cpu){
	bool new_nmi = get_ppu_nmi();
	bool nmi_edge = (!nmi && new_nmi);
	nmi = new_nmi;
	if(nmi_edge){
		DEBUG_PPU("nmi\n");
		fflush(stdout);
		push_stack(&(cpu->S), (uint8_t)(cpu->PC >> 8));
		push_stack(&(cpu->S), (uint8_t)(cpu->PC));
		uint8_t status = cpu->P_val;
		status = (status & ~(1 << 4));
		push_stack(&(cpu->S), status);
		cpu->P_bit.I = 1;
		uint8_t pc_lb = read_ram(0xfffa);
		uint8_t pc_hb = read_ram(0xfffb);
		cpu->PC = (pc_hb << 8) | pc_lb;
	}
}