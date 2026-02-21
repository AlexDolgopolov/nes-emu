#include <cpu.h>
#include <6502_mem.h>

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


}
