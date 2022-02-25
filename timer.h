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

#ifndef __TIMER_H__
#define __TIMER_H__

extern unsigned char read_fix_8b_1, read_fix_8b_2, read_fix_8b_3, read_fix_8b_4, read_fix_8b_5, read_fix_8b_6, read_fix_8b_7, read_fix_8b_8;
extern unsigned short read_fix_16b_1, read_fix_16b_2, read_fix_16b_3, read_fix_16b_4, read_fix_16b_5, read_fix_16b_6, read_fix_16b_7, read_fix_16b_8;

#ifdef __386__
extern unsigned int read_fix_32b_1, read_fix_32b_2, read_fix_32b_3, read_fix_32b_4, read_fix_32b_5, read_fix_32b_6, read_fix_32b_7, read_fix_32b_8;
#endif

unsigned long profile_function(void (*exec_function)(void));
unsigned long profile_function_loops(void (*exec_function)(unsigned long), unsigned long loops);

#endif
