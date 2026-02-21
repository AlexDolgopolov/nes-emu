#include "cpu_decoder.h"

void cpu_decode(CpuStateTypedef* cpu){
    uint16_t pc = cpu->PC;
    uint8_t opcode = read_ram(uint16_t addr);

}
