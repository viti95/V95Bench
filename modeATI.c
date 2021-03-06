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

#include "modeATI.h"
#include "timer.h"
#include "file.h"
#include "messages.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 25L
#define BENCH_TIME 5000L

unsigned long total_loops_modeATI;
unsigned long timespent_w8_modeATI;
unsigned long timespent_r8_modeATI;
unsigned long timespent_w16_modeATI;
unsigned long timespent_r16_modeATI;

#ifdef __386__
unsigned long timespent_w32_modeATI;
unsigned long timespent_r32_modeATI;
#endif

void init_modeATI(void)
{
    static int parms[16] = {0x70, 0x50, 0x58, 0x0a,
                            0x40, 0x06, 0x32, 0x38,
                            0x02, 0x03, 0x06, 0x07,
                            0x00, 0x00, 0x00, 0x00};
    int i;

    /* Set the Graphics Solution to 640 x 200 with 16 colors in
       Color Mode */
    outp(0x3D8, 0x2);

    /* Set extended graphics registers */
    outp(0x3DD, 0x80);

    outp(0x03D8, 0x2);
    /* Program 6845 crt controlller */
    for (i = 0; i < 16; ++i)
    {
        outp(0x3D4, i);
        outp(0x3D5, parms[i]);
    }
    outp(0x3D8, 0x0A);
    outp(0x3D9, 0x30);

    outp(0x3DD, 0x80);
}

void preheat_modeATI(unsigned long total_loops)
{
    total_loops_modeATI = total_loops;
    bench_w8_modeATI();
}

void bench_w8_modeATI(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeATI;

    do
    {

#ifdef __386__
        for (vram = (unsigned char *)0xB0000; vram < (unsigned char *)0xB1F40; vram++)
#else
        for (vram = MK_FP(0xB000, 0); vram < MK_FP(0xB000, 0x1F40); vram++)
#endif
        {
            *(vram) = 0x55;
            *(vram + 0x2000) = 0x55;
            *(vram + 0x4000) = 0x55;
            *(vram + 0x6000) = 0x55;
            *(vram + 0x8000) = 0x55;
            *(vram + 0xA000) = 0x55;
            *(vram + 0xC000) = 0x55;
            *(vram + 0xE000) = 0x55;
        }
    } while (num_loops-- != 0);
}

void bench_w16_modeATI(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeATI;

    do
    {

#ifdef __386__
        for (vram = (unsigned short *)0xB0000; vram < (unsigned short *)0xB1F40; vram++)
#else
        for (vram = MK_FP(0xB000, 0); vram < MK_FP(0xB000, 0x1F40); vram++)
#endif
        {
            *(vram) = 0xEA23;
            *(vram + 0x1000) = 0xEA23;
            *(vram + 0x2000) = 0xEA23;
            *(vram + 0x3000) = 0xEA23;
            *(vram + 0x4000) = 0xEA23;
            *(vram + 0x5000) = 0xEA23;
            *(vram + 0x6000) = 0xEA23;
            *(vram + 0x7000) = 0xEA23;
        }
    } while (num_loops-- != 0);
}

#ifdef __386__
void bench_w32_modeATI(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeATI;

    do
    {
        for (vram = (unsigned int *)0xB0000; vram < (unsigned int *)0xB1F40; vram++)
        {
            *(vram) = 0x7F2A035C;
            *(vram + 0x800) = 0x7F2A035C;
            *(vram + 0x1000) = 0x7F2A035C;
            *(vram + 0x1800) = 0x7F2A035C;
            *(vram + 0x2000) = 0x7F2A035C;
            *(vram + 0x2800) = 0x7F2A035C;
            *(vram + 0x3000) = 0x7F2A035C;
            *(vram + 0x3800) = 0x7F2A035C;
        }
    } while (num_loops-- != 0);
}
#endif

void bench_r8_modeATI(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeATI;

    unsigned char read1, read2, read3, read4, read5, read6, read7, read8;

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
            read5 = *(vram + 0x8000);
            read6 = *(vram + 0xA000);
            read7 = *(vram + 0xC000);
            read8 = *(vram + 0xE000);
        }
    } while (num_loops-- != 0);

    read_fix_8b_1 = read1;
    read_fix_8b_2 = read2;
    read_fix_8b_3 = read3;
    read_fix_8b_4 = read4;
    read_fix_8b_5 = read5;
    read_fix_8b_6 = read6;
    read_fix_8b_7 = read7;
    read_fix_8b_8 = read8;
}

void bench_r16_modeATI(void)
{
#ifdef __386__
    unsigned short *vram;
#else
    unsigned short far *vram;
#endif

    unsigned int num_loops = total_loops_modeATI;

    unsigned short read1, read2, read3, read4, read5, read6, read7, read8;

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
            read5 = *(vram + 0x4000);
            read6 = *(vram + 0x5000);
            read7 = *(vram + 0x6000);
            read8 = *(vram + 0x7000);
        }
    } while (num_loops-- != 0);

    read_fix_16b_1 = read1;
    read_fix_16b_2 = read2;
    read_fix_16b_3 = read3;
    read_fix_16b_4 = read4;
    read_fix_16b_5 = read5;
    read_fix_16b_6 = read6;
    read_fix_16b_7 = read7;
    read_fix_16b_8 = read8;
}

#ifdef __386__
void bench_r32_modeATI(void)
{
    unsigned int *vram;

    unsigned int num_loops = total_loops_modeATI;

    unsigned int read1, read2, read3, read4, read5, read6, read7, read8;

    do
    {
        for (vram = (unsigned int *)0xB0000; vram < (unsigned int *)0xB1F40; vram++)
        {
            read1 = *(vram);
            read2 = *(vram + 0x800);
            read3 = *(vram + 0x1000);
            read4 = *(vram + 0x1800);
            read5 = *(vram + 0x2000);
            read6 = *(vram + 0x2800);
            read7 = *(vram + 0x3000);
            read8 = *(vram + 0x3800);
        }
    } while (num_loops-- != 0);

    read_fix_32b_1 = read1;
    read_fix_32b_2 = read2;
    read_fix_32b_3 = read3;
    read_fix_32b_4 = read4;
    read_fix_32b_5 = read5;
    read_fix_32b_6 = read6;
    read_fix_32b_7 = read7;
    read_fix_32b_8 = read8;
}
#endif

void execute_bench_modeATI(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_modeATI();

    // PRE-HEAT
    do
    {
        timespent_w8_modeATI = profile_function_loops(preheat_modeATI, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_modeATI == 0);
    preheat_loops /= 2;
    total_loops_modeATI = preheat_loops * BENCH_TIME / timespent_w8_modeATI;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_modeATI > 65535)
        total_loops_modeATI = 65535;
#endif

    // BENCHMARK
    timespent_w8_modeATI = profile_function(bench_w8_modeATI);
    timespent_r8_modeATI = profile_function(bench_r8_modeATI);
    timespent_w16_modeATI = profile_function(bench_w16_modeATI);
    timespent_r16_modeATI = profile_function(bench_r16_modeATI);

#ifdef __386__
    timespent_w32_modeATI = profile_function(bench_w32_modeATI);
    timespent_r32_modeATI = profile_function(bench_r32_modeATI);
#endif
}

void get_results_modeATI(unsigned char to_file)
{
    double total_result_w;
    double total_result_r;

    total_result_w = calc_kb_second(total_loops_modeATI, 62.5, timespent_w8_modeATI);
    total_result_r = calc_kb_second(total_loops_modeATI, 62.5, timespent_r8_modeATI);

    if (to_file)
        fprintf(logFile, MSG_MODEATI_8BIT, total_result_w, total_result_r);
    else
        printf(MSG_MODEATI_8BIT, total_result_w, total_result_r);

    total_result_w = calc_kb_second(total_loops_modeATI, 62.5, timespent_w16_modeATI);
    total_result_r = calc_kb_second(total_loops_modeATI, 62.5, timespent_r16_modeATI);

    if (to_file)
        fprintf(logFile, MSG_GENERIC_16BIT + 7, total_result_w, total_result_r);
    else
        printf(MSG_GENERIC_16BIT + 7, total_result_w, total_result_r);

#ifdef __386__
    total_result_w = calc_kb_second(total_loops_modeATI, 62.5, timespent_w32_modeATI);
    total_result_r = calc_kb_second(total_loops_modeATI, 62.5, timespent_r32_modeATI);

    if (to_file)
        fprintf(logFile, MSG_GENERIC_32BIT + 7, total_result_w, total_result_r);
    else
        printf(MSG_GENERIC_32BIT + 7, total_result_w, total_result_r);
#endif
}
