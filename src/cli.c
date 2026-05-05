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

#include "cli.h"
#include <stdio.h>
#include <string.h>
#include "6502_mem.h"
#include "cpu.h"

uint32_t process_cli(CpuStateTypedef* cpu){
  char strbuf[100] = {0};
  scanf("%s", strbuf);
  if(strcmp(strbuf, "WREGISTERS") == 0){
    uint32_t pc, s, a, x, y, p;
    scanf("%d", &pc);
    scanf("%d", &s);
    scanf("%d", &a);
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &p);
    cpu->PC     = pc;
    cpu->S      = s;
    cpu->A      = a;
    cpu->X      = x;
    cpu->Y      = y;
    cpu->P_val  = p;
    printf("WREGISTERS\n");
    fflush(stdout);
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "RREGISTERS") == 0){
    printf("pc = 0x%x\n",cpu->PC);
    fflush(stdout);
    printf("s =  0x%x\n",cpu->S);
    fflush(stdout);
    printf("a =  0x%x\n",cpu->A);
    fflush(stdout);
    printf("x =  0x%x\n",cpu->X);
    fflush(stdout);
    printf("y =  0x%x\n",cpu->Y);
    fflush(stdout);
    printf("p =  0x%x\n",cpu->P_val);
    fflush(stdout);
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "WMEMORY") == 0){
    uint32_t addr, val;
    scanf("%d", &addr);
    scanf("%d", &val);
    write_ram((uint16_t)addr, (uint8_t)val);
    printf("WMEMORY\n");
    fflush(stdout);
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "RMEMORY") == 0){
    uint32_t addr, memory;
    scanf("%d", &addr);
    memory = read_ram(addr);
    printf("value on address 0x%x = 0x%x\n", addr, memory);
    fflush(stdout);
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "STEP") == 0){
    cpu_tick(cpu);
    printf("STEP\n");
    fflush(stdout);
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "END") == 0){
    printf("PROCESSOR SHUT DOWN\n");
    printf("OK\n");
    fflush(stdout);
    return 0;
  } else {
    printf("ERROR\n");
    fflush(stdout);
    return 0;
  }
}
