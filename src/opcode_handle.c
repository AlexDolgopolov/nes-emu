#include "opcode_handle.h"
#include <stdio.h>
#include "debug.h"

uint8_t opcode_ILL(CpuStateTypedef* cpu, uint16_t mem_idx){
    // Illegal Insruction (This is not official opcode, but may be helpfull for debug)
    DEBUG("illegal_istruction\n");
    fflush(stdout);
    while(1);
    return 0;
}

uint8_t opcode_ADC(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("ADC\n");
 // Add with Carry
 uint8_t mem_val = read_ram(mem_idx);
 uint16_t accumulator_val = cpu->A + mem_val + ((cpu->P_bit.C) ? 1 : 0);
 cpu->P_bit.C = (accumulator_val > 0xff);
 uint8_t accumulator = accumulator_val & 0xff;
 cpu->P_bit.Z = accumulator == 0;
 cpu->P_bit.V = ((accumulator ^ cpu->A) & (accumulator ^ mem_val) & 0x80) != 0;
 cpu->P_bit.N = (accumulator & (1<<7)) != 0;
 cpu->A = accumulator;
 return 0;
}

uint8_t opcode_AND(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("AND\n");
 // Bitwise AND
 uint8_t mem_val = read_ram(mem_idx);
 uint8_t accumulator = cpu->A & mem_val;
 cpu->P_bit.Z = accumulator == 0;
 cpu->P_bit.N = (accumulator & (1<<7)) != 0;
 cpu->A = accumulator;
 return 0;
}

uint8_t opcode_ASL(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("ASL\n");
    // Arithmetic Shift Left
    uint8_t mem_val = read_ram(mem_idx);
    cpu->P_bit.C = (mem_val & (1 << 7)) != 0;
    mem_val = mem_val << 1;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1<<7)) != 0;
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_ASL_A(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("ASL\n");
    // Arithmetic Shift Left - Accumulator
    uint8_t mem_val = cpu->A;
    cpu->P_bit.C = (mem_val & (1 << 7)) != 0;
    mem_val = mem_val << 1;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1<<7)) != 0;
    cpu->A = mem_val;
    return 0;
}

uint8_t opcode_BCC(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BCC\n");
    // Branch if Carry Clear
    if(cpu->P_bit.C == 0){
        char mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BCS(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BCS\n");
// Branch if Carry Set
    if(cpu->P_bit.C == 1){
        char mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BEQ(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BEQ\n");
// Branch if Equal
    if(cpu->P_bit.Z == 1){
        char mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BIT(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BIT\n");
// Bit Test
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t accumulator = cpu->A & mem_val;
    cpu->P_bit.Z = accumulator == 0;
    cpu->P_bit.V = (mem_val & (1 << 6)) != 0;
    cpu->P_bit.N = (mem_val & (1 << 7)) != 0;
    return 0;
}

uint8_t opcode_BMI(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BMI\n");
// Branch if Minus
    if(cpu->P_bit.N == 1){
        char mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BNE(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BNE\n");
    // Branch if Not Equal
    if(cpu->P_bit.Z == 0){
        char mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BPL(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BPL\n");
    // Branch if Plus
    if(cpu->P_bit.N == 0){
        char mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC) & 0xff00) != ((cpu->PC+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val;
        DEBUG("BRANCH to %x\n", cpu->PC);
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BRK(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BRK\n");
    // Break (software IRQ)
    uint16_t pc = cpu->PC+1; // we already increment pc by 1
    push_stack(&(cpu->S), (pc & 0xff00) >> 8);
    push_stack(&(cpu->S), pc & 0xff);
    push_stack(&(cpu->S), cpu->P_val | (1 << 4) | (1 << 5));
    cpu->P_bit.I = 1;
    cpu->PC = (read_ram(0xffff) << 8) | read_ram(0xfffe);
    return 0;
}

uint8_t opcode_BVC(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BVC\n");
    // Branch if Overflow Clear
    if(cpu->P_bit.V == 0){
        char mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_BVS(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("BVS\n");
    // Branch if Overflow Set
    if(cpu->P_bit.V == 1){
        char mem_val = read_ram(mem_idx);
        bool page_cross_branch = ((cpu->PC+2) & 0xff00) != ((cpu->PC+2+mem_val) & 0xff00);
        cpu->PC = cpu->PC + mem_val;
        return page_cross_branch ? 2 : 1;
    } else return 0;
}

uint8_t opcode_CLC(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("CLC\n");
    // Clear Carry
    cpu->P_bit.C = 0;
    return 0;
}

uint8_t opcode_CLD(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("CLD\n");
    // Clear Decimal
    cpu->P_bit.D = 0;
    return 0;
}

uint8_t opcode_CLI(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("CLI\n");
    // Clear Interrupt Disable
    cpu->P_bit.I = 0;
    return 0;
}

uint8_t opcode_CLV(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("CLV\n");
    // Clear Overflow
    cpu->P_bit.V = 0;
    return 0;
}

uint8_t opcode_CMP(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("CMP\n");
    // Compare A
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t accumulator = cpu->A;
    cpu->P_bit.C = (accumulator >= mem_val);
    cpu->P_bit.Z = (accumulator == mem_val);
    cpu->P_bit.N = ((accumulator - mem_val) & (1 << 7)) != 0;
    return 0;
}

uint8_t opcode_CPX(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("CPX\n");
    // Compare X
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t x_val = cpu->X;
    DEBUG("mem_val = %x\n", mem_val);
    DEBUG("x_val = %x\n", x_val);
    cpu->P_bit.C = (x_val >= mem_val);
    cpu->P_bit.Z = (x_val == mem_val);
    cpu->P_bit.N = ((x_val - mem_val) & (1 << 7)) != 0;
    return 0;
}

uint8_t opcode_CPY(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("CPY\n");
    // Compare Y
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t y_val = cpu->Y;
    cpu->P_bit.C = (y_val >= mem_val);
    cpu->P_bit.Z = (y_val == mem_val);
    cpu->P_bit.N = ((y_val - mem_val) & (1 << 7)) != 0;
    return 0;
}

uint8_t opcode_DEC(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("DEC\n");
    // Decrement Memory
    uint8_t mem_val = read_ram(mem_idx);
    mem_val--;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7) != 0;
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_DEX(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("DEX\n");
    // Decrement X
    uint8_t mem_val = cpu->X;
    mem_val--;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7) != 0;
    cpu->X = mem_val;
    return 0;
}

uint8_t opcode_DEY(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("DEY\n");
    // Decrement Y
    uint8_t mem_val = cpu->Y;
    mem_val--;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7) != 0;
    cpu->Y = mem_val;
    DEBUG("cpu->Y = %x\n", cpu->Y);
    return 0;
}

uint8_t opcode_EOR(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("EOR\n");
    // Bitwise XOR
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t result = cpu->A ^ mem_val;
    cpu->P_bit.Z = result == 0;
    cpu->P_bit.N = (result & (1<<7)) != 0;
    cpu->A = result;
return 0;
}

uint8_t opcode_INC(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("INC\n");
    // Increment Memory
    uint8_t mem_val = read_ram(mem_idx);
    mem_val++;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7) != 0;
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_INX(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("INX\n");
    // Increment X
    uint8_t mem_val = cpu->X;
    mem_val++;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7) != 0;
    cpu->X = mem_val;
    return 0;
}

uint8_t opcode_INY(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("INY\n");
    // Increment Y
    uint8_t mem_val = cpu->Y;
    mem_val++;
    cpu->P_bit.Z = (mem_val == 0x0);
    cpu->P_bit.N = (mem_val & 1 << 7) != 0;
    cpu->Y = mem_val;
    return 0;
}

uint8_t opcode_JMP(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("JMP\n");
    // Jump
    cpu->PC = mem_idx;
    return 0;
}
uint8_t opcode_JSR(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("JSR\n");
    uint16_t return_addr = cpu->PC - 1;
    push_stack(&(cpu->S), (uint8_t)(return_addr >> 8));
    push_stack(&(cpu->S), (uint8_t)(return_addr & 0xFF));
    DEBUG("JSR: saving return_addr=0x%04X, jumping to 0x%04X\n", return_addr, mem_idx);
    cpu->PC = mem_idx;
    return 0;
}

uint8_t opcode_LDA(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("LDA\n");
    DEBUG("%x\n", mem_idx);
    // Load A
    uint8_t mem_val = read_ram(mem_idx);
    cpu->A = mem_val;
    cpu->P_bit.Z = cpu->A == 0;
    cpu->P_bit.N = (cpu->A & (1<<7)) != 0;
    return 0;
}

uint8_t opcode_LDX(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("LDX\n");
    // Load X
    uint8_t mem_val = read_ram(mem_idx);
    cpu->X = mem_val;
    cpu->P_bit.Z = cpu->X == 0;
    cpu->P_bit.N = (cpu->X & (1<<7)) != 0;
    return 0;
}

uint8_t opcode_LDY(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("LDY\n");
    // Load Y
    uint8_t mem_val = read_ram(mem_idx);
    cpu->Y = mem_val;
    cpu->P_bit.Z = cpu->Y == 0;
    cpu->P_bit.N = (cpu->Y & (1<<7)) != 0;
    return 0;
}

uint8_t opcode_LSR(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("LSR\n");
    // Logical Shift Right
    uint8_t mem_val = read_ram(mem_idx);
    cpu->P_bit.C = (mem_val & (1 << 0)) != 0;
    mem_val = mem_val >> 1;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1<<7)) != 0;
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_LSR_A(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("LSR\n");
    // Logical Shift Right - Accumulator
    uint8_t mem_val = cpu->A;
    cpu->P_bit.C = (mem_val & (1 << 0)) != 0;
    mem_val = mem_val >> 1;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1<<7)) != 0;
    cpu->A = mem_val;
    return 0;
}

uint8_t opcode_NOP(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("NOP\n");
    // No Operation
    return 0;
}

uint8_t opcode_ORA(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("ORA\n");
    // Bitwise OR
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t accumulator = cpu->A | mem_val;
    DEBUG("accumulator = %x\n", cpu->A);
    DEBUG("mem_idx = %x\n", mem_idx);
    DEBUG("mem_val = %x\n", mem_val);
    cpu->P_bit.Z = accumulator == 0;
    cpu->P_bit.N = (accumulator & (1<<7)) != 0;
    cpu->A = accumulator;
    return 0;
}

uint8_t opcode_PHA(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("PHA\n");
    // Push A
    push_stack(&(cpu->S), cpu->A);
    return 0;
}

uint8_t opcode_PHP(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("PHP\n");
    // Push Processor Status
    push_stack(&(cpu->S), cpu->P_val | (1 << 4));
    return 0;
}

uint8_t opcode_PLA(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("PLA\n");
    // Pull A
    cpu->A = pop_stack(&(cpu->S));
    cpu->P_bit.Z = (cpu->A == 0);
    cpu->P_bit.N = (cpu->A & (1 << 7)) != 0;
    return 0;
}

uint8_t opcode_PLP(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("PLP\n");
    // Pull A
    cpu->P_val &= ((1 << 4) | (1 << 5));
    cpu->P_val |= (pop_stack(&(cpu->S))) & ~((1 << 4) | (1 << 5));
    return 0;
}

uint8_t opcode_ROL(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("ROL\n");
    // Rotate Left
    uint8_t mem_val = read_ram(mem_idx);
    bool carry = (mem_val & (1 << 7)) != 0;
    mem_val = mem_val << 1;
    mem_val |= cpu->P_bit.C & 0x1;
    cpu->P_bit.C = carry;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1 << 7)) != 0;
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_ROL_A(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("ROL\n");
    // Rotate Left - Accumulator
    uint8_t mem_val = cpu->A;
    bool carry = (mem_val & (1 << 7)) != 0;
    mem_val = mem_val << 1;
    mem_val |= cpu->P_bit.C & 0x1;
    cpu->P_bit.C = carry;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1 << 7)) != 0;
    cpu->A = mem_val;
    return 0;
}

uint8_t opcode_ROR(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("ROR\n");
    // Rotate Right
    uint8_t mem_val = read_ram(mem_idx);
    bool carry = (mem_val & 0b1) != 0;
    mem_val = mem_val >> 1;
    mem_val |= (cpu->P_bit.C & 0x1) << 7;
    cpu->P_bit.C = carry;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1 << 7)) != 0;
    write_ram(mem_idx, mem_val);
    return 0;
}

uint8_t opcode_ROR_A(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("ROR\n");
    // Rotate Right - Accumulator
    uint8_t mem_val = cpu->A;
    bool carry = (mem_val & 0b1) != 0;
    mem_val = mem_val >> 1;
    mem_val |= (cpu->P_bit.C & 0x1) << 7;
    cpu->P_bit.C = carry;
    cpu->P_bit.Z = mem_val == 0;
    cpu->P_bit.N = (mem_val & (1 << 7)) != 0;
    cpu->A = mem_val;
    return 0;
}

uint8_t opcode_RTI(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("RTI\n");
    // Return from Interrupt
    cpu->P_val = (pop_stack(&(cpu->S)) & ~(0b11 << 4)) | (cpu->P_val & (0b11 << 4));
    uint8_t new_pc_lb = pop_stack(&(cpu->S));
    uint8_t new_pc_hb = pop_stack(&(cpu->S));
    cpu->PC = (new_pc_hb << 8) | new_pc_lb;
    return 0;
}

uint8_t opcode_RTS(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("RTS\n");
    // Return from Subroutine
    DEBUG("SP = %x\n", cpu->S);
    uint8_t new_pc_lb = pop_stack(&(cpu->S));
    uint8_t new_pc_hb = pop_stack(&(cpu->S));
    DEBUG("RTS: popped addr=0x%04X, jumping to 0x%04X\n", ((new_pc_hb << 8) | new_pc_lb), ((new_pc_hb << 8) | new_pc_lb) + 1);
    cpu->PC = ((new_pc_hb << 8) | new_pc_lb) + 1;
    return 0;
}

uint8_t opcode_SBC(CpuStateTypedef* cpu, uint16_t mem_idx) {
    uint8_t mem_val = read_ram(mem_idx);
    uint8_t inverted = mem_val ^ 0xFF;
    uint16_t result = (uint16_t)cpu->A + (uint16_t)inverted + (uint16_t)cpu->P_bit.C;
    cpu->P_bit.C = (result > 0xFF);
    cpu->P_bit.Z = ((result & 0xFF) == 0);
    cpu->P_bit.V = ((cpu->A ^ result) & (inverted ^ result) & 0x80) != 0;
    cpu->P_bit.N = (result & 0x80) != 0;
    cpu->A = (uint8_t)result;
    return 0;
}

uint8_t opcode_SEC(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("SEC\n");
    // Set Carry
    cpu->P_bit.C = 1;
    return 0;
}

uint8_t opcode_SED(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("SED\n");
    // Set Decimal
    cpu->P_bit.D = 1;
    return 0;
}

uint8_t opcode_SEI(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("SEI\n");
    // Set Interrupt Disable
    cpu->P_bit.I = 1;
    return 0;
}

uint8_t opcode_STA(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("STA\n");
    DEBUG("mem_idx = %x\n", mem_idx);
    // Store A
    write_ram(mem_idx, cpu->A);
    return 0;
}

uint8_t opcode_STX(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("STX\n");
    // Store X
    write_ram(mem_idx, cpu->X);
    return 0;
}

uint8_t opcode_STY(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("STY\n");
    // Store Y
    DEBUG("mem_idx = %x\n", mem_idx);
    write_ram(mem_idx, cpu->Y);
    return 0;
}

uint8_t opcode_TAX(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("TAX\n");
    // Transfer A to X
    cpu->X = cpu->A;
    cpu->P_bit.Z = (cpu->X == 0);
    cpu->P_bit.N = (cpu->X & (1 << 7)) != 0;
    return 0;
}

uint8_t opcode_TAY(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("TAY\n");
    // Transfer A to Y
    cpu->Y = cpu->A;
    cpu->P_bit.Z = (cpu->Y == 0);
    cpu->P_bit.N = (cpu->Y & (1 << 7)) != 0;
    return 0;
}

uint8_t opcode_TSX(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("TSX\n");
    // Transfer S to X
    cpu->X = cpu->S;
    cpu->P_bit.Z = (cpu->X == 0);
    cpu->P_bit.N = (cpu->X & (1 << 7)) != 0;
    return 0;
}

uint8_t opcode_TXA(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("TXA\n");
    // Transfer X to A
    cpu->A = cpu->X;
    cpu->P_bit.Z = (cpu->A == 0);
    cpu->P_bit.N = (cpu->A & (1 << 7)) != 0;

    return 0;
}

uint8_t opcode_TXS(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("TXS\n");
    // Transfer X to S
    cpu->S = cpu->X;
    return 0;
}

uint8_t opcode_TYA(CpuStateTypedef* cpu, uint16_t mem_idx){
    DEBUG("TYA\n");
    // Transfer Y to A
    cpu->A = cpu->Y;
    cpu->P_bit.Z = (cpu->A == 0);
    cpu->P_bit.N = (cpu->A & (1 << 7)) != 0;
    return 0;
}
