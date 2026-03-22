#include "6502_mem.h"

uint8_t cpu_ram[0x10000] = {0};

uint8_t read_ram(uint16_t addr){
    return(cpu_ram[addr]);
}

void write_ram(uint16_t addr, uint8_t val){
    cpu_ram[addr] = val;
}

void push_stack(uint8_t* sp, uint8_t data){
    write_ram(0x0100 + *sp, data);
    *sp = (*sp)--;
}
uint8_t pop_stack(uint8_t* sp){
    *sp = (*sp)++;
    return(read_ram(0x0100 + *sp));
}

