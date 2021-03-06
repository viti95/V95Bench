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

#include "modeY.h"
#include "timer.h"
#include "file.h"
#include "messages.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define SC_INDEX 0x3C4
#define SC_DATA 0x3C5
#define SC_MEMMODE 4

#define CRTC_INDEX 0x3D4
#define CRTC_DATA 0x3D5
#define CRTC_UNDERLINE 20
#define CRTC_MODE 23

#define GC_INDEX 0x3CE
#define GC_DATA 0x3CF
#define GC_READMAP 4
#define GC_MODE 5
#define GC_MISCELLANEOUS 6
#define GC_BITMASK 8

#define PREHEAT_LOOPS 25L
#define BENCH_TIME 5000L

unsigned long total_loops_modeY;
unsigned long timespent_w8_modeY;
unsigned long timespent_r8_modeY;
unsigned long timespent_w16_modeY;
unsigned long timespent_r16_modeY;

#ifdef __386__
unsigned long timespent_w32_modeY;
unsigned long timespent_r32_modeY;
#endif

void init_modeY(void)
{
    union REGS regs;

    // Set video mode 13
    regs.w.ax = 0x13;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif

    outp(SC_INDEX, SC_MEMMODE);
    outp(SC_DATA, (inp(SC_DATA) & ~8) | 4);
    outp(GC_INDEX, GC_MODE);
    outp(GC_DATA, inp(GC_DATA) & ~0x13);
    outp(GC_INDEX, GC_MISCELLANEOUS);
    outp(GC_DATA, inp(GC_DATA) & ~2);
    outpw(SC_INDEX, 0xf02);

    outp(CRTC_INDEX, CRTC_UNDERLINE);
    outp(CRTC_DATA, inp(CRTC_DATA) & ~0x40);
    outp(CRTC_INDEX, CRTC_MODE);
    outp(CRTC_DATA, inp(CRTC_DATA) | 0x40);
    outp(GC_INDEX, GC_READMAP);
}

void preheat_modeY(unsigned long total_loops)
{
    total_loops_modeY = total_loops;
    bench_w8_modeY();
}

void bench_w8_modeY(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeY;

    do
    {
        // PLANE 0
        outp(SC_DATA, 1 << (0 & 3));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x46;
            *(vram + 1) = 0x46;
            *(vram + 2) = 0x46;
            *(vram + 3) = 0x46;
            *(vram + 4) = 0x46;
            *(vram + 5) = 0x46;
            *(vram + 6) = 0x46;
            *(vram + 7) = 0x46;
        }

        // PLANE 1
        outp(SC_DATA, 1 << (1 & 3));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x03;
            *(vram + 1) = 0x03;
            *(vram + 2) = 0x03;
            *(vram + 3) = 0x03;
            *(vram + 4) = 0x03;
            *(vram + 5) = 0x03;
            *(vram + 6) = 0x03;
            *(vram + 7) = 0x03;
        }

        // PLANE 2
        outp(SC_DATA, 1 << (2 & 3));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xCC;
            *(vram + 1) = 0xCC;
            *(vram + 2) = 0xCC;
            *(vram + 3) = 0xCC;
            *(vram + 4) = 0xCC;
            *(vram + 5) = 0xCC;
            *(vram + 6) = 0xCC;
            *(vram + 7) = 0xCC;
        }

        // PLANE 3
        outp(SC_DATA, 1 << (3 & 3));

#ifdef __386__
        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x92;
            *(vram + 1) = 0x92;
            *(vram + 2) = 0x92;
            *(vram + 3) = 0x92;
            *(vram + 4) = 0x92;
            *(vram + 5) = 0x92;
            *(vram + 6) = 0x92;
            *(vram + 7) = 0x92;
        }
    } while (num_loops-- != 0);
}

void bench_w16_modeY(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeY;

    do
    {
        // PLANE 0
        outp(SC_DATA, 1 << (0 & 3));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x4651;
            *(vram + 1) = 0x4651;
            *(vram + 2) = 0x4651;
            *(vram + 3) = 0x4651;
            *(vram + 4) = 0x4651;
            *(vram + 5) = 0x4651;
            *(vram + 6) = 0x4651;
            *(vram + 7) = 0x4651;
        }

        // PLANE 1
        outp(SC_DATA, 1 << (1 & 3));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x1582;
            *(vram + 1) = 0x1582;
            *(vram + 2) = 0x1582;
            *(vram + 3) = 0x1582;
            *(vram + 4) = 0x1582;
            *(vram + 5) = 0x1582;
            *(vram + 6) = 0x1582;
            *(vram + 7) = 0x1582;
        }

        // PLANE 2
        outp(SC_DATA, 1 << (2 & 3));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0xCCAA;
            *(vram + 1) = 0xCCAA;
            *(vram + 2) = 0xCCAA;
            *(vram + 3) = 0xCCAA;
            *(vram + 4) = 0xCCAA;
            *(vram + 5) = 0xCCAA;
            *(vram + 6) = 0xCCAA;
            *(vram + 7) = 0xCCAA;
        }

        // PLANE 3
        outp(SC_DATA, 1 << (3 & 3));

#ifdef __386__
        for (vram = (unsigned short *)0xA0000; vram < (unsigned short *)0xA3E80; vram += 8)
#else
        for (vram = MK_FP(0xA000, 0); vram < MK_FP(0xA000, 0x3E80); vram += 8)
#endif
        {
            *(vram) = 0x11A0;
            *(vram + 1) = 0x11A0;
            *(vram + 2) = 0x11A0;
            *(vram + 3) = 0x11A0;
            *(vram + 4) = 0x11A0;
            *(vram + 5) = 0x11A0;
            *(vram + 6) = 0x11A0;
            *(vram + 7) = 0x11A0;
        }
    } while (num_loops-- != 0);
}

#ifdef __386__
void bench_w32_modeY(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeY;

    do
    {
        // PLANE 0
        outp(SC_DATA, 1 << (0 & 3));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 8)
        {
            *(vram) = 0x36E1ABCD;
            *(vram + 1) = 0x36E1ABCD;
            *(vram + 2) = 0x36E1ABCD;
            *(vram + 3) = 0x36E1ABCD;
            *(vram + 4) = 0x36E1ABCD;
            *(vram + 5) = 0x36E1ABCD;
            *(vram + 6) = 0x36E1ABCD;
            *(vram + 7) = 0x36E1ABCD;
        }

        // PLANE 1
        outp(SC_DATA, 1 << (1 & 3));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 8)
        {
            *(vram) = 0xCE52DA04;
            *(vram + 1) = 0xCE52DA04;
            *(vram + 2) = 0xCE52DA04;
            *(vram + 3) = 0xCE52DA04;
            *(vram + 4) = 0xCE52DA04;
            *(vram + 5) = 0xCE52DA04;
            *(vram + 6) = 0xCE52DA04;
            *(vram + 7) = 0xCE52DA04;
        }

        // PLANE 2
        outp(SC_DATA, 1 << (2 & 3));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 8)
        {
            *(vram) = 0x26E71439;
            *(vram + 1) = 0x26E71439;
            *(vram + 2) = 0x26E71439;
            *(vram + 3) = 0x26E71439;
            *(vram + 4) = 0x26E71439;
            *(vram + 5) = 0x26E71439;
            *(vram + 6) = 0x26E71439;
            *(vram + 7) = 0x26E71439;
        }

        // PLANE 3
        outp(SC_DATA, 1 << (3 & 3));

        for (vram = (unsigned int *)0xA0000; vram < (unsigned int *)0xA3E80; vram += 8)
        {
            *(vram) = 0x021EBFD3;
            *(vram + 1) = 0x021EBFD3;
            *(vram + 2) = 0x021EBFD3;
            *(vram + 3) = 0x021EBFD3;
            *(vram + 4) = 0x021EBFD3;
            *(vram + 5) = 0x021EBFD3;
            *(vram + 6) = 0x021EBFD3;
            *(vram + 7) = 0x021EBFD3;
        }
    } while (num_loops-- != 0);
}
#endif

void bench_r8_modeY(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeY;

    unsigned char read1, read2, read3, read4;

    do
    {
        // PLANE 0
        outp(SC_DATA, 1 << (0 & 3));

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

        // PLANE 1
        outp(SC_DATA, 1 << (1 & 3));

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

        // PLANE 2
        outp(SC_DATA, 1 << (2 & 3));

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

        // PLANE 3
        outp(SC_DATA, 1 << (3 & 3));

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

void bench_r16_modeY(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeY;

    unsigned short read1, read2, read3, read4;

    do
    {
        // PLANE 0
        outp(SC_DATA, 1 << (0 & 3));

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

        // PLANE 1
        outp(SC_DATA, 1 << (1 & 3));

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

        // PLANE 2
        outp(SC_DATA, 1 << (2 & 3));

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

        // PLANE 3
        outp(SC_DATA, 1 << (3 & 3));

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
void bench_r32_modeY(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeY;

    unsigned int read1, read2, read3, read4;

    do
    {
        // PLANE 0
        outp(SC_DATA, 1 << (0 & 3));

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

        // PLANE 1
        outp(SC_DATA, 1 << (1 & 3));

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

        // PLANE 2
        outp(SC_DATA, 1 << (2 & 3));

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

        // PLANE 3
        outp(SC_DATA, 1 << (3 & 3));

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

void execute_bench_modeY(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_modeY();

    // PRE-HEAT
    do
    {
        timespent_w8_modeY = profile_function_loops(preheat_modeY, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_modeY == 0);
    preheat_loops /= 2;
    total_loops_modeY = preheat_loops * BENCH_TIME / timespent_w8_modeY;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_modeY > 65535)
        total_loops_modeY = 65535;
#endif

    // BENCHMARK
    timespent_w8_modeY = profile_function(bench_w8_modeY);
    timespent_r8_modeY = profile_function(bench_r8_modeY);
    timespent_w16_modeY = profile_function(bench_w16_modeY);
    timespent_r16_modeY = profile_function(bench_r16_modeY);

#ifdef __386__
    timespent_w32_modeY = profile_function(bench_w32_modeY);
    timespent_r32_modeY = profile_function(bench_r32_modeY);
#endif
}

void get_results_modeY(unsigned char to_file)
{
    double total_result_w;
    double total_result_r;

    total_result_w = calc_kb_second(total_loops_modeY, 62.5, timespent_w8_modeY);
    total_result_r = calc_kb_second(total_loops_modeY, 62.5, timespent_r8_modeY);

    if (to_file)
        fprintf(logFile, MSG_MODEY_8BIT, total_result_w, total_result_r);
    else
        printf(MSG_MODEY_8BIT, total_result_w, total_result_r);

    total_result_w = calc_kb_second(total_loops_modeY, 62.5, timespent_w16_modeY);
    total_result_r = calc_kb_second(total_loops_modeY, 62.5, timespent_r16_modeY);

    if (to_file)
        fprintf(logFile, MSG_GENERIC_16BIT + 2, total_result_w, total_result_r);
    else
        printf(MSG_GENERIC_16BIT + 2, total_result_w, total_result_r);

#ifdef __386__
    total_result_w = calc_kb_second(total_loops_modeY, 62.5, timespent_w32_modeY);
    total_result_r = calc_kb_second(total_loops_modeY, 62.5, timespent_r32_modeY);

    if (to_file)
        fprintf(logFile, MSG_GENERIC_32BIT + 2, total_result_w, total_result_r);
    else
        printf(MSG_GENERIC_32BIT + 2, total_result_w, total_result_r);
#endif
}
