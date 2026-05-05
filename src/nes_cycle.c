/*
 * NES-emu
 * Copyright (C) 2026 Alex Dolgopolov
 *
 * This file is part of NES-emu.
 *
 * NES-emu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NES-emu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with NES-emu. If not, see <https://www.gnu.org/licenses/>.
 */

#include "nes_cycle.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "cpu.h"
#include "ppu.h"

extern CpuStateTypedef cpu;

#ifdef _WIN32
    #include <windows.h>
    
    static LARGE_INTEGER pf;
    
    void timer_init(void) {
        QueryPerformanceFrequency(&pf);
        timeBeginPeriod(1);
    }
    
    uint64_t get_us(void) {
        LARGE_INTEGER pc;
        QueryPerformanceCounter(&pc);
        return (uint64_t)(pc.QuadPart * 1000000 / pf.QuadPart);
    }

#elif defined(__linux__) || defined(__APPLE__)
    #include <time.h>
    
    void timer_init(void) {}
    
    uint64_t get_us(void) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return (uint64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }

#else
    void timer_init(void) {}
    uint64_t get_us(void) { return 0; }
#endif

#define CPU_PER_FRAME   29781
#define FRAME_US        16639

bool nes_running = true;

void nes_cycle(){
    timer_init();

    uint64_t next_frame = get_us();

    while (nes_running) {
        for (int i = 0; i < CPU_PER_FRAME; i++) {
            cpu_tick(&cpu);
            ppu_tick();
            ppu_tick();
            ppu_tick();
        }

        next_frame += FRAME_US;
        while (get_us() < next_frame);
    }
}