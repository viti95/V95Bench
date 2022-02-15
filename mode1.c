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

#include "mode1.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PREHEAT_LOOPS 800L
#define BENCH_TIME 5000L

unsigned long total_loops_mode1;
unsigned long timespent_mode1;

void init_mode1(void)
{
    union REGS regs;

    // Set video mode 1
    regs.w.ax = 0x01;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif
}

void preheat_mode1(unsigned long total_loops)
{
    unsigned int loops;

#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    for (loops = 0; loops < total_loops; loops++)
    {
#ifdef __386__
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB87D0; vram += 8)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x07D0); vram += 8)
#endif
        {
            *(vram) = 0xA5;
            *(vram + 1) = 0xA5;
            *(vram + 2) = 0xA5;
            *(vram + 3) = 0xA5;
            *(vram + 4) = 0xA5;
            *(vram + 5) = 0xA5;
            *(vram + 6) = 0xA5;
            *(vram + 7) = 0xA5;
        }
    }
}

void bench_mode1(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int loops;
    unsigned int num_loops = total_loops_mode1;

    for (loops = 0; loops < num_loops; loops++)
    {
#ifdef __386__
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB87D0; vram += 8)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x07D0); vram += 8)
#endif
        {
            *(vram) = 0xA5;
            *(vram + 1) = 0xA5;
            *(vram + 2) = 0xA5;
            *(vram + 3) = 0xA5;
            *(vram + 4) = 0xA5;
            *(vram + 5) = 0xA5;
            *(vram + 6) = 0xA5;
            *(vram + 7) = 0xA5;
        }
    }
}

void execute_bench_mode1(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_mode1();

    // PRE-HEAT
    do
    {
        timespent_mode1 = profile_function_loops(preheat_mode1, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_mode1 == 0);
    preheat_loops /= 2;
    total_loops_mode1 = preheat_loops * BENCH_TIME / timespent_mode1;

    // BENCHMARK
    timespent_mode1 = profile_function(bench_mode1);
}

void show_results_mode1(void)
{
    double total_result;

    total_result = ((double)total_loops_mode1 * 1.953125 * 1000.0) / ((double)timespent_mode1);
    printf("TXT 40x25 16c: %.2lf kb/s\n", total_result);
}
