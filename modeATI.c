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

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 25
#define BENCH_TIME 5000

unsigned int total_loops_modeATI;
unsigned long timespent_modeATI;

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

void preheat_modeATI(void)
{
    unsigned int loops;
    unsigned char *vram;

    for (loops = 0; loops < PREHEAT_LOOPS; loops++)
    {
        for (vram = (unsigned char *)0xB0000; vram < (unsigned char *)0xB1F40; vram++)
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
    }
}

void bench_modeATI(void)
{
    unsigned char *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops_modeATI;

    for (loops = 0; loops < num_loops; loops++)
    {
        for (vram = (unsigned char *)0xB0000; vram < (unsigned char *)0xB1F40; vram++)
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
    }
}

void execute_bench_modeATI(void)
{
    // SET VIDEO MODE
    init_modeATI();

    // PRE-HEAT
    timespent_modeATI = profile_function(preheat_modeATI);
    total_loops_modeATI = PREHEAT_LOOPS * BENCH_TIME / timespent_modeATI;

    // BENCHMARK
    timespent_modeATI = profile_function(bench_modeATI);
}

void show_results_modeATI(void)
{
    double total_result;

    total_result = ((double)total_loops_modeATI * 62.5 * 1000) / ((double)timespent_modeATI);
    printf("ATI 640x200 16c: %.2lf kb/s\n", total_result);
}
