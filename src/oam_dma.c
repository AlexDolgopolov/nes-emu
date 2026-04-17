#include "oam_dma.h"
#include "debug.h"


void write_oam_dma(uint8_t arg){
	DEBUG("DMA START WORKING FOR 256 CPU CYCLES\n");
	uint16_t start_addr = arg << 8;
	for(uint16_t i=0;i<256;i++){
		write_oam_data((uint8_t)i, read_ram(start_addr+i));	
	}
	set_wait_cycle(513);
}