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
#include "file.h"
#include "messages.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PREHEAT_LOOPS 400L
#define BENCH_TIME 5000L

unsigned long total_loops_mode3;
unsigned long timespent_w8_mode3;
unsigned long timespent_r8_mode3;
unsigned long timespent_w16_mode3;
unsigned long timespent_r16_mode3;

#ifdef __386__
unsigned long timespent_w32_mode3;
unsigned long timespent_r32_mode3;
#endif

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
    total_loops_mode3 = total_loops;
    bench_w8_mode3();
}

void bench_w8_mode3(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_mode3;

    do
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
    } while (num_loops-- != 0);
}

void bench_w16_mode3(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_mode3;

    do
    {
#ifdef __386__
        for (vram = (unsigned short *)0xB8000; vram < (unsigned short *)0xB8FA0; vram += 8)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x0FA0); vram += 8)
#endif
        {
            *(vram) = 0x8391;
            *(vram + 1) = 0x8391;
            *(vram + 2) = 0x8391;
            *(vram + 3) = 0x8391;
            *(vram + 4) = 0x8391;
            *(vram + 5) = 0x8391;
            *(vram + 6) = 0x8391;
            *(vram + 7) = 0x8391;
        }
    } while (num_loops-- != 0);
}

#ifdef __386__
void bench_w32_mode3(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_mode3;

    do
    {
        for (vram = (unsigned int *)0xB8000; vram < (unsigned int *)0xB8FA0; vram += 8)
        {
            *(vram) = 0x14C2ABEF;
            *(vram + 1) = 0x14C2ABEF;
            *(vram + 2) = 0x14C2ABEF;
            *(vram + 3) = 0x14C2ABEF;
            *(vram + 4) = 0x14C2ABEF;
            *(vram + 5) = 0x14C2ABEF;
            *(vram + 6) = 0x14C2ABEF;
            *(vram + 7) = 0x14C2ABEF;
        }
    } while (num_loops-- != 0);
}
#endif

void bench_r8_mode3(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_mode3;

    unsigned char read1, read2, read3, read4;

    do
    {
#ifdef __386__
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB8FA0; vram += 4)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x0FA0); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }
    } while (num_loops-- != 0);

    read_fix_8b_1 = read1;
    read_fix_8b_2 = read2;
    read_fix_8b_3 = read3;
    read_fix_8b_4 = read4;
}

void bench_r16_mode3(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_mode3;

    unsigned short read1, read2, read3, read4;

    do
    {
#ifdef __386__
        for (vram = (unsigned short *)0xB8000; vram < (unsigned short *)0xB8FA0; vram += 4)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x0FA0); vram += 4)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }
    } while (num_loops-- != 0);

    read_fix_16b_1 = read1;
    read_fix_16b_2 = read2;
    read_fix_16b_3 = read3;
    read_fix_16b_4 = read4;
}

#ifdef __386__
void bench_r32_mode3(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_mode3;

    unsigned int read1, read2, read3, read4;

    do
    {
        for (vram = (unsigned int *)0xB8000; vram < (unsigned int *)0xB8FA0; vram += 4)
        {
            read1 = *(vram);
            read2 = *(vram + 1);
            read3 = *(vram + 2);
            read4 = *(vram + 3);
        }
    } while (num_loops-- != 0);

    read_fix_32b_1 = read1;
    read_fix_32b_2 = read2;
    read_fix_32b_3 = read3;
    read_fix_32b_4 = read4;
}
#endif

void execute_bench_mode3(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_mode3();

    // PRE-HEAT
    do
    {
        timespent_w8_mode3 = profile_function_loops(preheat_mode3, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_mode3 == 0);
    preheat_loops /= 2;
    total_loops_mode3 = preheat_loops * BENCH_TIME / timespent_w8_mode3;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_mode3 > 65535)
        total_loops_mode3 = 65535;
#endif

    // BENCHMARK
    timespent_w8_mode3 = profile_function(bench_w8_mode3);
    timespent_r8_mode3 = profile_function(bench_r8_mode3);
    timespent_w16_mode3 = profile_function(bench_w16_mode3);
    timespent_r16_mode3 = profile_function(bench_r16_mode3);

#ifdef __386__
    timespent_w32_mode3 = profile_function(bench_w32_mode3);
    timespent_r32_mode3 = profile_function(bench_r32_mode3);
#endif
}

void get_results_mode3(unsigned char to_file)
{
    double total_result_w;
    double total_result_r;

    total_result_w = calc_kb_second(total_loops_mode3, 3.90625, timespent_w8_mode3);
    total_result_r = calc_kb_second(total_loops_mode3, 3.90625, timespent_r8_mode3);

    if (to_file)
        fprintf(logFile, MSG_MODE3_8BIT, total_result_w, total_result_r);
    else
        printf(MSG_MODE3_8BIT, total_result_w, total_result_r);

    total_result_w = calc_kb_second(total_loops_mode3, 3.90625, timespent_w16_mode3);
    total_result_r = calc_kb_second(total_loops_mode3, 3.90625, timespent_r16_mode3);

    if (to_file)
        fprintf(logFile, MSG_GENERIC_16BIT + 9, total_result_w, total_result_r);
    else
        printf(MSG_GENERIC_16BIT + 9, total_result_w, total_result_r);

#ifdef __386__
    total_result_w = calc_kb_second(total_loops_mode3, 3.90625, timespent_w32_mode3);
    total_result_r = calc_kb_second(total_loops_mode3, 3.90625, timespent_r32_mode3);

    if (to_file)
        fprintf(logFile, MSG_GENERIC_32BIT + 9, total_result_w, total_result_r);
    else
        printf(MSG_GENERIC_32BIT + 9, total_result_w, total_result_r);
#endif
}
