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

void nes_cycle(){
    timer_init();

    uint64_t next_frame = get_us();

    while (1) {
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