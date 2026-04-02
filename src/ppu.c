#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ppu.h"

uint8_t pattern_table[0x2000];
uint8_t nametable[0x1000];
PPUScrollingType scrolling;
uint8_t palette[32];
uint8_t oam_memory[256];
PPUState ppu;
bool ppu_vblank_nmi;

const uint32_t nes_palette[64] = {
    0x545454, 0x001E74, 0x081090, 0x300088, 0x440064, 0x5C0030, 0x540400, 0x3C1800,
    0x202A00, 0x083A00, 0x004000, 0x003C00, 0x00323C, 0x000000, 0x000000, 0x000000,
    0x989698, 0x084CC4, 0x3032EC, 0x5C1EE4, 0x8814B0, 0xA01464, 0x982220, 0x783C00,
    0x545A00, 0x287200, 0x087C00, 0x007628, 0x006678, 0x000000, 0x000000, 0x000000,
    0xECEEEC, 0x4C9AEC, 0x787CEC, 0xB062EC, 0xE454EC, 0xEC58B4, 0xEC6A64, 0xD48820,
    0xA0AA00, 0x74C400, 0x4CD020, 0x38CC6C, 0x38B4CC, 0x3C3C3C, 0x000000, 0x000000,
    0xECEEEC, 0xA8CCEC, 0xBCBCEC, 0xD4B2EC, 0xECAEEC, 0xECAED4, 0xECB4B0, 0xE4C490,
    0xCCD278, 0xB4DE78, 0xA8E290, 0x98E2B4, 0xA0D6E4, 0xA0A2A0, 0x000000, 0x000000
};

uint32_t framebuffer[256 * 240];

void ppu_render_frame(){
	for(uint8_t tile_y = 0;tile_y < 30;tile_y++){
		for(uint8_t tile_x = 0;tile_x < 32;tile_x++){
			uint8_t tile_id = ppu_read(0x2000 + tile_y * 32 + tile_x);
			uint8_t palette_number = (ppu_read(0x23C0 + (tile_y / 4) * 8 + (tile_x / 4)) >> (((tile_y % 4) / 2) * 4 + ((tile_x % 4) / 2) * 2)) & 0x03;
			uint16_t pattern_table_addr = (((ppu.ppuctrl & (1 << 4)) == 0) ? 0 : 0x1000) + tile_id * 16;
			for(uint8_t row = 0;row<8;row++){
				uint8_t lb = pattern_table[pattern_table_addr+row];
				uint8_t hb = pattern_table[pattern_table_addr+row+8];
				for(uint8_t col = 0;col<8;col++){
					uint8_t color_idx = ((hb >> 6) | (lb >> 7)) & 0b11;
					lb <<= 1;
					hb <<= 1;
					uint8_t framebuffer_x = tile_x * 8 + col;
					uint8_t framebuffer_y = tile_y * 8 + row;
					uint8_t color_code = color_idx == 0 ? ppu_read(0x3f00) : ppu_read(0x3f00+(palette_number*4)+color_idx);
					framebuffer[framebuffer_y*256+framebuffer_x] = nes_palette[color_code];
				}
			}
		}	
	}
}

void ppu_powerup(){
	ppu_vblank_nmi = 0;
	ppu.scanline = 0;
	ppu.cycle = 0;
	ppu.x_pos = 0;
	ppu.y_pos = 0;
	ppu.w = 0;
	ppu.ppuctrl = 0;
	ppu.ppumask = 0;
	ppu.ppu_status = 0; 
	ppu.oam_addr = 0;
	ppu.current_vram_addr = 0;
	ppu.ppudata_buffer = 0;
}

bool get_ppu_nmi(){
	return ppu_vblank_nmi;
}

void ppu_tick(){
	ppu_vblank_nmi = ((ppu.ppuctrl & ppu.ppu_status) & (1 << 7)) != 0;
	if((++ppu.cycle) > 340){
		ppu.cycle = 0;
		ppu.scanline++;
	}
	if((ppu.scanline == 241) && (ppu.cycle == 1)) ppu.ppu_status |= 1 << 7;
	if((ppu.scanline == 261) && (ppu.cycle == 1)) ppu.ppu_status &= ~(0b111 << 5);
	if(ppu.scanline == 262)	ppu.scanline = 0;
}

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
