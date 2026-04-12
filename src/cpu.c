#include <cpu.h>
#include <6502_mem.h>
#include <stdio.h>
#include <addrmode.h>
#include <decode_lut.h>
#include <interrupt.h>
#include "debug.h"
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

void cpu_tick(CpuStateTypedef* cpu){
    DEBUG("start tick\n", 0);
    check_interrupt(cpu);
    uint16_t address = cpu->PC;
    DEBUG("address = %x\n", address);
    uint8_t cmd = read_ram(address);
    DEBUG("cmd = %x\n", cmd);
    Instruction instr = get_instruction(cmd);
    if((void*)instr.addrmode == NULL){
        DEBUG("ILLEGAL_INSTRUCTION\n", 0);
        while(1);
    }
    RetAddress  i_addr = instr.addrmode(cpu);
    cpu->PC += i_addr.pc_inc;
    //execute
    instr.operate(cpu, i_addr.address);
    DEBUG("end tick\n", 0);
}
