#include <stdio.h>
#include <cpu.h>

CpuStateTypedef cpu;

int main(){
  cpu_powerup(&cpu);
  printf("Hello, World!\n");
  return 1;
};
