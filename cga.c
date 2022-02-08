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

#include "cga.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

unsigned int total_loops;
unsigned long timespent;

void init_CGA_mode4(void)
{
    union REGS regs;

    // Set video mode 4
    regs.w.ax = 0x04;
    int386(0x10, (union REGS *)&regs, &regs);
}

void preheat_CGA_mode4(void)
{
    unsigned int loops;
    unsigned char *vram;
    unsigned int i;

    for (loops = 0; loops < 100; loops++)
    {
        for (vram = (unsigned char *)0xB8000, i = 0; i < 320 * 200 / (8 * 4); i++, vram += 4)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 0x2000) = 0xFF;
            *(vram + 0x2001) = 0xFF;
            *(vram + 0x2002) = 0xFF;
            *(vram + 0x2003) = 0xFF;
        }
    }
}

void bench_CGA_mode4(void)
{
    unsigned char *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops;
    unsigned int i;

    for (loops = 0; loops < num_loops; loops++)
    {

        for (vram = (unsigned char *)0xB8000, i = 0; i < 320 * 200 / (8 * 4); i++, vram += 4)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 0x2000) = 0xFF;
            *(vram + 0x2001) = 0xFF;
            *(vram + 0x2002) = 0xFF;
            *(vram + 0x2003) = 0xFF;
        }
    }
}

void execute_bench_CGA_mode4(void)
{
    // SET VIDEO MODE
    init_CGA_mode4();

    // PRE-HEAT
    timespent = profile_function(preheat_CGA_mode4);
    total_loops = 100 * 10000 / timespent; // 10 secs

    // BENCHMARK
    timespent = profile_function(bench_CGA_mode4);
}

void show_results_CGA_mode4(void)
{
    double total_result;

    total_result = ((double)total_loops * 15.625 * 1000) / ((double)timespent);
    printf("CGA Mode 4: %.2lf kb/s", total_result);
}
