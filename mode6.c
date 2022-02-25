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

#include "mode6.h"
#include "timer.h"
#include "file.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PREHEAT_LOOPS 100L
#define BENCH_TIME 5000L

unsigned long total_loops_mode6;
unsigned long timespent_w8_mode6;
unsigned long timespent_r8_mode6;
unsigned long timespent_w16_mode6;
unsigned long timespent_r16_mode6;

#ifdef __386__
unsigned long timespent_w32_mode6;
unsigned long timespent_r32_mode6;
#endif

static const char MSG_8BIT[]  = "CGA 640x200 2c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
static const char MSG_16BIT[] = "                W16 %.2lf kb/s, R16 %.2lf kb/s\n";
static const char MSG_32BIT[] = "                W32 %.2lf kb/s, R32 %.2lf kb/s\n";

void init_mode6(void)
{
    union REGS regs;

    // Set video mode 6
    regs.w.ax = 0x06;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif
}

void preheat_mode6(unsigned long total_loops)
{
    total_loops_mode6 = total_loops;
    bench_w8_mode6();
}

void bench_w8_mode6(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_mode6;

    do
    {

#ifdef __386__
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB9F40; vram += 4)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x1F40); vram += 4)
#endif
        {
            *(vram) = 0x6B;
            *(vram + 1) = 0x6B;
            *(vram + 2) = 0x6B;
            *(vram + 3) = 0x6B;
            *(vram + 0x2000) = 0x6B;
            *(vram + 0x2001) = 0x6B;
            *(vram + 0x2002) = 0x6B;
            *(vram + 0x2003) = 0x6B;
        }
    } while (num_loops-- != 0);
}

void bench_w16_mode6(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_mode6;

    do
    {

#ifdef __386__
        for (vram = (unsigned short *)0xB8000; vram < (unsigned short *)0xB9F40; vram += 4)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x1F40); vram += 4)
#endif
        {
            *(vram) = 0xB53A;
            *(vram + 1) = 0xB53A;
            *(vram + 2) = 0xB53A;
            *(vram + 3) = 0xB53A;
            *(vram + 0x1000) = 0xB53A;
            *(vram + 0x1001) = 0xB53A;
            *(vram + 0x1002) = 0xB53A;
            *(vram + 0x1003) = 0xB53A;
        }
    } while (num_loops-- != 0);
}

#ifdef __386__
void bench_w32_mode6(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_mode6;

    do
    {
        for (vram = (unsigned int *)0xB8000; vram < (unsigned int *)0xB9F40; vram += 4)
        {
            *(vram) = 0xBA860131;
            *(vram + 1) = 0xBA860131;
            *(vram + 2) = 0xBA860131;
            *(vram + 3) = 0xBA860131;
            *(vram + 0x800) = 0xBA860131;
            *(vram + 0x801) = 0xBA860131;
            *(vram + 0x802) = 0xBA860131;
            *(vram + 0x803) = 0xBA860131;
        }
    } while (num_loops-- != 0);
}
#endif

void bench_r8_mode6(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_mode6;

    unsigned char read1, read2, read3, read4;

    do
    {

#ifdef __386__
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB9F40; vram += 2)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x1F40); vram += 2)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 0x2000);
            read4 = *(vram + 0x2001);
        }
    } while (num_loops-- != 0);

    read_fix_8b_1 = read1;
    read_fix_8b_2 = read2;
    read_fix_8b_3 = read3;
    read_fix_8b_4 = read4;
}

void bench_r16_mode6(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_mode6;

    unsigned short read1, read2, read3, read4;

    do
    {

#ifdef __386__
        for (vram = (unsigned short *)0xB8000; vram < (unsigned short *)0xB9F40; vram += 2)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x1F40); vram += 2)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 0x1000);
            read4 = *(vram + 0x1001);
        }
    } while (num_loops-- != 0);

    read_fix_16b_1 = read1;
    read_fix_16b_2 = read2;
    read_fix_16b_3 = read3;
    read_fix_16b_4 = read4;
}

#ifdef __386__
void bench_r32_mode6(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_mode6;

    unsigned int read1, read2, read3, read4;

    do
    {
        for (vram = (unsigned int *)0xB8000; vram < (unsigned int *)0xB9F40; vram += 2)
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 0x800);
            read4 = *(vram + 0x801);
        }
    } while (num_loops-- != 0);

    read_fix_32b_1 = read1;
    read_fix_32b_2 = read2;
    read_fix_32b_3 = read3;
    read_fix_32b_4 = read4;
}
#endif

void execute_bench_mode6(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_mode6();

    // PRE-HEAT
    do
    {
        timespent_w8_mode6 = profile_function_loops(preheat_mode6, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_mode6 == 0);
    preheat_loops /= 2;
    total_loops_mode6 = preheat_loops * BENCH_TIME / timespent_w8_mode6;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_mode6 > 65535)
        total_loops_mode6 = 65535;
#endif

    // BENCHMARK
    timespent_w8_mode6 = profile_function(bench_w8_mode6);
    timespent_r8_mode6 = profile_function(bench_r8_mode6);
    timespent_w16_mode6 = profile_function(bench_w16_mode6);
    timespent_r16_mode6 = profile_function(bench_r16_mode6);

#ifdef __386__
    timespent_w32_mode6 = profile_function(bench_w32_mode6);
    timespent_r32_mode6 = profile_function(bench_r32_mode6);
#endif
}

void show_results_mode6(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_w8_mode6);
    total_result_r = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_r8_mode6);
    printf(MSG_8BIT, total_result_w, total_result_r);
    total_result_w = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_w16_mode6);
    total_result_r = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_r16_mode6);
    printf(MSG_16BIT, total_result_w, total_result_r);

#ifdef __386__
    total_result_w = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_w32_mode6);
    total_result_r = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_r32_mode6);
    printf(MSG_32BIT, total_result_w, total_result_r);
#endif
}

void export_results_mode6(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_w8_mode6);
    total_result_r = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_r8_mode6);
    fprintf(logFile, MSG_8BIT, total_result_w, total_result_r);
    total_result_w = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_w16_mode6);
    total_result_r = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_r16_mode6);
    fprintf(logFile, MSG_16BIT, total_result_w, total_result_r);

#ifdef __386__
    total_result_w = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_w32_mode6);
    total_result_r = ((double)total_loops_mode6 * 15.625 * 1000.0) / ((double)timespent_r32_mode6);
    fprintf(logFile, MSG_32BIT, total_result_w, total_result_r);
#endif
}
