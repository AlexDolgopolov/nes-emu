#include "6502_mem.h"
#include "debug.h"



uint8_t cpu_ram[0x10000] = {0};

uint8_t read_ram(uint16_t addr){
    uint8_t retval;
#ifdef CPU_TEST_MODE
    return cpu_ram[addr];
#else
    if((addr >= 0x0000 && addr < 0x2000)){
        retval = cpu_ram[addr & 0x7ff];
    } else if((addr >= 0x2000 && addr < 0x4000)){
        retval = read_ppu_reg(addr & 0x7);
    } else if((addr >= 0x4000 && addr < 0x4020)){
        // NES APU AND IO REGISTERS
        // addr & 0x1f
        retval = cpu_ram[addr];
    } else {
        retval = cpu_ram[addr];
    }
    DEBUG_RAM("ram read addr = %x, data = %x\n", addr, retval);
    return retval;
#endif
    
}

void write_ram(uint16_t addr, uint8_t val){
DEBUG_RAM("ram write addr = %x, data = %x\n", addr, val);
#ifdef CPU_TEST_MODE
    cpu_ram[addr] = val;
#else
    if((addr >= 0x0000 && addr < 0x2000)){
        cpu_ram[addr & 0x7ff] = val;
    } else if((addr >= 0x2000 && addr < 0x4000)){
        write_ppu_reg(addr & 0x7, val);
    } else if((addr >= 0x4000 && addr < 0x4020)){
        // NES APU AND IO REGISTERS
        // addr & 0x1f
        cpu_ram[addr] = val;
    } else {
        cpu_ram[addr] = val;
    }
#endif
}

void push_stack(uint8_t* sp, uint8_t data){
    DEBUG_STACK("push_stack: %x\nsp = %x\n", data, *sp);
    write_ram(0x0100 + *sp, data);
    DEBUG_STACK("ram at %x = %x\n", 0x0100 + *sp, read_ram(0x0100 + *sp));
    (*sp)--;
}

uint8_t pop_stack(uint8_t* sp){
    (*sp)++;
    DEBUG_STACK("pop_stack: %x\nsp = %x\n", read_ram(0x0100 + *sp), *sp);
    DEBUG_STACK("ram at %x = %x\n", 0x0100 + *sp, read_ram(0x0100 + *sp));
    return read_ram(0x0100 + *sp);
}



