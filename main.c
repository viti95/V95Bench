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
#include <time.h>
#include <dos.h>

#include "main.h"
#include "cga.h"

int videomode;

void select_benchmark(void)
{

    switch (videomode)
    {
    case MDA:
        break;
    case HGC:
        break;
    case CGA:
        execute_bench_CGA_mode4();
        break;
    case EGA:
        break;
    case MCGA:
        break;
    case VGA:
        break;
    case VESA:
        break;
    case Tandy:
        break;
    case PCjr:
        break;
    case ATI:
        break;
    case Plantronics:
        break;
    default:
        printf("Invalid option :(");
        return;
    }
}

void reset_video(void){

    union REGS regs;

    regs.w.ax = 3;
    int386(0x10, &regs, &regs); // back to text mode
}

void show_results(void){

    switch (videomode)
    {
    case MDA:
        break;
    case HGC:
        break;
    case CGA:
        show_results_CGA_mode4();
        break;
    case EGA:
        break;
    case MCGA:
        break;
    case VGA:
        break;
    case VESA:
        break;
    case Tandy:
        break;
    case PCjr:
        break;
    case ATI:
        break;
    case Plantronics:
        break;
    default:
        printf("Invalid option :(");
        return;
    }

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


