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

#include "mode3.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PREHEAT_LOOPS 400L
#define BENCH_TIME 5000L

unsigned long total_loops_mode3;
unsigned long timespent_mode3;

void init_mode3(void)
{
    union REGS regs;

    // Set video mode 3
    regs.w.ax = 0x03;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif
}

void preheat_mode3(unsigned long total_loops)
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
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB8FA0; vram += 8)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x0FA0); vram += 8)
#endif
        {
            *(vram) = 0xA4;
            *(vram + 1) = 0xA4;
            *(vram + 2) = 0xA4;
            *(vram + 3) = 0xA4;
            *(vram + 4) = 0xA4;
            *(vram + 5) = 0xA4;
            *(vram + 6) = 0xA4;
            *(vram + 7) = 0xA4;
        }
    }
}

void bench_mode3(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int loops;
    unsigned int num_loops = total_loops_mode3;

    for (loops = 0; loops < num_loops; loops++)
    {
#ifdef __386__
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB8FA0; vram += 8)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x0FA0); vram += 8)
#endif
        {
            *(vram) = 0xA4;
            *(vram + 1) = 0xA4;
            *(vram + 2) = 0xA4;
            *(vram + 3) = 0xA4;
            *(vram + 4) = 0xA4;
            *(vram + 5) = 0xA4;
            *(vram + 6) = 0xA4;
            *(vram + 7) = 0xA4;
        }
    }
}

void execute_bench_mode3(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_mode3();

    // PRE-HEAT
    do
    {
        timespent_mode3 = profile_function_loops(preheat_mode3, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_mode3 == 0);
    preheat_loops /= 2;
    total_loops_mode3 = preheat_loops * BENCH_TIME / timespent_mode3;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_mode3 > 65535)
        total_loops_mode3 = 65535;
#endif

    // BENCHMARK
    timespent_mode3 = profile_function(bench_mode3);
}

void show_results_mode3(void)
{
    double total_result;

    total_result = ((double)total_loops_mode3 * 3.90625 * 1000.0) / ((double)timespent_mode3);
    printf("TXT 80x25 16c: %.2lf kb/s\n", total_result);
}
