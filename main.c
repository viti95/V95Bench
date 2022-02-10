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

#include "main.h"
#include "mode4.h"
#include "mode13.h"
#include "modeD.h"
#include "modeE.h"
#include "modeF.h"
#include "modePCP.h"
#include "modeHGC.h"
#include "modeATI.h"

int videomode;

unsigned char do_bench_mode4 = 0;
unsigned char do_bench_mode13 = 0;
unsigned char do_bench_modeD = 0;
unsigned char do_bench_modeE = 0;
unsigned char do_bench_modeF = 0;
unsigned char do_bench_modePCP = 0;
unsigned char do_bench_modeHGC = 0;
unsigned char do_bench_modeATI = 0;

void launch_bench_mode4(void){
    do_bench_mode4 = 1;
    execute_bench_mode4();
}

void launch_bench_mode13(void){
    do_bench_mode13 = 1;
    execute_bench_mode13();
}

void launch_bench_modeD(void){
    do_bench_modeD = 1;
    execute_bench_modeD();
}

void launch_bench_modeE(void){
    do_bench_modeE = 1;
    execute_bench_modeE();
}

void launch_bench_modeF(void){
    do_bench_modeF = 1;
    execute_bench_modeF();
}

void launch_bench_modePCP(void){
    do_bench_modePCP = 1;
    execute_bench_modePCP();
}

void launch_bench_modeHGC(void){
    do_bench_modeHGC = 1;
    execute_bench_modeHGC();
}

void launch_bench_modeATI(void){
    do_bench_modeATI = 1;
    execute_bench_modeATI();
}

void select_benchmark(void)
{
    switch (videomode)
    {
    case MDA:
        break;
    case HGC:
        launch_bench_modeHGC();
        break;
    case CGA:
        launch_bench_mode4();
        break;
    case EGA:
        launch_bench_mode4();
        launch_bench_modeD();
        launch_bench_modeE();
        launch_bench_modeF();
        break;
    case MCGA:
        launch_bench_mode4();
        launch_bench_mode13();
        break;
    case VGA:
        launch_bench_mode4();
        launch_bench_modeD();
        launch_bench_modeE();
        launch_bench_modeF();
        launch_bench_mode13();
        break;
    case VESA:
        break;
    case Tandy:
        break;
    case PCjr:
        break;
    case ATI:
        launch_bench_mode4();
        launch_bench_modePCP();
        launch_bench_modeATI();
        break;
    case Plantronics:
        launch_bench_mode4();
        launch_bench_modePCP();
        break;
    default:
        printf("Invalid option :(");
        return;
    }
}

void reset_video(void){

    union REGS regs;

    if (videomode == HGC)
    {
        regs.w.ax = 7;
    }else{
        regs.w.ax = 3;
    }

    int386(0x10, &regs, &regs); // back to text mode
}

void show_results(void){

    if (do_bench_modeHGC)
        show_results_modeHGC();

    if (do_bench_mode4)
        show_results_mode4();

    if (do_bench_modePCP)
        show_results_modePCP();

    if (do_bench_modeATI)
        show_results_modeATI();

    if (do_bench_modeD)
        show_results_modeD();

    if (do_bench_modeE)
        show_results_modeE();

    if (do_bench_modeF)
        show_results_modeF();

    if (do_bench_mode13)
        show_results_mode13();

}

int main(int argc, char **argv)
{
    printf("\n");
    printf(" =====================\n");
    printf(" = V95 GPU Benchmark =\n");
    printf(" =====================\n");
    printf("\n");
    printf(" Please select video card:\n");
    printf("\n");
    printf("    1.  MDA\n");
    printf("    2.  Hercules\n");
    printf("    3.  CGA\n");
    printf("    4.  EGA\n");
    printf("    5.  MCGA\n");
    printf("    6.  VGA\n");
    printf("    7.  VESA\n");
    printf("    8.  Tandy\n");
    printf("    9.  IBM PCjr\n");
    printf("    10. ATI Small Wonder\n");
    printf("    11. Plantronics ColorPlus\n");
    printf("\n");

    printf(" Select option: ");
    scanf("%d", &videomode);

    select_benchmark();

    reset_video();

    show_results();

    return 0;
}


