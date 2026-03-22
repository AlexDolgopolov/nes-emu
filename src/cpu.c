#include <cpu.h>
#include <6502_mem.h>
#include <stdio.h>
#include <addrmode.h>
#include <decode_lut.h>

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
    printf("start tick\n");
    fflush(stdout);
    uint16_t address = cpu->PC;
    printf("address = %x\n", address);
    fflush(stdout);
    uint8_t cmd = read_ram(address);
    printf("cmd = %x\n", cmd);
    fflush(stdout);
    Instruction instr = get_instruction(cmd);
    printf("fetch instruction\n");
    fflush(stdout);
    RetAddress  i_addr = instr.addrmode(cpu);
    printf("fetch address\n");
    fflush(stdout);
    cpu->PC += i_addr.pc_inc;
    //execute
    instr.operate(cpu, i_addr.address);
    printf("finish execute\n");
    fflush(stdout);
    printf("end tick\n");
    fflush(stdout);
}
