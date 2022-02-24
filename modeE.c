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
#include "file.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 25L
#define BENCH_TIME 5000L

unsigned long total_loops_modeE;
unsigned long timespent_w8_modeE;
unsigned long timespent_r8_modeE;
unsigned long timespent_w16_modeE;
unsigned long timespent_r16_modeE;

#ifdef __386__
unsigned long timespent_w32_modeE;
unsigned long timespent_r32_modeE;
#endif

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

void preheat_modeE(unsigned long total_loops)
{
    total_loops_modeE = total_loops;
    bench_w8_modeE();
}

void bench_w8_modeE(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeE;

    do
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x53;
            *(vram + 1) = 0x53;
            *(vram + 2) = 0x53;
            *(vram + 3) = 0x53;
            *(vram + 4) = 0x53;
            *(vram + 5) = 0x53;
            *(vram + 6) = 0x53;
            *(vram + 7) = 0x53;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
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

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xB5;
            *(vram + 1) = 0xB5;
            *(vram + 2) = 0xB5;
            *(vram + 3) = 0xB5;
            *(vram + 4) = 0xB5;
            *(vram + 5) = 0xB5;
            *(vram + 6) = 0xB5;
            *(vram + 7) = 0xB5;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x1C;
            *(vram + 1) = 0x1C;
            *(vram + 2) = 0x1C;
            *(vram + 3) = 0x1C;
            *(vram + 4) = 0x1C;
            *(vram + 5) = 0x1C;
            *(vram + 6) = 0x1C;
            *(vram + 7) = 0x1C;
        }
    } while (num_loops-- != 0);
}

void bench_w16_modeE(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeE;

    do
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xA431;
            *(vram + 1) = 0xA431;
            *(vram + 2) = 0xA431;
            *(vram + 3) = 0xA431;
            *(vram + 4) = 0xA431;
            *(vram + 5) = 0xA431;
            *(vram + 6) = 0xA431;
            *(vram + 7) = 0xA431;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x225F;
            *(vram + 1) = 0x225F;
            *(vram + 2) = 0x225F;
            *(vram + 3) = 0x225F;
            *(vram + 4) = 0x225F;
            *(vram + 5) = 0x225F;
            *(vram + 6) = 0x225F;
            *(vram + 7) = 0x225F;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x3AA4;
            *(vram + 1) = 0x3AA4;
            *(vram + 2) = 0x3AA4;
            *(vram + 3) = 0x3AA4;
            *(vram + 4) = 0x3AA4;
            *(vram + 5) = 0x3AA4;
            *(vram + 6) = 0x3AA4;
            *(vram + 7) = 0x3AA4;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x192F;
            *(vram + 1) = 0x192F;
            *(vram + 2) = 0x192F;
            *(vram + 3) = 0x192F;
            *(vram + 4) = 0x192F;
            *(vram + 5) = 0x192F;
            *(vram + 6) = 0x192F;
            *(vram + 7) = 0x192F;
        }
    } while (num_loops-- != 0);
}

#ifdef __386__
void bench_w32_modeE(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeE;

    do
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 8)
        {
            *(vram) = 0xBEAC02FC;
            *(vram + 1) = 0xBEAC02FC;
            *(vram + 2) = 0xBEAC02FC;
            *(vram + 3) = 0xBEAC02FC;
            *(vram + 4) = 0xBEAC02FC;
            *(vram + 5) = 0xBEAC02FC;
            *(vram + 6) = 0xBEAC02FC;
            *(vram + 7) = 0xBEAC02FC;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 8)
        {
            *(vram) = 0xAC351942;
            *(vram + 1) = 0xAC351942;
            *(vram + 2) = 0xAC351942;
            *(vram + 3) = 0xAC351942;
            *(vram + 4) = 0xAC351942;
            *(vram + 5) = 0xAC351942;
            *(vram + 6) = 0xAC351942;
            *(vram + 7) = 0xAC351942;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 8)
        {
            *(vram) = 0xE369BC15;
            *(vram + 1) = 0xE369BC15;
            *(vram + 2) = 0xE369BC15;
            *(vram + 3) = 0xE369BC15;
            *(vram + 4) = 0xE369BC15;
            *(vram + 5) = 0xE369BC15;
            *(vram + 6) = 0xE369BC15;
            *(vram + 7) = 0xE369BC15;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 8)
        {
            *(vram) = 0xBBA143DA;
            *(vram + 1) = 0xBBA143DA;
            *(vram + 2) = 0xBBA143DA;
            *(vram + 3) = 0xBBA143DA;
            *(vram + 4) = 0xBBA143DA;
            *(vram + 5) = 0xBBA143DA;
            *(vram + 6) = 0xBBA143DA;
            *(vram + 7) = 0xBBA143DA;
        }
    } while (num_loops-- != 0);
}
#endif

void bench_r8_modeE(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeE;

    unsigned char read1, read2, read3, read4;

    do
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_8b_1 = read1;
        read_fix_8b_2 = read2;
        read_fix_8b_3 = read3;
        read_fix_8b_4 = read4;

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_8b_1 = read1;
        read_fix_8b_2 = read2;
        read_fix_8b_3 = read3;
        read_fix_8b_4 = read4;

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_8b_1 = read1;
        read_fix_8b_2 = read2;
        read_fix_8b_3 = read3;
        read_fix_8b_4 = read4;

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_8b_1 = read1;
        read_fix_8b_2 = read2;
        read_fix_8b_3 = read3;
        read_fix_8b_4 = read4;
    } while (num_loops-- != 0);
}

void bench_r16_modeE(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeE;

    unsigned short read1, read2, read3, read4;

    do
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_16b_1 = read1;
        read_fix_16b_2 = read2;
        read_fix_16b_3 = read3;
        read_fix_16b_4 = read4;

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_16b_1 = read1;
        read_fix_16b_2 = read2;
        read_fix_16b_3 = read3;
        read_fix_16b_4 = read4;

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_16b_1 = read1;
        read_fix_16b_2 = read2;
        read_fix_16b_3 = read3;
        read_fix_16b_4 = read4;

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 4)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_16b_1 = read1;
        read_fix_16b_2 = read2;
        read_fix_16b_3 = read3;
        read_fix_16b_4 = read4;
    } while (num_loops-- != 0);
}

#ifdef __386__
void bench_r32_modeE(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeE;

    unsigned int read1, read2, read3, read4;

    do
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 4)
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_32b_1 = read1;
        read_fix_32b_2 = read2;
        read_fix_32b_3 = read3;
        read_fix_32b_4 = read4;

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 4)
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_32b_1 = read1;
        read_fix_32b_2 = read2;
        read_fix_32b_3 = read3;
        read_fix_32b_4 = read4;

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 4)
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_32b_1 = read1;
        read_fix_32b_2 = read2;
        read_fix_32b_3 = read3;
        read_fix_32b_4 = read4;

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 4)
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }

        read_fix_32b_1 = read1;
        read_fix_32b_2 = read2;
        read_fix_32b_3 = read3;
        read_fix_32b_4 = read4;
    } while (num_loops-- != 0);
}
#endif

void execute_bench_modeE(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_modeE();

    // PRE-HEAT
    do
    {
        timespent_w8_modeE = profile_function_loops(preheat_modeE, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_modeE == 0);
    preheat_loops /= 2;
    total_loops_modeE = preheat_loops * BENCH_TIME / timespent_w8_modeE;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_modeE > 65535)
        total_loops_modeE = 65535;
#endif

    // BENCHMARK
    timespent_w8_modeE = profile_function(bench_w8_modeE);
    timespent_r8_modeE = profile_function(bench_r8_modeE);
    timespent_w16_modeE = profile_function(bench_w16_modeE);
    timespent_r16_modeE = profile_function(bench_r16_modeE);

#ifdef __386__
    timespent_w32_modeE = profile_function(bench_w32_modeE);
    timespent_r32_modeE = profile_function(bench_r32_modeE);
#endif
}

void show_results_modeE(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_w8_modeE);
    total_result_r = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_r8_modeE);
    printf("EGA 640x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n", total_result_w, total_result_r);
    total_result_w = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_w16_modeE);
    total_result_r = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_r16_modeE);
    printf("                 W16 %.2lf kb/s, R16 %.2lf kb/s\n", total_result_w, total_result_r);

#ifdef __386__
    total_result_w = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_w32_modeE);
    total_result_r = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_r32_modeE);
    printf("                 W32 %.2lf kb/s, R32 %.2lf kb/s\n", total_result_w, total_result_r);
#endif
}

void export_results_modeE(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_w8_modeE);
    total_result_r = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_r8_modeE);
    fprintf(logFile, "EGA 640x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n", total_result_w, total_result_r);
    total_result_w = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_w16_modeE);
    total_result_r = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_r16_modeE);
    fprintf(logFile, "                 W16 %.2lf kb/s, R16 %.2lf kb/s\n", total_result_w, total_result_r);

#ifdef __386__
    total_result_w = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_w32_modeE);
    total_result_r = ((double)total_loops_modeE * 62.5 * 1000.0) / ((double)timespent_r32_modeE);
    fprintf(logFile, "                 W32 %.2lf kb/s, R32 %.2lf kb/s\n", total_result_w, total_result_r);
#endif
}
