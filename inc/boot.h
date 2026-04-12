#ifndef BOOT_H
#define BOOT_H

#include <stdint.h>
#include <stdbool.h>
#include <ppu.h>

typedef enum{
	NO_MAPPER,
	UNKNOWN
} MapperType;

typedef struct{
	uint8_t prg_rom_size;
	uint8_t chr_rom_size;
	PPUScrollingType scrolling;
	uint32_t sram_size;
	MapperType mapper;
} RomMetaDataType;

void boot(const char* path);

#endif