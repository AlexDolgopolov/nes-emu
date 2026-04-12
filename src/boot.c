#include "boot.h"
#include <stdio.h>
#include "framebuffero.h"
#include "6502_mem.h"
FILE* nes_file;
RomMetaDataType rom_meta;



static void read_rom_data(FILE* file, uint8_t* buffer, size_t size){
	for(size_t i=0;i<size;i++){
		int byte;
		byte = fgetc(file);
		if(byte == EOF){
			printf("Unexpected EOF. Error");
			fflush(stdout);
			while(1);
		}
		if(buffer != NULL){
			*buffer = (uint8_t)byte;
			buffer++;	
		}
	}
}

uint8_t temp_chr_mem[1*8192];
uint8_t temp_prg_mem[2*16384];
extern uint8_t cpu_ram[0x10000];


void boot(const char* path){
	framebuffero_init();
	nes_file = fopen(path, "rb");
	uint8_t magic_word[4];
	read_rom_data(nes_file, magic_word, 4);
	read_rom_data(nes_file, &(rom_meta.prg_rom_size), 1);
	read_rom_data(nes_file, &(rom_meta.chr_rom_size), 1);
	uint32_t psize = rom_meta.prg_rom_size * 16384;
	uint32_t ssize = rom_meta.chr_rom_size * 8192;
	uint8_t flag0;
	read_rom_data(nes_file, &flag0, 1);
	uint8_t flag1;
	read_rom_data(nes_file, &flag1, 1);
	printf("%.*s\n", 4, magic_word);
	printf("prg_rom = %d\n", rom_meta.prg_rom_size);
	printf("chr_rom = %d\n", rom_meta.chr_rom_size);
	printf("flag0 = %x\n", flag0);
	printf("flag1 = %x\n", flag1);
	fflush(stdout);
	uint8_t reserved[8];
	read_rom_data(nes_file, reserved, 8);
	read_rom_data(nes_file, temp_prg_mem, psize);

	for(uint32_t i=0;i<psize;i++){
		write_ram(i+0x8000, temp_prg_mem[i]);
	}

	read_rom_data(nes_file, temp_chr_mem, ssize);
	for(uint32_t i=0;i<ssize;i++){
		ppu_write(i, temp_chr_mem[i]);
	}

}