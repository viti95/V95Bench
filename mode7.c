/* 
 * This file is part of the V95bench distribution (https://github.com/viti95/V95bench).
 * Copyright (c) 2022 Víctor Nieto.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "mode7.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PREHEAT_LOOPS 400
#define BENCH_TIME 5000

unsigned int total_loops_mode7;
unsigned long timespent_mode7;

void init_mode7(void)
{
    union REGS regs;

    // Set video mode 7
    regs.w.ax = 0x07;
    int386(0x10, (union REGS *)&regs, &regs);
}

void preheat_mode7(void)
{
    unsigned int loops;
    unsigned char *vram;

    for (loops = 0; loops < PREHEAT_LOOPS; loops++)
    {
        for (vram = (unsigned char *)0xB0000; vram < (unsigned char *)0xB0FA0; vram += 8)
        {
            *(vram) = 0x55;
            *(vram + 1) = 0x55;
            *(vram + 2) = 0x55;
            *(vram + 3) = 0x55;
            *(vram + 4) = 0x55;
            *(vram + 5) = 0x55;
            *(vram + 6) = 0x55;
            *(vram + 7) = 0x55;
        }
    }
}

void bench_mode7(void)
{
    unsigned char *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops_mode7;

    for (loops = 0; loops < num_loops; loops++)
    {
        for (vram = (unsigned char *)0xB0000; vram < (unsigned char *)0xB0FA0; vram += 8)
        {
            *(vram) = 0x55;
            *(vram + 1) = 0x55;
            *(vram + 2) = 0x55;
            *(vram + 3) = 0x55;
            *(vram + 4) = 0x55;
            *(vram + 5) = 0x55;
            *(vram + 6) = 0x55;
            *(vram + 7) = 0x55;
        }
    }
}

void execute_bench_mode7(void)
{
    // SET VIDEO MODE
    init_mode7();

    // PRE-HEAT
    timespent_mode7 = profile_function(preheat_mode7);
    total_loops_mode7 = PREHEAT_LOOPS * BENCH_TIME / timespent_mode7;

    // BENCHMARK
    timespent_mode7 = profile_function(bench_mode7);
}

void show_results_mode7(void)
{
    double total_result;

    total_result = ((double)total_loops_mode7 * 3.90625 * 1000) / ((double)timespent_mode7);
    printf("TXT 80x25 2c: %.2lf kb/s\n", total_result);
}
