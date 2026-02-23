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
 return 0;
}

uint8_t opcode_AND(CpuStateTypedef* cpu, uint16_t mem_idx){
 // Bitwise AND
 uint8_t mem_val = read_ram(mem_idx);
 uint8_t accumulator = cpu->A & mem_val;
 cpu->P_bit.Z = accumulator == 0;
 cpu->P_bit.N = (accumulator & (1<<7)) != 0;
 cpu->A = accumulator;
 return 0;
}

uint8_t opcode_ASL(CpuStateTypedef* cpu, uint16_t mem_idx){
 // Arithmetic Shift Left
 uint8_t mem_val = read_ram(mem_idx);
 mem_val = mem_val << 1;
 cpu->P_bit.C = (mem_val & (1 << 7)) != 0;
 cpu->P_bit.Z = mem_val == 0;
 cpu->P_bit.N = (mem_val & (1<<7)) != 0;
 write_ram(mem_idx, mem_val);
 return 0;
}

uint8_t opcode_ASL_A(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Arithmetic Shift Left - Accumulator
    uint8_t mem_val = cpu->A;
    mem_val = mem_val << 1;
    cpu->P_bit.C = (mem_val & (1 << 7)) != 0;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1<<7)) != 0;
    cpu->A = mem_val;
    return 0;
}

uint8_t opcode_BCC(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Branch if Carry Clear
    if(cpu->P_bit.C == 0){
        uint8_t mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val + 2;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BCS(CpuStateTypedef* cpu, uint16_t mem_idx){
// Branch if Carry Set
    if(cpu->P_bit.C == 1){
        uint8_t mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val + 2;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BEQ(CpuStateTypedef* cpu, uint16_t mem_idx){
// Branch if Equal
    if(cpu->P_bit.Z == 1){
        uint8_t mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val + 2;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BIT(CpuStateTypedef* cpu, uint16_t mem_idx){
// Bit Test
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t accumulator = cpu->A & mem_val;
    cpu->P_bit.Z = accumulator == 0;
    cpu->P_bit.V = (accumulator & (1 << 6)) != 0;
    cpu->P_bit.N = (accumulator & (1 << 7)) != 0;
    return 0;
}

uint8_t opcode_BMI(CpuStateTypedef* cpu, uint16_t mem_idx){
// Branch if Minus
    if(cpu->P_bit.N == 1){
        uint8_t mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val + 2;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BNE(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Branch if Not Equal
    if(cpu->P_bit.Z == 0){
        uint8_t mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val + 2;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BPL(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Branch if Plus
    if(cpu->P_bit.N == 0){
        uint8_t mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val + 2;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BRK(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Break (software IRQ)
    uint16_t pc = cpu->PC+2;
    push_stack(&(cpu->S), (pc & 0xff00) >> 8);
    push_stack(&(cpu->S), pc & 0xff);
    push_stack(&(cpu->S), cpu->P_val | (1 << 4) | (1 << 5));
    cpu->P_bit.I = 1;
    cpu->PC = (read_ram(0xfffd) << 8) | read_ram(0xfffc);
    return 0;
}

uint8_t opcode_BVC(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Branch if Overflow Clear
    if(cpu->P_bit.V == 0){
        uint8_t mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val + 2;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BVS(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Branch if Overflow Set
    if(cpu->P_bit.V == 1){
        uint8_t mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val + 2;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_CLC(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Clear Carry
    cpu->P_bit.C = 0;
    return 0;
}

uint8_t opcode_CLD(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Clear Decimal
    cpu->P_bit.D = 0;
    return 0;
}

uint8_t opcode_CLI(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Clear Interrupt Disable
    cpu->P_bit.I = 0;
    return 0;
}

uint8_t opcode_CLV(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Clear Overflow
    cpu->P_bit.V = 0;
    return 0;
}

uint8_t opcode_CMP(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Compare A
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t accumulator = cpu->A;
    cpu->P_bit.C = (accumulator >= mem_val);
    cpu->P_bit.Z = (accumulator == mem_val);
    cpu->P_bit.N = (accumulator < mem_val);
    return 0;
}

uint8_t opcode_CPX(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Compare X
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t x_val = cpu->X;
    cpu->P_bit.C = (x_val >= mem_val);
    cpu->P_bit.Z = (x_val == mem_val);
    cpu->P_bit.N = (x_val < mem_val);
    return 0;
}

uint8_t opcode_CPY(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Compare Y
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t y_val = cpu->Y;
    cpu->P_bit.C = (y_val >= mem_val);
    cpu->P_bit.Z = (y_val == mem_val);
    cpu->P_bit.N = (y_val < mem_val);
    return 0;
}

uint8_t opcode_DEC(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Decrement Memory
    uint8_t mem_val = read_ram(mem_idx);
    mem_val--;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7);
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_DEX(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Decrement X
    uint8_t mem_val = cpu->X;
    mem_val--;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7);
    cpu->X = mem_val;
    return 0;
}

uint8_t opcode_DEY(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Decrement Y
    uint8_t mem_val = cpu->Y;
    mem_val--;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7);
    cpu->Y = mem_val;
    return 0;
}

uint8_t opcode_EOR(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Bitwise XOR
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t result = cpu->A ^ mem_val;
    cpu->P_bit.Z = result == 0;
    cpu->P_bit.N = (result & (1<<7)) != 0;
    cpu->A = result;
return 0;
}

uint8_t opcode_INC(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Increment Memory
    uint8_t mem_val = read_ram(mem_idx);
    mem_val++;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7);
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_INX(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Increment X
    uint8_t mem_val = cpu->X;
    mem_val++;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7);
    cpu->X = mem_val;
    return 0;
}

uint8_t opcode_INY(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Increment Y
    uint8_t mem_val = cpu->Y;
    mem_val++;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7);
    cpu->Y = mem_val;
    return 0;
}

uint8_t opcode_JMP(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Jump
    cpu->PC = read_ram(mem_idx);
    return 0;
}
uint8_t opcode_JSR(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Jump to Subroutine
    push_stack(&(cpu->S), (cpu->PC + 2) >> 8);
    push_stack(&(cpu->S), (cpu->PC + 2));
    cpu->PC = read_ram(mem_idx);
    return 0;
}

uint8_t opcode_LDA(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Load A
    uint8_t mem_val = read_ram(mem_idx);
    cpu->A = mem_val;
    cpu->P_bit.Z = cpu->A == 0;
    cpu->P_bit.N = (cpu->A & (1<<7)) != 0;
    return 0;
}

uint8_t opcode_LDX(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Load X
    uint8_t mem_val = read_ram(mem_idx);
    cpu->X = mem_val;
    cpu->P_bit.Z = cpu->X == 0;
    cpu->P_bit.N = (cpu->X & (1<<7)) != 0;
    return 0;
}

uint8_t opcode_LDY(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Load Y
    uint8_t mem_val = read_ram(mem_idx);
    cpu->Y = mem_val;
    cpu->P_bit.Z = cpu->Y == 0;
    cpu->P_bit.N = (cpu->Y & (1<<7)) != 0;
    return 0;
}

uint8_t opcode_ASR(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Arithmetic Shift Right
    uint8_t mem_val = read_ram(mem_idx);
    mem_val = mem_val >> 1;
    cpu->P_bit.C = (mem_val & (1 << 7)) != 0;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1<<7)) != 0;
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_ASR_A(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Arithmetic Shift Right - Accumulator
    uint8_t mem_val = cpu->A;
    mem_val = mem_val >> 1;
    cpu->P_bit.C = (mem_val & (1 << 7)) != 0;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1<<7)) != 0;
    cpu->A = mem_val;
    return 0;
}

uint8_t opcode_NOP(CpuStateTypedef* cpu, uint16_t mem_idx){
    // No Operation
    return 0;
}

uint8_t opcode_ORA(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Bitwise OR
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t accumulator = cpu->A | mem_val;
    cpu->P_bit.Z = accumulator == 0;
    cpu->P_bit.N = (accumulator & (1<<7)) != 0;
    cpu->A = accumulator;
    return 0;
}

uint8_t opcode_PHA(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Push A
    push_stack(&(cpu->S), cpu->A);
    return 0;
}

uint8_t opcode_PHP(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Push Processor Status
    push_stack(&(cpu->S), cpu->P_val);
    return 0;
}

uint8_t opcode_PLA(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Pull A
    cpu->A = pop_stack(&(cpu->S));
    return 0;
}

uint8_t opcode_PLP(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Pull A
    cpu->P_val &= ((1 << 4) | (1 << 5));
    cpu->P_val |= (pop_stack(&(cpu->S))) & ~((1 << 4) | (1 << 5));
    return 0;
}

uint8_t opcode_ROL(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Rotate Left
    uint8_t mem_val = read_ram(mem_idx);
    bool carry = (mem_val & (1 << 7)) != 0;
    mem_val = mem_val << 1;
    mem_val |= cpu->P_bit.C & 0x1;
    cpu->P_bit.C = carry;
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_ROL_A(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Rotate Left - Accumulator
    uint8_t mem_val = cpu->A
    bool carry = (mem_val & (1 << 7)) != 0;
    mem_val = mem_val << 1;
    mem_val |= cpu->P_bit.C & 0x1;
    cpu->P_bit.C = carry;
    cpu->A = mem_val;
    return 0;
}

uint8_t opcode_ROR(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Rotate Right
    uint8_t mem_val = read_ram(mem_idx);
    bool carry = (mem_val & 0b1) != 0;
    mem_val = mem_val >> 1;
    mem_val |= (cpu->P_bit.C & 0x1) << 7;
    cpu->P_bit.C = carry;
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_ROR_A(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Rotate Right - Accumulator
    uint8_t mem_val = cpu->A;
    bool carry = (mem_val & 0b1) != 0;
    mem_val = mem_val >> 1;
    mem_val |= (cpu->P_bit.C & 0x1) << 7;
    cpu->P_bit.C = carry;
    cpu->A = mem_val;
    return 0;
}

uint8_t opcode_RTI(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Return from Interrupt
    cpu->P_val = (pop_stack(&(cpu->S)) & ~(0b11 << 4)) | (cpu->P_val & (0b11 << 4));
    uint8_t new_pc_lb = pop_stack(&(cpu->S));
    uint8_t new_pc_hb = pop_stack(&(cpu->S));
    cpu->PC = (new_pc_hb << 8) | new_pc_lb;
    return 0;
}

uint8_t opcode_RTS(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Return from Subroutine
    uint8_t new_pc_lb = pop_stack(&(cpu->S));
    uint8_t new_pc_hb = pop_stack(&(cpu->S));
    cpu->PC = ((new_pc_hb << 8) | new_pc_lb) + 1;
    return 0;
}

uint8_t opcode_SBC(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Substract with Carry
    uint8_t mem_val = read_ram(mem_idx);
    uint16_t accumulator_val = cpu->A + ~mem_val + (cpu->P_bit.C);
    cpu->P_bit.C = (accumulator_val > cpu->A);
    cpu->P_bit.Z = accumulator_val == 0;
    cpu->P_bit.V = (accumulator_val ^ cpu->A) & (accumulator_val ^ ~mem_val) & 0x80;
    cpu->P_bit.N = (accumulator_val & (1<<7)) != 0;
    cpu->A = accumulator_val;
    return 0;
}

uint8_t opcode_SEC(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Set Carry
    cpu->P_bit.C = 1;
    return 0;
}

uint8_t opcode_SED(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Set Decimal
    cpu->P_bit.D = 1;
    return 0;
}

uint8_t opcode_SEI(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Set Interrupt Disable
    cpu->P_bit.I = 1;
    return 0;
}

uint8_t opcode_STA(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Store A
    write_ram(mem_idx, cpu->A);
    return 0;
}

uint8_t opcode_STX(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Store X
    write_ram(mem_idx, cpu->X);
    return 0;
}

uint8_t opcode_STY(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Store Y
    write_ram(mem_idx, cpu->Y);
    return 0;
}

uint8_t opcode_TAX(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Transfer A to X
    cpu->X = cpu->A;
    return 0;
}

uint8_t opcode_TAY(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Transfer A to Y
    cpu->Y = cpu->A;
    return 0;
}

uint8_t opcode_TSX(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Transfer S to X
    cpu->X = cpu->S;
    return 0;
}

uint8_t opcode_TXA(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Transfer X to A
    cpu->A = cpu->X;
    return 0;
}

uint8_t opcode_TXS(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Transfer X to S
    cpu->S = cpu->X;
    return 0;
}

uint8_t opcode_TYA(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Transfer Y to A
    cpu->A = cpu->Y;
    return 0;
}
