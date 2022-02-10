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

#include "modeHGC.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 50
#define BENCH_TIME 5000

unsigned int total_loops_modeHGC;
unsigned long timespent_modeHGC;

void init_modeHGC(void)
{
    union REGS regs;

    // byte Graph_720x348[12] = {0x03, 0x36, 0x2D, 0x2E, 0x07, 0x5B, 0x02, 0x57, 0x57, 0x02, 0x03, 0x0A};
    unsigned char Graph_640x400[12] = {0x03, 0x34, 0x28, 0x2A, 0x47, 0x69, 0x00, 0x64, 0x65, 0x02, 0x03, 0x0A};
    // byte Graph_640x200[12] = {0x03, 0x6E, 0x28, 0x2E, 0x07, 0x67, 0x0A, 0x64, 0x65, 0x02, 0x01, 0x0A}; --> NOT WORKING ON REAL HARDWARE

    int i;

    outp(0x03BF, Graph_640x400[0]);
    for (i = 0; i < 10; i++)
    {
        outp(0x03B4, i);
        outp(0x03B5, Graph_640x400[i + 1]);
    }
    outp(0x03B8, Graph_640x400[11]);
}

void preheat_modeHGC(void)
{
    unsigned int loops;
    unsigned char *vram;

    for (loops = 0; loops < PREHEAT_LOOPS; loops++)
    {
        for (vram = (unsigned char *)0xB0000; vram < (unsigned char *)0xB1F40; vram += 2)
        {
            *(vram) = 0x55;
            *(vram + 1) = 0x55;
            *(vram + 0x2000) = 0x55;
            *(vram + 0x2001) = 0x55;
            *(vram + 0x4000) = 0x55;
            *(vram + 0x4001) = 0x55;
            *(vram + 0x6000) = 0x55;
            *(vram + 0x6001) = 0x55;
        }
    }
}

void bench_modeHGC(void)
{
    unsigned char *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops_modeHGC;

    for (loops = 0; loops < num_loops; loops++)
    {
        for (vram = (unsigned char *)0xB0000; vram < (unsigned char *)0xB1F40; vram += 2)
        {
            *(vram) = 0x55;
            *(vram + 1) = 0x55;
            *(vram + 0x2000) = 0x55;
            *(vram + 0x2001) = 0x55;
            *(vram + 0x4000) = 0x55;
            *(vram + 0x4001) = 0x55;
            *(vram + 0x6000) = 0x55;
            *(vram + 0x6001) = 0x55;
        }
    }
}

void execute_bench_modeHGC(void)
{
    // SET VIDEO MODE
    init_modeHGC();

    // PRE-HEAT
    timespent_modeHGC = profile_function(preheat_modeHGC);
    total_loops_modeHGC = PREHEAT_LOOPS * BENCH_TIME / timespent_modeHGC;

    // BENCHMARK
    timespent_modeHGC = profile_function(bench_modeHGC);
}

void show_results_modeHGC(void)
{
    double total_result;

    total_result = ((double)total_loops_modeHGC * 31.25 * 1000) / ((double)timespent_modeHGC);
    printf("Hercules 640x400 2c: %.2lf kb/s\n", total_result);
}
