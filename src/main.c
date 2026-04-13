#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h> 
#include <stdio.h>
#include <string.h>
#include "nes_cycle.h"
#include "cli.h"
#include "boot.h"
#include "framebuffero.h"
CpuStateTypedef cpu;
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Not valid argc\n");
    fflush(stdout);
    return 1;
  } else {
    if(strcmp(argv[1], "0") == 0){
    // WORK MODE
      printf("%s, WORK MODE NOT IMPLEMENTED\n", argv[1]);
      fflush(stdout);
      boot("../rom/smb.nes");
      framebuffero_init();
      cpu_powerup(&cpu);
      ppu_powerup();
      nes_cycle();
      printf("PROCESSOR SHUT DOWN\n");
      fflush(stdout);
      return 1;
    } else if(strcmp(argv[1], "1") == 0){
      printf("%s, TEST MODE\n", argv[1]);
      fflush(stdout);
      while(process_cli(&cpu) != 0);
      printf("PROCESSOR SHUT DOWN\n");
      fflush(stdout);
      return 0;
    } else if(strcmp(argv[1], "2") == 0){
      // BOOT TEST MODE
      printf("%s, TEST MODE\n", argv[1]);
      fflush(stdout);
      process_cli(&cpu);
      printf("PROCESSOR SHUT DOWN\n");
      fflush(stdout);
      return 0;
    } else {
      printf("%s, UNKNOWN MODE\n", argv[1]);
      fflush(stdout);
      printf("PROCESSOR SHUT DOWN\n");
      fflush(stdout);
      return 2;
    }
    return 0;
  }
};
