#ifndef CPU_MEM_H
#define CPU_MEM_H

#include <stdint.h>

uint8_t read_ram(uint16_t addr);
void write_ram(uint16_t addr, uint8_t val);
void push_stack(uint8_t* sp, uint8_t data);
uint8_t pop_stack(uint8_t* sp);

#endif
