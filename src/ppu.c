#include <stdio.h>
#include <stdint.h>
#include "ppu.h"

uint8_t pattern_table[0x2000];
uint8_t nametable[0x1000];
PPUScrollingType scrolling;
uint8_t palette[32];
uint8_t oam_memory[256];
PPUState ppu;

uint8_t read_ppu_reg(PPURegisterType reg){
	switch(reg){
		case PPUCTRL:{
			//ERROR
			printf("Warning: PPUCTRL read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case PPUMASK:{
			//ERROR
			printf("Warning: PPUMASK read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case PPUSTATUS:{
			uint8_t retval = ppu.ppu_status;
			ppu.w = 0;
			ppu.ppu_status &= ~(1 << 7);
			return retval;
		}
		case OAMADDR:{
			//ERROR
			printf("Warning: OAMADDR read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case OAMDATA:{
			uint8_t retval = oam_memory[ppu.oam_addr];
			return retval;
		}
		case PPUSCROLL:{
			//ERROR
			printf("Warning: PPUSCROLL read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case PPUADDR:{
			//ERROR
			printf("Warning: PPUADDR read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case PPUDATA:{
			uint8_t retval;
			if(ppu.current_vram_addr >= 0x3f00 && ppu.current_vram_addr <= 0x3fff){
				// palette
				retval = ppu_read(ppu.current_vram_addr);
				ppu.ppudata_buffer = ppu_read(ppu.current_vram_addr & ~(1 << 12)); // palette mirroring
			} else {
				// other mem
				retval = ppu.ppudata_buffer;
				ppu.ppudata_buffer = ppu_read(ppu.current_vram_addr);
			}
			ppu.current_vram_addr += ((ppu.ppuctrl & (1 << 2)) != 0) ? 32 : 1;
			return retval;
		}
		default:{
			printf("Error: Undefined register");
			fflush(stdout);
			while(1);
		}
	}
	return 0x0;
}
void write_ppu_reg(PPURegisterType reg, uint8_t data){
	switch(reg){
		case PPUCTRL:{
			ppu.ppuctrl = data;
			return;
		}
		case PPUMASK:{
			ppu.ppumask = data;
			return;
		}
		case PPUSTATUS:{
			printf("Warning: PPUSTATUS write attempt\n");
			fflush(stdout);
			return;
		}
		case OAMADDR:{
			ppu.oam_addr = data;
			return;
		}
		case OAMDATA:{
			oam_memory[ppu.oam_addr] = data;
			ppu.oam_addr += 1;
			return;
		}
		case PPUSCROLL:{
			if(ppu.w == 0){
				ppu.x_pos = data;
				ppu.w = 1;
			} else {
				ppu.y_pos = data;
				ppu.w = 0;
			}
			return;
		}
		case PPUADDR:{
			if(ppu.w == 0){
				ppu.current_vram_addr = (ppu.current_vram_addr & 0x00ff) | (data << 8);
				ppu.w = 1;
			} else {
				ppu.current_vram_addr = (ppu.current_vram_addr & 0xff00) | (data);
				ppu.w = 0;
			}
		}
		case PPUDATA:{
			ppu_write(ppu.current_vram_addr, data);
			ppu.current_vram_addr += ((ppu.ppuctrl & (1 << 2)) != 0) ? 32 : 1;
			return;
		}
		default:{
			printf("Error: Undefined register");
			fflush(stdout);
			while(1);
		}
	}
	return;
}

uint8_t ppu_read(uint16_t address){
	address &= 0x3fff;
	if(address >= 0x0 && address <= 0x1fff){
		// TODO MAPPER
		return pattern_table[address];
	} else if(address >= 0x2000 && address <= 0x3eff){
		if(address>=0x3000) address -= 0x1000;
		uint16_t addr_in_page = address & 0x3ff;
		uint16_t page = 0;
		if(scrolling == ScrollingSS){
			return nametable[addr_in_page];
		} else if(scrolling == ScrollingFS){
			page = (address & (0b11 << 10));
			return nametable[page | addr_in_page];
		} else if(scrolling == ScrollingRL){
			page = (address & (0b1 << 10)) >> 10;
			if(page == 0) 	return(nametable[addr_in_page]);
			else 			return(nametable[addr_in_page+0x400]);
		} else {
			//ScrollingUD
			page = (address & (0b10 << 10)) >> 11;
			if(page == 0) 	return(nametable[addr_in_page]);
			else 			return(nametable[addr_in_page+0x400]);
		}
	} else if(address >= 0x3f00 && address <= 0x3fff){
		if ((address & 0x0003) == 0) address &= 0x000f;
		return palette[address & 0x1f];
	} else {
		return 0x0;
	}
}
void ppu_write(uint16_t address, uint8_t data){
	address &= 0x3fff;
	if(address >= 0x0 && address <= 0x1fff){
		// TODO MAPPER
		pattern_table[address] = data;
	} else if(address >= 0x2000 && address <= 0x3eff){
		if(address>=0x3000) address -= 0x1000;
		uint16_t addr_in_page = address & 0x3ff;
		uint16_t page = 0;
		if(scrolling == ScrollingSS){
			nametable[addr_in_page] = data;
		} else if(scrolling == ScrollingFS){
			page = (address & (0b11 << 10));
			nametable[page | addr_in_page] = data;
		} else if(scrolling == ScrollingRL){
			page = (address & (0b1 << 10)) >> 10;
			if(page == 0) 	nametable[addr_in_page] = data;
			else 			nametable[addr_in_page+0x400] = data;
		} else {
			//ScrollingUD
			page = (address & (0b10 << 10)) >> 11;
			if(page == 0) 	nametable[addr_in_page] = data;
			else 			nametable[addr_in_page+0x400] = data;
		}
	} else if(address >= 0x3f00 && address <= 0x3fff){
		if ((address & 0x0003) == 0) address &= 0x000f;
		palette[address & 0x1f] = data;
	} else {
		while(1);
	}
}
