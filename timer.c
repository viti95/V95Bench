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

#include <time.h>

#include "timer.h"

clock_t start, stop;
unsigned char read_fix_1, read_fix_2, read_fix_3, read_fix_4, read_fix_5, read_fix_6, read_fix_7, read_fix_8;

unsigned long profile_function(void (*exec_function)(void))
{
    start = clock();

    exec_function();

    stop = clock();
    return (stop - start) / (CLOCKS_PER_SEC / 1000);
}

unsigned long profile_function_loops(void (*exec_function)(unsigned long), unsigned long loops)
{
    start = clock();

    exec_function(loops);

    stop = clock();
    return (stop - start) / (CLOCKS_PER_SEC / 1000);
}
