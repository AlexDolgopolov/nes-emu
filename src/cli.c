#include "cli.h"
#include <stdio.h>
#include <string.h>
#include "6502_mem.h"
#include "cpu.h"

uint32_t process_cli(CpuStateTypedef* cpu){
  char strbuf[100] = {0};
  scanf("%s", strbuf);
  if(strcmp(strbuf, "WREGISTERS") == 0){
    uint32_t pc, s, a, x, y, p;
    scanf("%d", &pc);
    scanf("%d", &s);
    scanf("%d", &a);
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &p);
    cpu->PC     = pc;
    cpu->S      = s;
    cpu->A      = a;
    cpu->X      = x;
    cpu->Y      = y;
    cpu->P_val  = p;
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "RREGISTERS") == 0){
    printf("pc = 0x%x\n",cpu->PC);
    fflush(stdout);
    printf("s =  0x%x\n",cpu->S);
    fflush(stdout);
    printf("a =  0x%x\n",cpu->A);
    fflush(stdout);
    printf("x =  0x%x\n",cpu->X);
    fflush(stdout);
    printf("y =  0x%x\n",cpu->Y);
    fflush(stdout);
    printf("p =  0x%x\n",cpu->P_val);
    fflush(stdout);
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "WMEMORY") == 0){
    uint32_t addr, val;
    scanf("%d", &addr);
    scanf("%d", &val);
    write_ram((uint16_t)addr, (uint8_t)val);
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "RMEMORY") == 0){
    uint32_t addr, memory;
    scanf("%d", &addr);
    memory = read_ram(addr);
    printf("value on address 0x%x = 0x%x\n", addr, memory);
    fflush(stdout);
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "STEP") == 0){
    cpu_tick(cpu);
    printf("OK\n");
    fflush(stdout);
    return 1;
  } else if(strcmp(strbuf, "END") == 0){
    printf("PROCESSOR SHUT DOWN\n");
    printf("OK\n");
    fflush(stdout);
    return 0;
  } else {
    printf("ERROR\n");
    fflush(stdout);
    return 0;
  }
}
