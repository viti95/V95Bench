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

#include "modeC16.h"
#include "timer.h"
#include "file.h"

#include <dos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#define PREHEAT_LOOPS 200L
#define BENCH_TIME 5000L

unsigned long total_loops_modeC16;
unsigned long timespent_w8_modeC16;
unsigned long timespent_r8_modeC16;

void init_modeC16(void)
{
#ifdef __386__
    unsigned char *vram = (unsigned char *)0xB8000;
#else
    unsigned char far *vram = MK_FP(0xB800, 0);
#endif

    unsigned int i;
    union REGS regs;

    // Set 80x25 color mode
    regs.w.ax = 0x03;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif

    // Disable cursor
    regs.h.ah = 0x01;
    regs.h.ch = 0x3F;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif

    // Disable blinking
    regs.h.ah = 0x10;
    regs.h.al = 0x03;
    regs.h.bl = 0x00;
    regs.h.bh = 0x00;
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif

    /* set mode control register for 80x25 text mode and disable video output */
    outp(0x3D8, 1);

    /*
        These settings put the 6845 into "graphics" mode without actually
        switching the CGA controller into graphics mode.  The register
        values are directly copied from CGA graphics mode register
        settings.  The 6845 does not directly display graphics, the
        6845 only generates addresses and sync signals, the CGA
        attribute controller either displays character ROM data or color
        pixel data, this is external to the 6845 and keeps the CGA card
        in text mode.
        ref: HELPPC
    */

    /* set vert total lines to 127 */
    outp(0x3D4, 0x04);
    outp(0x3D5, 0x7F);
    /* set vert displayed char rows to 100 */
    outp(0x3D4, 0x06);
    outp(0x3D5, 0x64);
    /* set vert sync position to 112 */
    outp(0x3D4, 0x07);
    outp(0x3D5, 0x70);
    /* set char scan line count to 1 */
    outp(0x3D4, 0x09);
    outp(0x3D5, 0x01);

    /* re-enable the video output in 80x25 text mode */
    outp(0x3D8, 9);

    for (i = 0; i < 16000; i += 2)
    {
        vram[i] = 0xDE;
    }
}

void preheat_modeC16(unsigned long total_loops)
{
    total_loops_modeC16 = total_loops;
    bench_w8_modeC16();
}

void bench_w8_modeC16(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeC16;

    do
    {

#ifdef __386__
        for (vram = (unsigned char *)0xB8001; vram < (unsigned char *)0xBBE81; vram += 16)
#else
        for (vram = MK_FP(0xB800, 0x0001); vram < MK_FP(0xB800, 0x3E81); vram += 16)
#endif
        {
            *(vram) = 0xA3;
            *(vram + 2) = 0xA3;
            *(vram + 4) = 0xA3;
            *(vram + 6) = 0xA3;
            *(vram + 8) = 0xA3;
            *(vram + 10) = 0xA3;
            *(vram + 12) = 0xA3;
            *(vram + 14) = 0xA3;
        }
    } while (num_loops-- != 0);
}

void bench_r8_modeC16(void)
{
#ifdef __386__
    unsigned char *vram;
#else
    unsigned char far *vram;
#endif

    unsigned int num_loops = total_loops_modeC16;

    unsigned char read1, read2, read3, read4;

    do
    {

#ifdef __386__
        for (vram = (unsigned char *)0xB8001; vram < (unsigned char *)0xBBE81; vram += 8)
#else
        for (vram = MK_FP(0xB800, 0x0001); vram < MK_FP(0xB800, 0x3E81); vram += 8)
#endif
        {
            read1 = *(vram);
            read2 = *(vram + 2);
            read3 = *(vram + 4);
            read4 = *(vram + 6);
        }
    } while (num_loops-- != 0);

    read_fix_8b_1 = read1;
    read_fix_8b_2 = read2;
    read_fix_8b_3 = read3;
    read_fix_8b_4 = read4;
}

void execute_bench_modeC16(void)
{
    unsigned long preheat_loops = PREHEAT_LOOPS;

    // SET VIDEO MODE
    init_modeC16();

    // PRE-HEAT
    do
    {
        timespent_w8_modeC16 = profile_function_loops(preheat_modeC16, preheat_loops);
        preheat_loops *= 2;
    } while (timespent_w8_modeC16 == 0);
    preheat_loops /= 2;
    total_loops_modeC16 = preheat_loops * BENCH_TIME / timespent_w8_modeC16;

#ifndef __386__
    // Fix for 16-bit executables
    if (total_loops_modeC16 > 65535)
        total_loops_modeC16 = 65535;
#endif

    // BENCHMARK
    timespent_w8_modeC16 = profile_function(bench_w8_modeC16);
    timespent_r8_modeC16 = profile_function(bench_r8_modeC16);
}

void show_results_modeC16(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = ((double)total_loops_modeC16 * 7.8125 * 1000.0) / ((double)timespent_w8_modeC16);
    total_result_r = ((double)total_loops_modeC16 * 7.8125 * 1000.0) / ((double)timespent_r8_modeC16);
    printf("CGA 160x100 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n", total_result_w, total_result_r);
}

void export_results_modeC16(void)
{
    double total_result_w;
    double total_result_r;

    total_result_w = ((double)total_loops_modeC16 * 7.8125 * 1000.0) / ((double)timespent_w8_modeC16);
    total_result_r = ((double)total_loops_modeC16 * 7.8125 * 1000.0) / ((double)timespent_r8_modeC16);
    fprintf(logFile, "CGA 160x100 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n", total_result_w, total_result_r);
}
