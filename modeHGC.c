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

#define PREHEAT_LOOPS 50L
#define BENCH_TIME 5000L

unsigned long total_loops_modeHGC;
unsigned long timespent_w8_modeHGC;
unsigned long timespent_r8_modeHGC;
unsigned long timespent_w16_modeHGC;
unsigned long timespent_r16_modeHGC;

#ifdef __386__
unsigned long timespent_w32_modeHGC;
unsigned long timespent_r32_modeHGC;
#endif

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

void preheat_modeHGC(unsigned long total_loops)
{
    total_loops_modeHGC = total_loops;
    bench_w8_modeHGC();
}

void bench_w8_modeHGC(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeHGC;

    do
    {

#ifdef __386__
        for (vram = (unsigned char *)0xB0000; vram < (unsigned char *)0xB1F40; vram += 2)
#else
        for (vram = MK_FP(0xB000, 0); vram < MK_FP(0xB000, 0x1F40); vram += 2)
#endif
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
    } while (num_loops-- != 0);
}

void bench_w16_modeHGC(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeHGC;

    do
    {

#ifdef __386__
        for (vram = (unsigned short *)0xB0000; vram < (unsigned short *)0xB1F40; vram += 2)
#else
        for (vram = MK_FP(0xB000, 0); vram < MK_FP(0xB000, 0x1F40); vram += 2)
#endif
        {
            *(vram) = 0xA413;
            *(vram + 1) = 0xA413;
            *(vram + 0x1000) = 0xA413;
            *(vram + 0x1001) = 0xA413;
            *(vram + 0x2000) = 0xA413;
            *(vram + 0x2001) = 0xA413;
            *(vram + 0x3000) = 0xA413;
            *(vram + 0x3001) = 0xA413;
        }
    } while (num_loops-- != 0);
}

#ifdef __386__
void bench_w32_modeHGC(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeHGC;

    do
    {
        for (vram = (unsigned int *)0xB0000; vram < (unsigned int *)0xB1F40; vram += 2)
        {
            *(vram) = 0x36E1CF02;
            *(vram + 1) = 0x36E1CF02;
            *(vram + 0x800) = 0x36E1CF02;
            *(vram + 0x801) = 0x36E1CF02;
            *(vram + 0x1000) = 0x36E1CF02;
            *(vram + 0x1001) = 0x36E1CF02;
            *(vram + 0x1800) = 0x36E1CF02;
            *(vram + 0x1801) = 0x36E1CF02;
        }
    } while (num_loops-- != 0);
}
#endif

void bench_r8_modeHGC(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeHGC;

    unsigned char read1, read2, read3, read4;

    do
    {

#ifdef __386__
        for (vram = (unsigned char *)0xB0000; vram < (unsigned char *)0xB1F40; vram++)
#else
        for (vram = MK_FP(0xB000, 0); vram < MK_FP(0xB000, 0x1F40); vram++)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 0x2000);
            read3 = *(vram + 0x4000);
            read4 = *(vram + 0x6000);
        }
    } while (num_loops-- != 0);

    read_fix_8b_1 = read1;
    read_fix_8b_2 = read2;
    read_fix_8b_3 = read3;
    read_fix_8b_4 = read4;
}

void bench_r16_modeHGC(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeHGC;

    unsigned short read1, read2, read3, read4;

    do
    {

#ifdef __386__
        for (vram = (unsigned short *)0xB0000; vram < (unsigned short *)0xB1F40; vram++)
#else
        for (vram = MK_FP(0xB000, 0); vram < MK_FP(0xB000, 0x1F40); vram++)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 0x1000);
            read3 = *(vram + 0x2000);
            read4 = *(vram + 0x3000);
        }
    } while (num_loops-- != 0);

    read_fix_16b_1 = read1;
    read_fix_16b_2 = read2;
    read_fix_16b_3 = read3;
    read_fix_16b_4 = read4;
}

#ifdef __386__
void bench_r32_modeHGC(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeHGC;

    unsigned int read1, read2, read3, read4;

    do
    {
        for (vram = (unsigned int *)0xB0000; vram < (unsigned int *)0xB1F40; vram++)
        {
            read1 = *(vram);
            read2 = *(vram + 0x800);
            read3 = *(vram + 0x1000);
            read4 = *(vram + 0x1800);
        }
    } while (num_loops-- != 0);

    read_fix_32b_1 = read1;
    read_fix_32b_2 = read2;
    read_fix_32b_3 = read3;
    read_fix_32b_4 = read4;
}
#endif

void execute_bench_modeHGC(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_modeHGC();

    // PRE-HEAT
    do
    {
        timespent_w8_modeHGC = profile_function_loops(preheat_modeHGC, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_modeHGC == 0);
    preheat_loops /= 2;
    total_loops_modeHGC = preheat_loops * BENCH_TIME / timespent_w8_modeHGC;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_modeHGC > 65535)
        total_loops_modeHGC = 65535;
#endif

    // BENCHMARK
    timespent_w8_modeHGC = profile_function(bench_w8_modeHGC);
    timespent_r8_modeHGC = profile_function(bench_r8_modeHGC);
    timespent_w16_modeHGC = profile_function(bench_w16_modeHGC);
    timespent_r16_modeHGC = profile_function(bench_r16_modeHGC);

#ifdef __386__
    timespent_w32_modeHGC = profile_function(bench_w32_modeHGC);
    timespent_r32_modeHGC = profile_function(bench_r32_modeHGC);
#endif
}

void show_results_modeHGC(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = ((double)total_loops_modeHGC * 31.25 * 1000.0) / ((double)timespent_w8_modeHGC);
    total_result_r = ((double)total_loops_modeHGC * 31.25 * 1000.0) / ((double)timespent_r8_modeHGC);
    printf("HGC 640x400 2c: W8 %.2lf kb/s, R8 %.2lf kb/s\n", total_result_w, total_result_r);
    total_result_w = ((double)total_loops_modeHGC * 31.25 * 1000.0) / ((double)timespent_w16_modeHGC);
    total_result_r = ((double)total_loops_modeHGC * 31.25 * 1000.0) / ((double)timespent_r16_modeHGC);
    printf("                W16 %.2lf kb/s, R16 %.2lf kb/s\n", total_result_w, total_result_r);

#ifdef __386__
    total_result_w = ((double)total_loops_modeHGC * 31.25 * 1000.0) / ((double)timespent_w32_modeHGC);
    total_result_r = ((double)total_loops_modeHGC * 31.25 * 1000.0) / ((double)timespent_r32_modeHGC);
    printf("                W32 %.2lf kb/s, R32 %.2lf kb/s\n", total_result_w, total_result_r);
#endif
}
