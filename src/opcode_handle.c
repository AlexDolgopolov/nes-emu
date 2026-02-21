#include "opcode_handle.h"

uint8_t opcode_ADC(CpuStateTypedef* cpu, uint16_t mem_idx){
 // Add with Carry
 uint8_t mem_val = read_ram(mem_idx);
 uint16_t accumulator_val = cpu->A + mem_val + ((cpu->P_bit.C) ? 1 : 0);
 cpu->P_bit.C = (accumulator_val > 0xff);
 uint8_t accumulator = accumulator_val & 0xff;
 cpu->P_bit.Z = accumulator == 0;
 cpu->P_bit.V = (accumulator ^ cpu->A) & (accumulator ^ mem_val) & 0x80;
 cpu->P_bit.N = (accumulator & (1<<7)) != 0;
 cpu->A = accumulator;
 cpu->PC++;
 return 2;
}

uint8_t opcode_AND(CpuStateTypedef* cpu, uint16_t mem_idx){
 // Bitwise AND
 uint8_t mem_val = read_ram(mem_idx);
 uint8_t accumulator = cpu->A & mem_val;
 cpu->P_bit.Z = accumulator == 0;
 cpu->P_bit.N = (accumulator & (1<<7)) != 0;
 cpu->A = accumulator;
 cpu->PC++;
 return 2;
}

uint8_t opcode_ASL(CpuStateTypedef* cpu, uint16_t mem_idx){
 // Arithmetic Shift Left
 uint8_t mem_val = read_ram(mem_idx);
 cpu->P_bit.C = (mem_val & (1 << 7)) != 0;
 mem_val = mem_val << 1;
 cpu->P_bit.Z = mem_val == 0;
 cpu->P_bit.N = (mem_val & (1<<7)) != 0;
 *mem = mem_val;
 cpu->PC++;
 return 2;
}

uint8_t opcode_BCC(CpuStateTypedef* cpu, uint16_t mem_idx){
// Branch if Carry Clear
    if(cpu->P_bit.C == 0){
        uint8_t mem_val = read_ram(mem_idx);
        cpu->PC = mem_val;
        return 3;
    } else return 2;
}

uint8_t opcode_BCS(CpuStateTypedef* cpu, uint16_t mem_idx){
// Branch if Carry Set
    if(cpu->P_bit.C == 1){
        uint8_t mem_val = read_ram(mem_idx);
        cpu->PC = mem_val;
        return 3;
    } else return 2;
}

uint8_t opcode_BEQ(CpuStateTypedef* cpu, uint16_t mem_idx){
// Branch if Equal
    if(cpu->P_bit.Z == 1){
        uint8_t mem_val = read_ram(mem_idx);
        cpu->PC = mem_val;
        return 3;
    } else return 2;
}

uint8_t opcode_BIT(CpuStateTypedef* cpu, uint16_t mem_idx){
// Bit Test
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t accumulator = cpu->A & mem_val;
    cpu->P_bit.Z = accumulator == 0;
    cpu->P_bit.V = (accumulator & (1 << 6)) != 0;
    cpu->P_bit.N = (accumulator & (1 << 7)) != 0;
    cpu->PC++;
    return 2;
}

uint8_t opcode_BMI(CpuStateTypedef* cpu, uint16_t mem_idx){
// Branch if Minus
    if(cpu->P_bit.N == 1){
        uint8_t mem_val = read_ram(mem_idx);
        cpu->PC = mem_val;
        return 3;
    } else return 2;
}

uint8_t opcode_BNE(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Branch if Not Equal
    if(cpu->P_bit.Z == 0){
        uint8_t mem_val = read_ram(mem_idx);
        cpu->PC = mem_val;
        return 3;
    } else return 2;
}

uint8_t opcode_BPL(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Branch if Plus
    if(cpu->P_bit.N == 0){
        uint8_t mem_val = read_ram(mem_idx);
        cpu->PC = mem_val;
        return 3;
    } else return 2;
}

uint8_t opcode_BRK(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Break (software IRQ)
    cpu->PC++;
    return 2;
}
