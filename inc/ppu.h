#ifndef PPU_H
#define PPU_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <framebuffero.h>

typedef enum{
	ScrollingSS, // single screen
	ScrollingRL, // right-left
	ScrollingUD, // up-down
	ScrollingFS  // four screen
} PPUScrollingType;

typedef enum{
	PPUCTRL,
	PPUMASK,
	PPUSTATUS,
	OAMADDR,
	OAMDATA,
	PPUSCROLL,
	PPUADDR,
	PPUDATA
} PPURegisterType;

typedef struct{
	uint16_t scanline;
	uint16_t cycle;
	uint16_t x_pos;
	uint16_t y_pos;
	uint8_t w;
	uint8_t ppuctrl;
	uint8_t ppumask;
	uint8_t ppu_status;
	uint8_t oam_addr;
	uint16_t current_vram_addr;
	uint8_t ppudata_buffer;
	uint16_t scroll_t;
	uint8_t fine_x;
} PPUState;

uint32_t* get_framebuffer_ptr();
void write_oam_data(uint8_t addr, uint8_t data);
void ppu_render_frame();
void ppu_powerup();
void ppu_tick();
bool get_ppu_nmi();
uint8_t read_ppu_reg(PPURegisterType reg);
void write_ppu_reg(PPURegisterType reg, uint8_t data);
uint8_t ppu_read(uint16_t address);
void ppu_write(uint16_t address, uint8_t data);

#endif