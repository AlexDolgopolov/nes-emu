#include "addrmode.h"

RetAddress addrmode_IMP(CpuStateTypedef* cpu){
    RetAddress retval = {.address = 0x0, .page_crossing = false};
    return retval;
} // Implicit

RetAddress addrmode_IMM(CpuStateTypedef* cpu){
    RetAddress retval = {.address = cpu->PC+1, .page_crossing = false};
    return retval;
} // Immediate

#define addrmode_REL addrmode_IMM

RetAddress addrmode_ABS(CpuStateTypedef* cpu){
    RetAddress retval = {.address = ((cpu->PC+2) << 8) | (cpu->PC+1), .page_crossing = false};
    return retval;
} // Absolute

RetAddress addrmode_ABSX(CpuStateTypedef* cpu){
    uint16_t address_base = ((cpu->PC+2) << 8) | (cpu->PC+1);
    RetAddress retval = {.address =  address_base+(cpu->X), .page_crossing = false};
    if((retval.address & 0xff00) != (address_base & 0xff00)) retval.page_crossing = true;
    return retval;
}// Absolute, X
RetAddress addrmode_ABSY(CpuStateTypedef* cpu){
    uint16_t address_base = ((cpu->PC+2) << 8) | (cpu->PC+1);
    RetAddress retval = {.address =  address_base+(cpu->Y), .page_crossing = false};
    if((retval.address & 0xff00) != (address_base & 0xff00)) retval.page_crossing = true;
    return retval;
}// Absolute, Y
RetAddress addrmode_ZP(CpuStateTypedef* cpu){
    RetAddress retval = {.address = 0x0 | (cpu->PC+1), .page_crossing = false};
    return retval;
}  // Zero Page
RetAddress addrmode_ZPX(CpuStateTypedef* cpu){
    RetAddress retval = {.address = ((0x0 | (cpu->PC+1))+cpu->X) & 0xff, .page_crossing = false};
    return retval;
} // Zero Page, X
RetAddress addrmode_ZPY(CpuStateTypedef* cpu){
    RetAddress retval = {.address = ((0x0 | (cpu->PC+1))+cpu->Y) & 0xff, .page_crossing = false};
    return retval;
} // Zero Page, Y
RetAddress addrmode_IND(CpuStateTypedef* cpu){
    uint16_t addr_ptr = (read_ram(cpu->PC+2) << 8) | read_ram(cpu->PC+1);
    RetAddress retval = {.address = addr_ptr, .page_crossing = false};
    return retval;
} // Indirect
RetAddress addrmode_INDX(CpuStateTypedef* cpu){
    uint16_t addr_ptr = (read_ram(cpu->PC+2) << 8) | read_ram(cpu->PC+1);
    uint16_t real_addr = (read_ram(addr_ptr+1) << 8) | (read_ram(addr_ptr) + cpu->X);
    RetAddress retval = {.address = real_addr, .page_crossing = false};
    return retval;
}// (Indirect, X)
RetAddress addrmode_INDY(CpuStateTypedef* cpu){
    uint16_t addr_ptr = (read_ram(cpu->PC+2) << 8) | read_ram(cpu->PC+1);
    uint16_t real_addr = (read_ram(addr_ptr+1) << 8) | (read_ram(addr_ptr));
    RetAddress retval = {.address = real_addr + cpu->Y, .page_crossing = false};
    if((real_addr & 0xff00) != ((real_addr+cpu->Y) & 0xff00)) retval.page_crossing = true;
    return retval;
} // (Indirect), Y
