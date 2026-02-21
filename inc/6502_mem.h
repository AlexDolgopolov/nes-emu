#ifndef CPU_MEM_H
#define CPU_MEM_H

#include <stdint.h>

uint8_t read_ram(uint16_t addr);
void write_ram(uint16_t addr, uint8_t val);

#endif
