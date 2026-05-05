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

#include <cpu.h>
#include <6502_mem.h>
#include <stdio.h>
#include <addrmode.h>
#include <decode_lut.h>
#include <interrupt.h>
#include "debug.h"

uint16_t wait_cycle = 0;

void cpu_powerup(CpuStateTypedef* cpu){
    cpu->halt_cycle = 0;
    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->PC = (read_ram(0xfffd) << 8) | read_ram(0xfffc);
    cpu->S = 0xfd;
    cpu->P_val = 0;
    cpu->P_bit.I = 1;
}

void cpu_reset(CpuStateTypedef* cpu){
    // A, X, Y - unchanged
    cpu->PC = (read_ram(0xfffd) << 8) | read_ram(0xfffc);
    cpu->S -= 3;
    // P - unchanged except I
    cpu->P_bit.I = 1;
    cpu->halt_cycle = 0;
}

void set_wait_cycle(uint16_t wc_value){
    if(wait_cycle < wc_value) wait_cycle = wc_value;
}

void cpu_tick(CpuStateTypedef* cpu){
    if(wait_cycle != 0){
        wait_cycle--;
        return;
    }
    DEBUG("start tick\n");
    check_interrupt(cpu);
    uint16_t address = cpu->PC;
    DEBUG("address = %x\n", address);
    uint8_t cmd = read_ram(address);
    DEBUG("cmd = %x\n", cmd);
    Instruction instr = get_instruction(cmd);
    if((void*)instr.addrmode == NULL){
        DEBUG("ILLEGAL_INSTRUCTION\n");
        while(1);
    }
    RetAddress  i_addr = instr.addrmode(cpu);
    cpu->PC += i_addr.pc_inc;
    //execute
    uint16_t wc_val = instr.operate(cpu, i_addr.address);
    set_wait_cycle(wc_val);
    DEBUG("end tick\n");
}
