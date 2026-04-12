#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "cpu.h"
#include "ppu.h"
#include <stdbool.h>
#include "6502_mem.h"

void check_interrupt(CpuStateTypedef* cpu);

#endif