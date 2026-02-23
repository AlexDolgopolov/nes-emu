#ifndef OPCODE_HANDLE_H
#define OPCODE_HANDLE_H

#include <stdbool.h>
#include "cpu.h"
#include "6502_mem.h"


uint8_t opcode_ADC(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_AND(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_ASL(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_ASL_A(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BCC(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BCS(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BEQ(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BIT(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BMI(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BNE(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BPL(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BRK(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BVC(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_BVS(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_CLC(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_CLD(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_CLI(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_CLV(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_CMP(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_CPX(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_CPY(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_DEC(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_DEX(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_DEY(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_EOR(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_INC(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_INX(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_INY(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_JMP(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_JSR(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_LDA(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_LDX(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_LDY(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_ASR(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_ASR_A(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_NOP(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_ORA(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_PHA(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_PHP(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_PLA(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_PLP(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_ROL(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_ROL_A(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_ROR(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_ROR_A(CpuStateTypedef* cpu, uint16_t mem_idx){
uint8_t opcode_RTI(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_RTS(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_SBC(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_SEC(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_SED(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_SEI(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_STA(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_STX(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_STY(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_TAX(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_TAY(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_TSX(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_TXA(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_TXS(CpuStateTypedef* cpu, uint16_t mem_idx);
uint8_t opcode_TYA(CpuStateTypedef* cpu, uint16_t mem_idx);

#endif
