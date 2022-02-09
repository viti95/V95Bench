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

#include "modePCP.h"
#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 50
#define BENCH_TIME 5000

unsigned int total_loops_modePCP;
unsigned long timespent_modePCP;

void init_modePCP(void)
{
    union REGS regs;

    regs.w.ax = 0x04;
    int386(0x10, (union REGS *)&regs, &regs);

    outp(0x3DD, 0x10);
}

void preheat_modePCP(void)
{
    unsigned int loops;
    unsigned char *vram;

    for (loops = 0; loops < PREHEAT_LOOPS; loops++)
    {
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB9F40; vram += 2){
            *(vram) = 0x55;
            *(vram + 1) = 0x55;
            *(vram + 0x4000) = 0x55;
            *(vram + 0x4001) = 0x55;
            *(vram + 0x2000) = 0x55;
            *(vram + 0x2001) = 0x55;
            *(vram + 0x6000) = 0x55;
            *(vram + 0x6001) = 0x55;
        }
    }
}

void bench_modePCP(void)
{
    unsigned char *vram;

    unsigned int loops;
    unsigned int num_loops = total_loops_modePCP;

    for (loops = 0; loops < num_loops; loops++)
    {
        for (vram = (unsigned char *)0xB8000; vram < (unsigned char *)0xB9F40; vram += 2){
            *(vram) = 0x55;
            *(vram + 1) = 0x55;
            *(vram + 0x4000) = 0x55;
            *(vram + 0x4001) = 0x55;
            *(vram + 0x2000) = 0x55;
            *(vram + 0x2001) = 0x55;
            *(vram + 0x6000) = 0x55;
            *(vram + 0x6001) = 0x55;
        }
    }
}

void execute_bench_modePCP(void)
{
    // SET VIDEO MODE
    init_modePCP();

    // PRE-HEAT
    timespent_modePCP = profile_function(preheat_modePCP);
    total_loops_modePCP = PREHEAT_LOOPS * BENCH_TIME / timespent_modePCP;

    // BENCHMARK
    timespent_modePCP = profile_function(bench_modePCP);
}

void show_results_modePCP(void)
{
    double total_result;

    total_result = ((double)total_loops_modePCP * 31.25 * 1000) / ((double)timespent_modePCP);
    printf("Plantronics ColorPlus: %.2lf kb/s\n", total_result);
}