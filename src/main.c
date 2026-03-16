#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "cli.h"
CpuStateTypedef cpu;

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
      cpu_powerup(&cpu);
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
