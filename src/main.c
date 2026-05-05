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

#include <stdio.h>
#include <string.h>
#include "nes_cycle.h"
#include "cli.h"
#include "boot.h"
#include "framebuffero.h"

CpuStateTypedef cpu;

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Not valid argc\n");
    fflush(stdout);
    return 1;
  } else {
    if(strcmp(argv[1], "0") == 0){
    // WORK MODE
      printf("%s, WORK MODE NOT IMPLEMENTED\n", argv[1]);
      fflush(stdout);
      boot("../rom/smb.nes");
      framebuffero_init();
      cpu_powerup(&cpu);
      ppu_powerup();
      nes_cycle();
      printf("PROCESSOR SHUT DOWN\n");
      fflush(stdout);
      return 1;
    } else if(strcmp(argv[1], "1") == 0){
      printf("%s, TEST MODE\n", argv[1]);
      fflush(stdout);
      while(process_cli(&cpu) != 0);
      printf("PROCESSOR SHUT DOWN\n");
      fflush(stdout);
      return 0;
    } else if(strcmp(argv[1], "2") == 0){
      // BOOT TEST MODE
      printf("%s, TEST MODE\n", argv[1]);
      fflush(stdout);
      process_cli(&cpu);
      printf("PROCESSOR SHUT DOWN\n");
      fflush(stdout);
      return 0;
    } else {
      printf("%s, UNKNOWN MODE\n", argv[1]);
      fflush(stdout);
      printf("PROCESSOR SHUT DOWN\n");
      fflush(stdout);
      return 2;
    }
    return 0;
  }
};
