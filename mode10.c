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

#include "mode10.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 25L
#define BENCH_TIME 5000L

unsigned long total_loops_mode10;
unsigned long timespent_w8_mode10;
unsigned long timespent_r8_mode10;
unsigned long timespent_w16_mode10;

#ifdef __386__
unsigned long timespent_w32_mode10;
#endif

void init_mode10(void)
{
    union REGS regs;

    // Set video mode 10
    regs.w.ax = 0x10;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif

    outp(0x3C4, 0x2);
}

void preheat_mode10(unsigned long total_loops)
{
    total_loops_mode10 = total_loops;
    bench_w8_mode10();
}

void bench_w8_mode10(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int loops;
    unsigned int num_loops = total_loops_mode10;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA6D60; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 8)
#endif
        {
            *(vram) = 0x12;
            *(vram + 1) = 0x12;
            *(vram + 2) = 0x12;
            *(vram + 3) = 0x12;
            *(vram + 4) = 0x12;
            *(vram + 5) = 0x12;
            *(vram + 6) = 0x12;
            *(vram + 7) = 0x12;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA6D60; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 8)
#endif
        {
            *(vram) = 0xEA;
            *(vram + 1) = 0xEA;
            *(vram + 2) = 0xEA;
            *(vram + 3) = 0xEA;
            *(vram + 4) = 0xEA;
            *(vram + 5) = 0xEA;
            *(vram + 6) = 0xEA;
            *(vram + 7) = 0xEA;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA6D60; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 8)
#endif
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

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA6D60; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 8)
#endif
        {
            *(vram) = 0x9A;
            *(vram + 1) = 0x9A;
            *(vram + 2) = 0x9A;
            *(vram + 3) = 0x9A;
            *(vram + 4) = 0x9A;
            *(vram + 5) = 0x9A;
            *(vram + 6) = 0x9A;
            *(vram + 7) = 0x9A;
        }
    }
}

void bench_w16_mode10(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int loops;
    unsigned int num_loops = total_loops_mode10;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA6D60; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 8)
#endif
        {
            *(vram) = 0xA4B2;
            *(vram + 1) = 0xA4B2;
            *(vram + 2) = 0xA4B2;
            *(vram + 3) = 0xA4B2;
            *(vram + 4) = 0xA4B2;
            *(vram + 5) = 0xA4B2;
            *(vram + 6) = 0xA4B2;
            *(vram + 7) = 0xA4B2;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA6D60; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 8)
#endif
        {
            *(vram) = 0xEF1C;
            *(vram + 1) = 0xEF1C;
            *(vram + 2) = 0xEF1C;
            *(vram + 3) = 0xEF1C;
            *(vram + 4) = 0xEF1C;
            *(vram + 5) = 0xEF1C;
            *(vram + 6) = 0xEF1C;
            *(vram + 7) = 0xEF1C;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA6D60; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 8)
#endif
        {
            *(vram) = 0xF1D0;
            *(vram + 1) = 0xF1D0;
            *(vram + 2) = 0xF1D0;
            *(vram + 3) = 0xF1D0;
            *(vram + 4) = 0xF1D0;
            *(vram + 5) = 0xF1D0;
            *(vram + 6) = 0xF1D0;
            *(vram + 7) = 0xF1D0;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA6D60; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 8)
#endif
        {
            *(vram) = 0x4156;
            *(vram + 1) = 0x4156;
            *(vram + 2) = 0x4156;
            *(vram + 3) = 0x4156;
            *(vram + 4) = 0x4156;
            *(vram + 5) = 0x4156;
            *(vram + 6) = 0x4156;
            *(vram + 7) = 0x4156;
        }
    }
}

#ifdef __386__
void bench_w32_mode10(void)
{
    unsigned int *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops_mode10;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA6D60; vram += 8)
        {
            *(vram) = 0xE97ECB02;
            *(vram + 1) = 0xE97ECB02;
            *(vram + 2) = 0xE97ECB02;
            *(vram + 3) = 0xE97ECB02;
            *(vram + 4) = 0xE97ECB02;
            *(vram + 5) = 0xE97ECB02;
            *(vram + 6) = 0xE97ECB02;
            *(vram + 7) = 0xE97ECB02;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA6D60; vram += 8)
        {
            *(vram) = 0xF314CB02;
            *(vram + 1) = 0xF314CB02;
            *(vram + 2) = 0xF314CB02;
            *(vram + 3) = 0xF314CB02;
            *(vram + 4) = 0xF314CB02;
            *(vram + 5) = 0xF314CB02;
            *(vram + 6) = 0xF314CB02;
            *(vram + 7) = 0xF314CB02;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA6D60; vram += 8)
        {
            *(vram) = 0x3214CB02;
            *(vram + 1) = 0x3214CB02;
            *(vram + 2) = 0x3214CB02;
            *(vram + 3) = 0x3214CB02;
            *(vram + 4) = 0x3214CB02;
            *(vram + 5) = 0x3214CB02;
            *(vram + 6) = 0x3214CB02;
            *(vram + 7) = 0x3214CB02;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA6D60; vram += 8)
        {
            *(vram) = 0xFA98CB02;
            *(vram + 1) = 0xFA98CB02;
            *(vram + 2) = 0xFA98CB02;
            *(vram + 3) = 0xFA98CB02;
            *(vram + 4) = 0xFA98CB02;
            *(vram + 5) = 0xFA98CB02;
            *(vram + 6) = 0xFA98CB02;
            *(vram + 7) = 0xFA98CB02;
        }
    }
}
#endif

void bench_r8_mode10(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int loops;
    unsigned int num_loops = total_loops_mode10;

    unsigned char read1, read2, read3, read4;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA6D60; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_1 = read1;
        read_fix_2 = read2;
        read_fix_3 = read3;
        read_fix_4 = read4;

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA6D60; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_1 = read1;
        read_fix_2 = read2;
        read_fix_3 = read3;
        read_fix_4 = read4;

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA6D60; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_1 = read1;
        read_fix_2 = read2;
        read_fix_3 = read3;
        read_fix_4 = read4;

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA6D60; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x6D60); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_1 = read1;
        read_fix_2 = read2;
        read_fix_3 = read3;
        read_fix_4 = read4;
    }
}

void execute_bench_mode10(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_mode10();

    // PRE-HEAT
    do
    {
        timespent_w8_mode10 = profile_function_loops(preheat_mode10, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_mode10 == 0);
    preheat_loops /= 2;
    total_loops_mode10 = preheat_loops * BENCH_TIME / timespent_w8_mode10;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_mode10 > 65535)
        total_loops_mode10 = 65535;
#endif

    // BENCHMARK
    timespent_w8_mode10 = profile_function(bench_w8_mode10);
    timespent_r8_mode10 = profile_function(bench_r8_mode10);
    timespent_w16_mode10 = profile_function(bench_w16_mode10);

#ifdef __386__
    timespent_w32_mode10 = profile_function(bench_w32_mode10);
#endif
}

void show_results_mode10(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = ((double)total_loops_mode10 * 109.375 * 1000.0) / ((double)timespent_w8_mode10);
    total_result_r = ((double)total_loops_mode10 * 109.375 * 1000.0) / ((double)timespent_r8_mode10);
    printf("EGA 640x350 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n", total_result_w, total_result_r);
    total_result_w = ((double)total_loops_mode10 * 109.375 * 1000.0) / ((double)timespent_w16_mode10);
    printf("                 W16 %.2lf kb/s\n", total_result_w);

#ifdef __386__
    total_result_w = ((double)total_loops_mode10 * 109.375 * 1000.0) / ((double)timespent_w32_mode10);
    printf("                 W32 %.2lf kb/s\n", total_result_w);
#endif
}
