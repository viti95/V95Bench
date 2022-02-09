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

#include "mode13.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PREHEAT_LOOPS 25
#define BENCH_TIME 5000

unsigned int total_loops_mode13;
unsigned long timespent_mode13;

void init_mode13(void)
{
    union REGS regs;

    // Set video mode 13
    regs.w.ax = 0x13;
    int386(0x10, (union REGS *)&regs, &regs);
}

void preheat_mode13(void)
{
    unsigned int loops;
    unsigned char *vram;

    for (loops = 0; loops < PREHEAT_LOOPS; loops++)
    {
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xAFA00; vram += 8)
        {
            *(vram) = 0x01;
            *(vram + 1) = 0x01;
            *(vram + 2) = 0x01;
            *(vram + 3) = 0x01;
            *(vram + 4) = 0x01;
            *(vram + 5) = 0x01;
            *(vram + 6) = 0x01;
            *(vram + 7) = 0x01;
        }
    }
}

void bench_mode13(void)
{
    unsigned char *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops_mode13;

    for (loops = 0; loops < num_loops; loops++)
    {
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xAFA00; vram += 8)
        {
            *(vram) = 0x01;
            *(vram + 1) = 0x01;
            *(vram + 2) = 0x01;
            *(vram + 3) = 0x01;
            *(vram + 4) = 0x01;
            *(vram + 5) = 0x01;
            *(vram + 6) = 0x01;
            *(vram + 7) = 0x01;
        }
    }
}

void execute_bench_mode13(void)
{
    // SET VIDEO MODE
    init_mode13();

    // PRE-HEAT
    timespent_mode13 = profile_function(preheat_mode13);
    total_loops_mode13 = PREHEAT_LOOPS * BENCH_TIME / timespent_mode13;

    // BENCHMARK
    timespent_mode13 = profile_function(bench_mode13);
}

void show_results_mode13(void)
{
    double total_result;

    total_result = ((double)total_loops_mode13 * 62.5 * 1000) / ((double)timespent_mode13);
    printf("VGA Mode 13: %.2lf kb/s\n", total_result);
}
