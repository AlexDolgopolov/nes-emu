#include "ppu.h"
#include "debug.h"

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
uint8_t  bg_opaque[256] = {1};

uint32_t* get_framebuffer_ptr(){
	return framebuffer;
}

void write_oam_data(uint8_t addr, uint8_t data){
	oam_memory[addr] = data;
}

void ppu_render_line(uint16_t line){
	uint16_t scroll_x = ppu.x_pos + (ppu.ppuctrl & 0x01) * 256;
	uint16_t scroll_y = ppu.y_pos + ((ppu.ppuctrl >> 1) & 0x01) * 240;
	uint16_t world_y = (line + scroll_y) % 480;
	uint16_t local_y = world_y % 240;
	uint16_t tile_y = local_y / 8;
	uint16_t pixel_y = local_y % 8;
	for(int screen_x = 0; screen_x < 256; screen_x++){
			uint16_t world_x = (screen_x + scroll_x) % 512;
			
        	uint16_t nametable_base = 0x2000 + (world_x / 256) * 0x0400 + (world_y / 240) * 0x0800;
       
        	uint16_t local_x = world_x % 256;
        
        	uint16_t tile_x = local_x / 8;
        	uint16_t pixel_x = local_x % 8;
        
        	uint16_t tile_id = ppu_read(nametable_base + tile_y * 32 + tile_x);
        
	        // Атрибуты
    	    uint16_t attribute_base = nametable_base + 0x03C0;
        	uint16_t attribute_byte = ppu_read(attribute_base + (tile_y/4)*8 + (tile_x/4));
        	uint16_t shift = ((tile_y%4)/2)*4 + ((tile_x%4)/2)*2;
        	uint16_t palette_number = (attribute_byte >> shift) & 0x03;
        
	        // Паттерн
        	uint16_t pattern_base = ((ppu.ppuctrl & 0x10) ? 0x1000 : 0x0000);
        	uint16_t tile_addr = pattern_base + tile_id * 16;
        	uint16_t lb = ppu_read(tile_addr + pixel_y);
        	uint16_t hb = ppu_read(tile_addr + pixel_y + 8);
        	uint16_t bit = 7 - pixel_x;
        	uint16_t color_idx = ((hb >> bit) & 1) << 1 | ((lb >> bit) & 1);
		    
        	// Цвет
        	uint16_t color_code = (color_idx == 0) ? ppu_read(0x3F00) : ppu_read(0x3F00 + palette_number*4 + color_idx);
        	bg_opaque[screen_x] = (color_idx != 0) ? 1 : 0;
        	framebuffer[line * 256 + screen_x] = nes_palette[color_code & 0x3f];
	}
	// sprite render
	uint16_t base_addr = (ppu.ppuctrl & (1 << 3)) != 0 ? 0x1000 : 0x0000;
	uint8_t* sprite_data = &oam_memory[252];
	for(int sprite = 63; sprite >= 0; sprite--){
		uint16_t screen_y = sprite_data[0]+1;
		uint8_t row = line - screen_y;
		uint8_t tile_id = sprite_data[1];
		uint8_t attributes = sprite_data[2];
		uint8_t oam_x = sprite_data[3];
		sprite_data-=4;
		if(line < screen_y || line > (screen_y +7) || screen_y >= 240) continue;
		uint16_t tile_addr = base_addr + tile_id * 16;
		uint8_t palette_number = attributes & 0x03;          // биты 0-1
		uint8_t priority       = (attributes >> 5) & 0x01;   // бит 5
		uint8_t flip_h         = (attributes >> 6) & 0x01;   // бит 6
		uint8_t flip_v         = (attributes >> 7) & 0x01;   // бит 7
		uint8_t actual_row = flip_v == 1 ? 7 - row : row;
		uint8_t lb = ppu_read(tile_addr + actual_row);       // младший битплейн
		uint8_t hb = ppu_read(tile_addr + actual_row + 8);   // старший битплейн
		for(uint8_t col = 0; col < 8;col++){
			uint8_t bit_position = flip_h == 1 ? col : 7 - col;
			uint8_t low_bit  = (lb >> bit_position) & 1;
			uint8_t high_bit = (hb >> bit_position) & 1;
			uint8_t color_idx = (high_bit << 1) | low_bit;
			uint16_t px = oam_x + col;
			if(color_idx == 0) continue;
			if(sprite == 0){
				printf("[\n");
				printf("sprite0: %d, %d\n", px, line);
				printf("bg_opaque = %d\n", bg_opaque[px]);
				printf("]\n");
				if(
					//(bg_opaque[px] == true) && 
					(ppu.ppumask & 0x18)){
					// sprite 0 hit
					printf("sprite 0 hit\n");
					ppu.ppu_status |= 1 << 6;
				}	
			}
			if(px >= 256) continue;
			if(priority == 1 && (bg_opaque[px] != 0)) continue;
			uint8_t color_code = ppu_read(0x3F10 + palette_number * 4 + color_idx);
			framebuffer[line * 256 + px] = nes_palette[color_code & 0x3f];
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
	if((ppu.scanline < 240) && (ppu.cycle == 1)) ppu_render_line(ppu.scanline);
	if((ppu.scanline == 240) && (ppu.cycle == 1)) framebuffero_output();
	if((ppu.scanline == 241) && (ppu.cycle == 1)) ppu.ppu_status |= 1 << 7;
	if((ppu.scanline == 261) && (ppu.cycle == 1)) ppu.ppu_status &= ~(0b111 << 5);
	if(ppu.scanline == 262){
		ppu.scanline = 0;
	}
}

uint8_t read_ppu_reg(PPURegisterType reg){
	DEBUG_PPU("read ppu reg\n");
	switch(reg){
		case PPUCTRL:{
			DEBUG_PPU("PPUCTRL\n");
			//ERROR
			DEBUG_PPU("Warning: PPUCTRL read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case PPUMASK:{
			DEBUG_PPU("PPUMASK\n");
			//ERROR
			DEBUG_PPU("Warning: PPUMASK read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case PPUSTATUS:{
			DEBUG_PPU("PPUSTATUS, %x\n", ppu.ppu_status);
			uint8_t retval = ppu.ppu_status;
			ppu.w = 0;
			ppu.ppu_status &= ~(1 << 7);
			return retval;
		}
		case OAMADDR:{
			DEBUG_PPU("OAMADDR\n");
			//ERROR
			DEBUG_PPU("Warning: OAMADDR read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case OAMDATA:{
			DEBUG_PPU("OAMDATA\n");
			uint8_t retval = oam_memory[ppu.oam_addr];
			return retval;
		}
		case PPUSCROLL:{
			DEBUG_PPU("PPUSCROLL\n");
			//ERROR
			DEBUG_PPU("Warning: PPUSCROLL read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case PPUADDR:{
			DEBUG_PPU("PPUADDR\n");
			//ERROR
			DEBUG_PPU("Warning: PPUADDR read attempt\n");
			fflush(stdout);
			return 0x0;
		}
		case PPUDATA:{
			DEBUG_PPU("PPUDATA\n");
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
			DEBUG_PPU("Error: Undefined register");
			fflush(stdout);
			while(1);
		}
	}
	return 0x0;
}
void write_ppu_reg(PPURegisterType reg, uint8_t data){
	DEBUG_PPU("write ppu reg\n");
	switch(reg){
		case PPUCTRL:{
			DEBUG_PPU("PPUCTRL, %x\n", data);

			ppu.ppuctrl = data;
			return;
		}
		case PPUMASK:{
			DEBUG_PPU("PPUMASK: %x\n", data);
			ppu.ppumask = data;
			return;
		}
		case PPUSTATUS:{
			DEBUG_PPU("PPUSTATUS\n");
			DEBUG_PPU("Warning: PPUSTATUS write attempt\n");
			fflush(stdout);
			return;
		}
		case OAMADDR:{
			DEBUG_PPU("OAMADDR: %x\n", data);
			ppu.oam_addr = data;
			return;
		}
		case OAMDATA:{
			DEBUG_PPU("OAMDATA: %x\n", data);
			oam_memory[ppu.oam_addr] = data;
			ppu.oam_addr += 1;
			return;
		}
		case PPUSCROLL:{
			DEBUG_PPU("PPUSCROLL\n");
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
			DEBUG_PPU("PPUADDR: %x\n", data);
			if(ppu.w == 0){
				ppu.current_vram_addr = (ppu.current_vram_addr & 0x00ff) | (data << 8);
				ppu.w = 1;
			} else {
				ppu.current_vram_addr = (ppu.current_vram_addr & 0xff00) | (data);
				ppu.w = 0;
			}
			return;
		}
		case PPUDATA:{
			DEBUG_PPU("PPUDATA: %x\n", data);
			ppu_write(ppu.current_vram_addr, data);
			ppu.current_vram_addr += ((ppu.ppuctrl & (1 << 2)) != 0) ? 32 : 1;
			return;
		}
		default:{
			DEBUG_PPU("Error: Undefined register");
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