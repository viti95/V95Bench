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

#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "file.h"
#include "mode1.h"
#include "mode3.h"
#include "mode4.h"
#include "modeC16.h"
#include "modeV16.h"
#include "mode6.h"
#include "mode7.h"
#include "mode8.h"
#include "mode9.h"
#include "modeA.h"
#include "mode13.h"
#include "modeY.h"
#include "modeD.h"
#include "modeE.h"
#include "mode10.h"
#include "modePCP.h"
#include "modeHGC.h"
#include "modeATI.h"

unsigned char videomode;
unsigned char menu_selection;

unsigned char do_bench_mode1 = 0;
unsigned char do_bench_mode3 = 0;
unsigned char do_bench_mode4 = 0;
unsigned char do_bench_modeC16 = 0;
unsigned char do_bench_modeV16 = 0;
unsigned char do_bench_mode6 = 0;
unsigned char do_bench_mode7 = 0;
unsigned char do_bench_mode8 = 0;
unsigned char do_bench_mode9 = 0;
unsigned char do_bench_modeA = 0;
unsigned char do_bench_mode13 = 0;
unsigned char do_bench_modeY = 0;
unsigned char do_bench_modeD = 0;
unsigned char do_bench_modeE = 0;
unsigned char do_bench_mode10 = 0;
unsigned char do_bench_modePCP = 0;
unsigned char do_bench_modeHGC = 0;
unsigned char do_bench_modeATI = 0;

void pause_keyboard(void)
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void launch_bench_mode(unsigned char *do_bench_mode, void (*exececute_bench_mode)(void))
{
    *do_bench_mode = 1;
    exececute_bench_mode();
}

void select_benchmark(void)
{
    switch (videomode)
    {
    case MDA:
        launch_bench_mode(&do_bench_mode7, execute_bench_mode7);
        break;
    case HGC:
        launch_bench_mode(&do_bench_mode7, execute_bench_mode7);
        launch_bench_mode(&do_bench_modeHGC, execute_bench_modeHGC);
        break;
    case CGA:
        launch_bench_mode(&do_bench_mode1, execute_bench_mode1);
        launch_bench_mode(&do_bench_mode3, execute_bench_mode3);
        launch_bench_mode(&do_bench_modeC16, execute_bench_modeC16);
        launch_bench_mode(&do_bench_mode4, execute_bench_mode4);
        launch_bench_mode(&do_bench_mode6, execute_bench_mode6);
        break;
    case EGA:
        launch_bench_mode(&do_bench_mode1, execute_bench_mode1);
        launch_bench_mode(&do_bench_mode3, execute_bench_mode3);
        launch_bench_mode(&do_bench_mode4, execute_bench_mode4);
        launch_bench_mode(&do_bench_mode6, execute_bench_mode6);
        launch_bench_mode(&do_bench_modeD, execute_bench_modeD);
        launch_bench_mode(&do_bench_modeE, execute_bench_modeE);
        launch_bench_mode(&do_bench_mode10, execute_bench_mode10);
        break;
    case MCGA:
        launch_bench_mode(&do_bench_mode1, execute_bench_mode1);
        launch_bench_mode(&do_bench_mode3, execute_bench_mode3);
        launch_bench_mode(&do_bench_modeC16, execute_bench_modeC16);
        launch_bench_mode(&do_bench_mode4, execute_bench_mode4);
        launch_bench_mode(&do_bench_mode6, execute_bench_mode6);
        launch_bench_mode(&do_bench_mode13, execute_bench_mode13);
        break;
    case VGA:
        launch_bench_mode(&do_bench_mode1, execute_bench_mode1);
        launch_bench_mode(&do_bench_mode3, execute_bench_mode3);
        launch_bench_mode(&do_bench_mode4, execute_bench_mode4);
        launch_bench_mode(&do_bench_mode6, execute_bench_mode6);
        launch_bench_mode(&do_bench_modeD, execute_bench_modeD);
        launch_bench_mode(&do_bench_modeE, execute_bench_modeE);
        launch_bench_mode(&do_bench_mode10, execute_bench_mode10);
        launch_bench_mode(&do_bench_modeV16, execute_bench_modeV16);
        launch_bench_mode(&do_bench_mode13, execute_bench_mode13);
        launch_bench_mode(&do_bench_modeY, execute_bench_modeY);
        break;
    case VESA:
        break;
    case TandyPCjr:
        launch_bench_mode(&do_bench_mode1, execute_bench_mode1);
        launch_bench_mode(&do_bench_mode3, execute_bench_mode3);
        launch_bench_mode(&do_bench_modeC16, execute_bench_modeC16);
        launch_bench_mode(&do_bench_mode4, execute_bench_mode4);
        launch_bench_mode(&do_bench_mode6, execute_bench_mode6);
        launch_bench_mode(&do_bench_mode8, execute_bench_mode8);
        launch_bench_mode(&do_bench_mode9, execute_bench_mode9);
        launch_bench_mode(&do_bench_modeA, execute_bench_modeA);
        break;
    case ATI:
        launch_bench_mode(&do_bench_mode1, execute_bench_mode1);
        launch_bench_mode(&do_bench_mode3, execute_bench_mode3);
        launch_bench_mode(&do_bench_modeC16, execute_bench_modeC16);
        launch_bench_mode(&do_bench_mode4, execute_bench_mode4);
        launch_bench_mode(&do_bench_mode6, execute_bench_mode6);
        launch_bench_mode(&do_bench_modePCP, execute_bench_modePCP);
        launch_bench_mode(&do_bench_modeATI, execute_bench_modeATI);
        break;
    case Plantronics:
        launch_bench_mode(&do_bench_mode1, execute_bench_mode1);
        launch_bench_mode(&do_bench_mode3, execute_bench_mode3);
        launch_bench_mode(&do_bench_modeC16, execute_bench_modeC16);
        launch_bench_mode(&do_bench_mode4, execute_bench_mode4);
        launch_bench_mode(&do_bench_mode6, execute_bench_mode6);
        launch_bench_mode(&do_bench_modePCP, execute_bench_modePCP);
        break;
    default:
        printf("Invalid option :(");
        exit(EXIT_FAILURE);
        return;
    }
}

void reset_video(void)
{

    union REGS regs;

    if (videomode == HGC)
    {
        regs.w.ax = 7;
    }
    else
    {
        regs.w.ax = 3;
    }

// back to text mode
#ifdef __386__
    int386(0x10, &regs, &regs);
#else
    int86(0x10, &regs, &regs);
#endif
}

void show_results(void)
{
    printf("Results (press key Enter to continue)\n\n");

    if (do_bench_mode7)
    {
        show_results_mode7();
        pause_keyboard();
    }

    if (do_bench_modeHGC)
    {
        show_results_modeHGC();
        pause_keyboard();
    }

    if (do_bench_mode1)
    {
        show_results_mode1();
        pause_keyboard();
    }

    if (do_bench_mode3)
    {
        show_results_mode3();
        pause_keyboard();
    }

    if (do_bench_modeC16)
    {
        show_results_modeC16();
        pause_keyboard();
    }

    if (do_bench_mode4)
    {
        show_results_mode4();
        pause_keyboard();
    }

    if (do_bench_mode6)
    {
        show_results_mode6();
        pause_keyboard();
    }

    if (do_bench_mode8)
    {
        show_results_mode8();
        pause_keyboard();
    }

    if (do_bench_mode9)
    {
        show_results_mode9();
        pause_keyboard();
    }

    if (do_bench_modeA)
    {
        show_results_modeA();
        pause_keyboard();
    }

    if (do_bench_modePCP)
    {
        show_results_modePCP();
        pause_keyboard();
    }

    if (do_bench_modeATI)
    {
        show_results_modeATI();
        pause_keyboard();
    }

    if (do_bench_modeD)
    {
        show_results_modeD();
        pause_keyboard();
    }

    if (do_bench_modeE)
    {
        show_results_modeE();
        pause_keyboard();
    }

    if (do_bench_mode10)
    {
        show_results_mode10();
        pause_keyboard();
    }

    if (do_bench_modeV16)
    {
        show_results_modeV16();
        pause_keyboard();
    }

    if (do_bench_mode13)
    {
        show_results_mode13();
        pause_keyboard();
    }

    if (do_bench_modeY)
    {
        show_results_modeY();
        pause_keyboard();
    }
}

void export_results(char *filename)
{
    open_results_file(filename);

    if (do_bench_mode7)
        export_results_mode7();

    if (do_bench_modeHGC)
        export_results_modeHGC();

    if (do_bench_mode1)
        export_results_mode1();

    if (do_bench_mode3)
        export_results_mode3();

    if (do_bench_modeC16)
        export_results_modeC16();

    if (do_bench_mode4)
        export_results_mode4();

    if (do_bench_mode6)
        export_results_mode6();

    if (do_bench_mode8)
        export_results_mode8();

    if (do_bench_mode9)
        export_results_mode9();

    if (do_bench_modeA)
        export_results_modeA();

    if (do_bench_modePCP)
        export_results_modePCP();

    if (do_bench_modeATI)
        export_results_modeATI();

    if (do_bench_modeD)
        export_results_modeD();

    if (do_bench_modeE)
        export_results_modeE();

    if (do_bench_mode10)
        export_results_mode10();

    if (do_bench_modeV16)
        export_results_modeV16();

    if (do_bench_mode13)
        export_results_mode13();

    if (do_bench_modeY)
        export_results_modeY();

    close_results_file();

    printf("Results exported to file %s\n", filename);
}

int main(int argc, char **argv)
{
    char filename[13];

    printf("\n");
    printf("=====================\n");
    printf("= V95 GPU Benchmark =\n");
    printf("=====================\n");
    printf("\n");
    printf("Please select video card:\n");
    printf("\n");
    printf("    1.  MDA\n");
    printf("    2.  Hercules\n");
    printf("    3.  CGA\n");
    printf("    4.  EGA\n");
    printf("    5.  MCGA\n");
    printf("    6.  VGA\n");
    printf("    7.  VESA (not available)\n");
    printf("    8.  Tandy Video 1 / IBM PCjr\n");
    printf("    9.  ATI Small Wonder\n");
    printf("    10. Plantronics ColorPlus\n");
    printf("\n");

    printf("Select option: ");
    scanf("%u", &videomode);
    getchar(); // fix

    select_benchmark();

    reset_video();

    printf("\n");
    printf("Benchmark finished\n");
    printf("\n");
    printf("    1.  Show results\n");
    printf("    2.  Export results to file\n");
    printf("    3.  Both\n");
    printf("\n");

    printf("Select option: ");
    scanf("%u", &menu_selection);
    getchar(); // fix

    switch (menu_selection)
    {
    case 1:
        show_results();
        break;
    case 2:
        printf("Enter file name (8 characters max.)\n");
        scanf("%8s", filename);
        strcat(filename, ".txt");
        export_results(filename);
        break;
    case 3:
        show_results();

        printf("Enter file name (8 characters max.)\n");
        scanf("%8s", filename);
        strcat(filename, ".txt");
        export_results(filename);
        break;
    default:
        show_results();
        break;
    }

    return 0;
}
