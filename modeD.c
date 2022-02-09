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

#define PREHEAT_LOOPS 50
#define BENCH_TIME 5000

unsigned int total_loops_modeD;
unsigned long timespent_modeD;

void init_modeD(void)
{
    union REGS regs;

    // Set video mode D
    regs.w.ax = 0x0D;
    int386(0x10, (union REGS *)&regs, &regs);

    outp(0x3C4, 0x2);
}

void preheat_modeD(void)
{
    unsigned int loops;
    unsigned char *vram;

    for (loops = 0; loops < PREHEAT_LOOPS; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }
    }
}

void bench_modeD(void)
{
    unsigned char *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops_modeD;

    for (loops = 0; loops < num_loops; loops++)
    {
        // Red
        outp(0x3C5, 1 << (3 & 0x03));

        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Green
        outp(0x3C5, 1 << (2 & 0x03));

        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Blue
        outp(0x3C5, 1 << (1 & 0x03));

        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }

        // Intensity
        outp(0x3C5, 1 << (0 & 0x03));

        for (vram = (unsigned char *)0xA0000; vram < (unsigned char *)0xA1F40; vram += 8)
        {
            *(vram) = 0xFF;
            *(vram + 1) = 0xFF;
            *(vram + 2) = 0xFF;
            *(vram + 3) = 0xFF;
            *(vram + 4) = 0xFF;
            *(vram + 5) = 0xFF;
            *(vram + 6) = 0xFF;
            *(vram + 7) = 0xFF;
        }
    }
}

void execute_bench_modeD(void)
{
    // SET VIDEO MODE
    init_modeD();

    // PRE-HEAT
    timespent_modeD = profile_function(preheat_modeD);
    total_loops_modeD = PREHEAT_LOOPS * BENCH_TIME / timespent_modeD;

    // BENCHMARK
    timespent_modeD = profile_function(bench_modeD);
}

void show_results_modeD(void)
{
    double total_result;

    total_result = ((double)total_loops_modeD * 31.25 * 1000) / ((double)timespent_modeD);
    printf("EGA Mode D: %.2lf kb/s\n", total_result);
}