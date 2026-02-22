#include "6502_mem.h"

uint8_t cpu_ram[2048];

uint8_t read_ram(uint16_t addr){
    if((addr >= 0x0000 && addr < 0x2000)){
        return(cpu_ram[addr & 0x7ff]);
    } else if((addr >= 0x2000 && addr < 0x4000)){
        // NES PPU REGISTERS
        // addr & 0x7
        while(1);
    } else if((addr >= 0x4000 && addr < 0x4020)){
        // NES APU AND IO REGISTERS
        // addr & 0x1f
        while(1);
    } else {
        // UNMAPPED
        while(1);
    }
}

void write_ram(uint16_t addr, uint8_t val){
    if((addr >= 0x0000 && addr < 0x2000)){
        cpu_ram[addr & 0x7ff] = val;
    } else if((addr >= 0x2000 && addr < 0x4000)){
        // NES PPU REGISTERS
        // addr & 0x7
        while(1);
    } else if((addr >= 0x4000 && addr < 0x4020)){
        // NES APU AND IO REGISTERS
        // addr & 0x1f
        while(1);
    } else {
        // UNMAPPED
        while(1);
    }
}

void push_stack(uint8_t* sp, uint8_t data){
    write_ram(0x0100 + *sp, data);
    *sp = (*sp)--;
}
uint8_t pop_stack(uint8_t* sp){
    *sp = (*sp)++;
    return(read_ram(0x0100 + *sp));
}
