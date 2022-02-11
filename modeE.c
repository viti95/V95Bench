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

#include "modeE.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 25L
#define BENCH_TIME 5000L

unsigned long total_loops_modeE;
unsigned long timespent_modeE;

void init_modeE(void)
{
    union REGS regs;

    // Set video mode E
    regs.w.ax = 0x0E;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif

    outp(0x3C4, 0x2);
}

void preheat_modeE(void)
{
    unsigned int loops;

#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    for (loops = 0; loops < PREHEAT_LOOPS; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }
    }
}

void bench_modeE(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int loops;
    unsigned int num_loops = total_loops_modeE;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }
    }
}

void execute_bench_modeE(void)
{
    // SET VIDEO MODE
    init_modeE();

    // PRE-HEAT
    timespent_modeE = profile_function(preheat_modeE);
    total_loops_modeE = PREHEAT_LOOPS * BENCH_TIME / timespent_modeE;

    // BENCHMARK
    timespent_modeE = profile_function(bench_modeE);
}

void show_results_modeE(void)
{
    double total_result;

    total_result = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_modeE);
    printf("EGA 640x200 16c: %.2lf kb/s\n", total_result);
}
