#include "addrmode.h"
#include <stdio.h>
#include "debug.h"


RetAddress addrmode_IMP(CpuStateTypedef* cpu){
    RetAddress retval = {.address = 0x0, .page_crossing = false};
    retval.pc_inc = 1;
    return retval;
} // Implicit

RetAddress addrmode_IMM(CpuStateTypedef* cpu){
    RetAddress retval = {.address = cpu->PC+1, .page_crossing = false};
    retval.pc_inc = 2;
    return retval;
} // Immediate

#define addrmode_REL addrmode_IMM

RetAddress addrmode_ABS(CpuStateTypedef* cpu){
    uint16_t address_base = (read_ram(cpu->PC+2) << 8) | read_ram(cpu->PC+1);
    DEBUG("ABS reading %x, address_base = %x\n", cpu->PC+1, address_base);
    RetAddress retval = {.address = address_base, .page_crossing = false};
    retval.pc_inc = 3;
    return retval;
} // Absolute

RetAddress addrmode_ABSX(CpuStateTypedef* cpu){
    uint16_t address_base = (read_ram(cpu->PC+2) << 8) | read_ram(cpu->PC+1);
    RetAddress retval = {.address =  address_base+(cpu->X), .page_crossing = false};
    if((retval.address & 0xff00) != (address_base & 0xff00)) retval.page_crossing = true;
    retval.pc_inc = 3;
    return retval;
}// Absolute, X
RetAddress addrmode_ABSY(CpuStateTypedef* cpu){
    uint16_t address_base = (read_ram(cpu->PC+2) << 8) | read_ram(cpu->PC+1);
    RetAddress retval = {.address =  address_base+(cpu->Y), .page_crossing = false};
    if((retval.address & 0xff00) != (address_base & 0xff00)) retval.page_crossing = true;
    retval.pc_inc = 3;
    return retval;
}// Absolute, Y
RetAddress addrmode_ZP(CpuStateTypedef* cpu){
    RetAddress retval = {.address = read_ram(0x0 | (cpu->PC+1)), .page_crossing = false};
    retval.pc_inc = 2;
    return retval;
}  // Zero Page
RetAddress addrmode_ZPX(CpuStateTypedef* cpu){
    DEBUG("VAL(cpu->PC+1) = %x\n",read_ram(cpu->PC+1));
    DEBUG("VAL(cpu->X) = %x\n",read_ram(cpu->X));
    RetAddress retval = {.address = read_ram(cpu->PC+1)+cpu->X & 0xff, .page_crossing = false};
    retval.pc_inc = 2;
    return retval;
} // Zero Page, X
RetAddress addrmode_ZPY(CpuStateTypedef* cpu){
    RetAddress retval = {.address = read_ram(cpu->PC+1)+cpu->Y & 0xff, .page_crossing = false};
    retval.pc_inc = 2;
    return retval;
} // Zero Page, Y
RetAddress addrmode_IND(CpuStateTypedef* cpu){
    uint16_t addr_ptr = (read_ram(cpu->PC+2) << 8) | read_ram(cpu->PC+1);
    DEBUG("IND: addr_ptr = 0x%04X\n", addr_ptr);
    DEBUG("IND: byte at 0x%04X = 0x%02X\n", addr_ptr, read_ram(addr_ptr));
    DEBUG("IND: byte at 0x%04X = 0x%02X\n", addr_ptr+1, read_ram(addr_ptr+1));
    
    uint16_t addr_base;
    if((addr_ptr & 0xff) == 0xff){
        //ind bug
        addr_base = (read_ram(addr_ptr & 0xff00) << 8) | read_ram(addr_ptr);
    } else {
        addr_base = (read_ram(addr_ptr+1) << 8) | read_ram(addr_ptr);
    }
    RetAddress retval = {.address = addr_base, .page_crossing = false};
    retval.pc_inc = 2;
    return retval;
} // Indirect
RetAddress addrmode_INDX(CpuStateTypedef* cpu){
    uint8_t arg_zp = read_ram(cpu->PC + 1) + cpu->X;
    uint8_t addr_lb = read_ram(arg_zp);
    uint8_t addr_hb = read_ram((arg_zp+1) & 0xff);
    uint16_t real_addr = (addr_hb << 8) | addr_lb;
    RetAddress retval = {.address = real_addr, .page_crossing = false};
    retval.pc_inc = 2;
    return retval;
}// (Indirect, X)
RetAddress addrmode_INDY(CpuStateTypedef* cpu){
    // Читаем ОДИН байт операнда — адрес в Zero Page
    uint8_t zp_addr = read_ram(cpu->PC + 1);
    
    // Читаем 16-битный указатель ИЗ Zero Page
    uint8_t low = read_ram(zp_addr);
    uint8_t high = read_ram((zp_addr + 1) & 0xFF);  // Оставаемся в Zero Page!
    uint16_t base_addr = (high << 8) | low;
    
    // Прибавляем Y
    uint16_t final_addr = base_addr + cpu->Y;
    
    RetAddress retval = {
        .address = final_addr,
        .page_crossing = ((base_addr & 0xFF00) != (final_addr & 0xFF00)),
        .pc_inc = 2  // Опкод + 1 байт операнда
    };
    
    return retval;
}
