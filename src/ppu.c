#include "ppu.h"

uint8_t pattern_table[0x2000];
uint8_t nametable[0x1000];
PPUScrollingType scrolling;
uint8_t palette[32];
uint8_t oam_memory[256];

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
