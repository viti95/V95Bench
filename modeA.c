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

#include "modeA.h"
#include "timer.h"
#include "file.h"
#include "messages.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 50L
#define BENCH_TIME 5000L

unsigned long total_loops_modeA;
unsigned long timespent_w8_modeA;
unsigned long timespent_r8_modeA;
unsigned long timespent_w16_modeA;
unsigned long timespent_r16_modeA;

#ifdef __386__
unsigned long timespent_w32_modeA;
unsigned long timespent_r32_modeA;
#endif

void init_modeA(void)
{
    union REGS regs;

    // Set video mode A
    regs.w.ax = 0x0A;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif
}

void preheat_modeA(unsigned long total_loops)
{
    total_loops_modeA = total_loops;
    bench_w8_modeA();
}

void bench_w8_modeA(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeA;

    do
    {

#ifdef __386__
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB9F40; vram += 2)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x1F40); vram += 2)
#endif
        {
            *(vram) = 0xB5;
            *(vram + 1) = 0xB5;
            *(vram + 0x2000) = 0xB5;
            *(vram + 0x2001) = 0xB5;
            *(vram + 0x4000) = 0xB5;
            *(vram + 0x4001) = 0xB5;
            *(vram + 0x6000) = 0xB5;
            *(vram + 0x6001) = 0xB5;
        }
    } while (num_loops-- != 0);
}

void bench_w16_modeA(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeA;

    do
    {

#ifdef __386__
        for (vram = (unsigned short *)0xB8000; vram < (unsigned short *)0xB9F40; vram += 2)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x1F40); vram += 2)
#endif
        {
            *(vram) = 0x5C9E;
            *(vram + 1) = 0x5C9E;
            *(vram + 0x1000) = 0x5C9E;
            *(vram + 0x1001) = 0x5C9E;
            *(vram + 0x2000) = 0x5C9E;
            *(vram + 0x2001) = 0x5C9E;
            *(vram + 0x3000) = 0x5C9E;
            *(vram + 0x3001) = 0x5C9E;
        }
    } while (num_loops-- != 0);
}

#ifdef __386__
void bench_w32_modeA(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeA;

    do
    {
        for (vram = (unsigned int *)0xB8000; vram < (unsigned int *)0xB9F40; vram += 2)
        {
            *(vram) = 0x36E15792;
            *(vram + 1) = 0x36E15792;
            *(vram + 0x800) = 0x36E15792;
            *(vram + 0x801) = 0x36E15792;
            *(vram + 0x1000) = 0x36E1C5792;
            *(vram + 0x1001) = 0x36E15792;
            *(vram + 0x1800) = 0x36E15792;
            *(vram + 0x1801) = 0x36E15792;
        }
    } while (num_loops-- != 0);
}
#endif

void bench_r8_modeA(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeA;

    unsigned char read1, read2, read3, read4;

    do
    {

#ifdef __386__
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB9F40; vram++)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x1F40); vram++)
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

void bench_r16_modeA(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeA;

    unsigned short read1, read2, read3, read4;

    do
    {

#ifdef __386__
        for (vram = (unsigned short *)0xB8000; vram < (unsigned short *)0xB9F40; vram++)
#else
        for (vram = MK_FP(0xB800, 0); vram < MK_FP(0xB800, 0x1F40); vram++)
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
void bench_r32_modeA(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeA;

    unsigned int read1, read2, read3, read4;

    do
    {
        for (vram = (unsigned int *)0xB8000; vram < (unsigned int *)0xB9F40; vram++)
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

void execute_bench_modeA(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_modeA();

    // PRE-HEAT
    do
    {
        timespent_w8_modeA = profile_function_loops(preheat_modeA, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_modeA == 0);
    preheat_loops /= 2;
    total_loops_modeA = preheat_loops * BENCH_TIME / timespent_w8_modeA;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_modeA > 65535)
        total_loops_modeA = 65535;
#endif

    // BENCHMARK
    timespent_w8_modeA = profile_function(bench_w8_modeA);
    timespent_r8_modeA = profile_function(bench_r8_modeA);
    timespent_w16_modeA = profile_function(bench_w16_modeA);
    timespent_r16_modeA = profile_function(bench_r16_modeA);

#ifdef __386__
    timespent_w32_modeA = profile_function(bench_w32_modeA);
    timespent_r32_modeA = profile_function(bench_r32_modeA);
#endif
}

void show_results_modeA(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = calc_kb_second(total_loops_modeA, 31.25, timespent_w8_modeA);
    total_result_r = calc_kb_second(total_loops_modeA, 31.25, timespent_r8_modeA);
    printf(MSG_MODEA_8BIT, total_result_w, total_result_r);
    total_result_w = calc_kb_second(total_loops_modeA, 31.25, timespent_w16_modeA);
    total_result_r = calc_kb_second(total_loops_modeA, 31.25, timespent_r16_modeA);
    printf(MSG_GENERIC_16BIT + 1, total_result_w, total_result_r);

#ifdef __386__
    total_result_w = calc_kb_second(total_loops_modeA, 31.25, timespent_w32_modeA);
    total_result_r = calc_kb_second(total_loops_modeA, 31.25, timespent_r32_modeA);
    printf(MSG_GENERIC_32BIT + 1, total_result_w, total_result_r);
#endif
}

void export_results_modeA(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = calc_kb_second(total_loops_modeA, 31.25, timespent_w8_modeA);
    total_result_r = calc_kb_second(total_loops_modeA, 31.25, timespent_r8_modeA);
    fprintf(logFile, MSG_MODEA_8BIT, total_result_w, total_result_r);
    total_result_w = calc_kb_second(total_loops_modeA, 31.25, timespent_w16_modeA);
    total_result_r = calc_kb_second(total_loops_modeA, 31.25, timespent_r16_modeA);
    fprintf(logFile, MSG_GENERIC_16BIT + 1, total_result_w, total_result_r);

#ifdef __386__
    total_result_w = calc_kb_second(total_loops_modeA, 31.25, timespent_w32_modeA);
    total_result_r = calc_kb_second(total_loops_modeA, 31.25, timespent_r32_modeA);
    fprintf(logFile, MSG_GENERIC_32BIT + 1, total_result_w, total_result_r);
#endif
}
