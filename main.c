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

#define FALSE 0
#define TRUE  1

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
        get_results_mode7(FALSE);
        pause_keyboard();
    }

    if (do_bench_modeHGC)
    {
        get_results_modeHGC(FALSE);
        pause_keyboard();
    }

    if (do_bench_mode1)
    {
        get_results_mode1(FALSE);
        pause_keyboard();
    }

    if (do_bench_mode3)
    {
        get_results_mode3(FALSE);
        pause_keyboard();
    }

    if (do_bench_modeC16)
    {
        get_results_modeC16(FALSE);
        pause_keyboard();
    }

    if (do_bench_mode4)
    {
        get_results_mode4(FALSE);
        pause_keyboard();
    }

    if (do_bench_mode6)
    {
        get_results_mode6(FALSE);
        pause_keyboard();
    }

    if (do_bench_mode8)
    {
        get_results_mode8(FALSE);
        pause_keyboard();
    }

    if (do_bench_mode9)
    {
        get_results_mode9(FALSE);
        pause_keyboard();
    }

    if (do_bench_modeA)
    {
        get_results_modeA(FALSE);
        pause_keyboard();
    }

    if (do_bench_modePCP)
    {
        get_results_modePCP(FALSE);
        pause_keyboard();
    }

    if (do_bench_modeATI)
    {
        get_results_modeATI(FALSE);
        pause_keyboard();
    }

    if (do_bench_modeD)
    {
        get_results_modeD(FALSE);
        pause_keyboard();
    }

    if (do_bench_modeE)
    {
        get_results_modeE(FALSE);
        pause_keyboard();
    }

    if (do_bench_mode10)
    {
        get_results_mode10(FALSE);
        pause_keyboard();
    }

    if (do_bench_modeV16)
    {
        get_results_modeV16(FALSE);
        pause_keyboard();
    }

    if (do_bench_mode13)
    {
        get_results_mode13(FALSE);
        pause_keyboard();
    }

    if (do_bench_modeY)
    {
        get_results_modeY(FALSE);
        pause_keyboard();
    }
}

void export_results(char *filename)
{
    open_results_file(filename);

    if (do_bench_mode7)
        get_results_mode7(TRUE);

    if (do_bench_modeHGC)
        get_results_modeHGC(TRUE);

    if (do_bench_mode1)
        get_results_mode1(TRUE);

    if (do_bench_mode3)
        get_results_mode3(TRUE);

    if (do_bench_modeC16)
        get_results_modeC16(TRUE);

    if (do_bench_mode4)
        get_results_mode4(TRUE);

    if (do_bench_mode6)
        get_results_mode6(TRUE);

    if (do_bench_mode8)
        get_results_mode8(TRUE);

    if (do_bench_mode9)
        get_results_mode9(TRUE);

    if (do_bench_modeA)
        get_results_modeA(TRUE);

    if (do_bench_modePCP)
        get_results_modePCP(TRUE);

    if (do_bench_modeATI)
        get_results_modeATI(TRUE);

    if (do_bench_modeD)
        get_results_modeD(TRUE);

    if (do_bench_modeE)
        get_results_modeE(TRUE);

    if (do_bench_mode10)
        get_results_mode10(TRUE);

    if (do_bench_modeV16)
        get_results_modeV16(TRUE);

    if (do_bench_mode13)
        get_results_mode13(TRUE);

    if (do_bench_modeY)
        get_results_modeY(TRUE);

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
