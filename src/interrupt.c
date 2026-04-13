#include "interrupt.h"
#include <stdio.h>
#include "debug.h"

bool nmi = false;

void check_interrupt(CpuStateTypedef* cpu){
	bool new_nmi = get_ppu_nmi();
	bool nmi_edge = (!nmi && new_nmi);
	nmi = new_nmi;
	if(nmi_edge){
		DEBUG_PPU("nmi\n");
		fflush(stdout);
		push_stack(&(cpu->S), (uint8_t)(cpu->PC >> 8));
		push_stack(&(cpu->S), (uint8_t)(cpu->PC));
		uint8_t status = cpu->P_val;
		status = (status & ~(1 << 4));
		push_stack(&(cpu->S), status);
		cpu->P_bit.I = 1;
		uint8_t pc_lb = read_ram(0xfffa);
		uint8_t pc_hb = read_ram(0xfffb);
		cpu->PC = (pc_hb << 8) | pc_lb;
	}
}