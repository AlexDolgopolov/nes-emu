#include <stdio.h>
#include <cpu.h>

CpuStateTypedef cpu;

int main(int argc, char *argv[]){
  if(argc != 2){
    fprintf(stderr, "Not valid argc");
    return 1;
  } else {

    cpu_powerup(&cpu);
    printf("Hello, World!\n");
    return 0;
  }
};
