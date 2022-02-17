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

#include "modeD.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 50L
#define BENCH_TIME 5000L

unsigned long total_loops_modeD;
unsigned long timespent_w8_modeD;
unsigned long timespent_r8_modeD;
unsigned long timespent_w16_modeD;

#ifdef __386__
unsigned long timespent_w32_modeD;
#endif

void init_modeD(void)
{
    union REGS regs;

    // Set video mode D
    regs.w.ax = 0x0D;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif

    outp(0x3C4, 0x2);
}

void preheat_modeD(unsigned long total_loops)
{
    total_loops_modeD = total_loops;
    bench_w8_modeD();
}

void bench_w8_modeD(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int loops;
    unsigned int num_loops = total_loops_modeD;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 8)
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

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 8)
#endif
        {
            *(vram) = 0x8C;
            *(vram + 1) = 0x8C;
            *(vram + 2) = 0x8C;
            *(vram + 3) = 0x8C;
            *(vram + 4) = 0x8C;
            *(vram + 5) = 0x8C;
            *(vram + 6) = 0x8C;
            *(vram + 7) = 0x8C;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 8)
#endif
        {
            *(vram) = 0xAA;
            *(vram + 1) = 0xAA;
            *(vram + 2) = 0xAA;
            *(vram + 3) = 0xAA;
            *(vram + 4) = 0xAA;
            *(vram + 5) = 0xAA;
            *(vram + 6) = 0xAA;
            *(vram + 7) = 0xAA;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 8)
#endif
        {
            *(vram) = 0x24;
            *(vram + 1) = 0x24;
            *(vram + 2) = 0x24;
            *(vram + 3) = 0x24;
            *(vram + 4) = 0x24;
            *(vram + 5) = 0x24;
            *(vram + 6) = 0x24;
            *(vram + 7) = 0x24;
        }
    }
}

void bench_w16_modeD(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int loops;
    unsigned int num_loops = total_loops_modeD;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA1F40; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 8)
#endif
        {
            *(vram) = 0x1452;
            *(vram + 1) = 0x1452;
            *(vram + 2) = 0x1452;
            *(vram + 3) = 0x1452;
            *(vram + 4) = 0x1452;
            *(vram + 5) = 0x1452;
            *(vram + 6) = 0x1452;
            *(vram + 7) = 0x1452;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA1F40; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 8)
#endif
        {
            *(vram) = 0x21EE;
            *(vram + 1) = 0x21EE;
            *(vram + 2) = 0x21EE;
            *(vram + 3) = 0x21EE;
            *(vram + 4) = 0x21EE;
            *(vram + 5) = 0x21EE;
            *(vram + 6) = 0x21EE;
            *(vram + 7) = 0x21EE;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA1F40; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 8)
#endif
        {
            *(vram) = 0xFF15;
            *(vram + 1) = 0xFF15;
            *(vram + 2) = 0xFF15;
            *(vram + 3) = 0xFF15;
            *(vram + 4) = 0xFF15;
            *(vram + 5) = 0xFF15;
            *(vram + 6) = 0xFF15;
            *(vram + 7) = 0xFF15;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA1F40; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 8)
#endif
        {
            *(vram) = 0xC13E;
            *(vram + 1) = 0xC13E;
            *(vram + 2) = 0xC13E;
            *(vram + 3) = 0xC13E;
            *(vram + 4) = 0xC13E;
            *(vram + 5) = 0xC13E;
            *(vram + 6) = 0xC13E;
            *(vram + 7) = 0xC13E;
        }
    }
}

#ifdef __386__
void bench_w32_modeD(void)
{
    unsigned int *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops_modeD;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA1F40; vram += 8)
        {
            *(vram) = 0xFE92B0CD;
            *(vram + 1) = 0xFE92B0CD;
            *(vram + 2) = 0xFE92B0CD;
            *(vram + 3) = 0xFE92B0CD;
            *(vram + 4) = 0xFE92B0CD;
            *(vram + 5) = 0xFE92B0CD;
            *(vram + 6) = 0xFE92B0CD;
            *(vram + 7) = 0xFE92B0CD;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA1F40; vram += 8)
        {
            *(vram) = 0x02451F24;
            *(vram + 1) = 0x02451F24;
            *(vram + 2) = 0x02451F24;
            *(vram + 3) = 0x02451F24;
            *(vram + 4) = 0x02451F24;
            *(vram + 5) = 0x02451F24;
            *(vram + 6) = 0x02451F24;
            *(vram + 7) = 0x02451F24;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA1F40; vram += 8)
        {
            *(vram) = 0xA4E329CA;
            *(vram + 1) = 0xA4E329CA;
            *(vram + 2) = 0xA4E329CA;
            *(vram + 3) = 0xA4E329CA;
            *(vram + 4) = 0xA4E329CA;
            *(vram + 5) = 0xA4E329CA;
            *(vram + 6) = 0xA4E329CA;
            *(vram + 7) = 0xA4E329CA;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA1F40; vram += 8)
        {
            *(vram) = 0x2FCA6745;
            *(vram + 1) = 0x2FCA6745;
            *(vram + 2) = 0x2FCA6745;
            *(vram + 3) = 0x2FCA6745;
            *(vram + 4) = 0x2FCA6745;
            *(vram + 5) = 0x2FCA6745;
            *(vram + 6) = 0x2FCA6745;
            *(vram + 7) = 0x2FCA6745;
        }
    }
}
#endif

void bench_r8_modeD(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int loops;
    unsigned int num_loops = total_loops_modeD;

    unsigned char read1, read2, read3, read4;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 4)
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
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 4)
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
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 4)
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
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x1F40); vram += 4)
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

void execute_bench_modeD(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_modeD();

    // PRE-HEAT
    do
    {
        timespent_w8_modeD = profile_function_loops(preheat_modeD, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_modeD == 0);
    preheat_loops /= 2;
    total_loops_modeD = preheat_loops * BENCH_TIME / timespent_w8_modeD;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_modeD > 65535)
        total_loops_modeD = 65535;
#endif

    // BENCHMARK
    timespent_w8_modeD = profile_function(bench_w8_modeD);
    timespent_r8_modeD = profile_function(bench_r8_modeD);
    timespent_w16_modeD = profile_function(bench_w16_modeD);

#ifdef __386__
    timespent_w32_modeD = profile_function(bench_w32_modeD);
#endif
}

void show_results_modeD(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = ((double)total_loops_modeD * 31.25 * 1000.0) / ((double)timespent_w8_modeD);
    total_result_r = ((double)total_loops_modeD * 31.25 * 1000.0) / ((double)timespent_r8_modeD);
    printf("EGA 320x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n", total_result_w, total_result_r);
    total_result_w = ((double)total_loops_modeD * 31.25 * 1000.0) / ((double)timespent_w16_modeD);
    printf("                 W16 %.2lf kb/s\n", total_result_w);

#ifdef __386__
    total_result_w = ((double)total_loops_modeD * 31.25 * 1000.0) / ((double)timespent_w32_modeD);
    printf("                 W32 %.2lf kb/s\n", total_result_w);
#endif
}
