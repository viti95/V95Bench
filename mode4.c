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

#include "mode4.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define PREHEAT_LOOPS 100
#define BENCH_TIME 5000

unsigned int total_loops_mode4;
unsigned long timespent_mode4;

void init_mode4(void)
{
    union REGS regs;

    // Set video mode 4
    regs.w.ax = 0x04;
    int386(0x10, (union REGS *)&regs, &regs);
}

void preheat_mode4(void)
{
    unsigned int loops;
    unsigned char *vram;

    for (loops = 0; loops < PREHEAT_LOOPS; loops++)
    {
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB9F40; vram += 4)
        {
            *(vram) = 0x55;
            *(vram + 1) = 0x55;
            *(vram + 2) = 0x55;
            *(vram + 3) = 0x55;
            *(vram + 0x2000) = 0x55;
            *(vram + 0x2001) = 0x55;
            *(vram + 0x2002) = 0x55;
            *(vram + 0x2003) = 0x55;
        }
    }
}

void bench_mode4(void)
{
    unsigned char *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops_mode4;

    for (loops = 0; loops < num_loops; loops++)
    {
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB9F40; vram += 4)
        {
            *(vram) = 0x55;
            *(vram + 1) = 0x55;
            *(vram + 2) = 0x55;
            *(vram + 3) = 0x55;
            *(vram + 0x2000) = 0x55;
            *(vram + 0x2001) = 0x55;
            *(vram + 0x2002) = 0x55;
            *(vram + 0x2003) = 0x55;
        }
    }
}

void execute_bench_mode4(void)
{
    // SET VIDEO MODE
    init_mode4();

    // PRE-HEAT
    timespent_mode4 = profile_function(preheat_mode4);
    total_loops_mode4 = PREHEAT_LOOPS * BENCH_TIME / timespent_mode4;

    // BENCHMARK
    timespent_mode4 = profile_function(bench_mode4);
}

void show_results_mode4(void)
{
    double total_result;

    total_result = ((double)total_loops_mode4 * 15.625 * 1000) / ((double)timespent_mode4);
    printf("CGA Mode 4: %.2lf kb/s\n", total_result);
}
