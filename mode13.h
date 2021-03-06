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

#ifndef __MODE13_H__
#define __MODE13_H__

void init_mode13(void);
void preheat_mode13(unsigned long total_loops);
void bench_w8_mode13(void);
void bench_r8_mode13(void);
void bench_w16_mode13(void);
void bench_r16_mode13(void);
void bench_w32_mode13(void);
void bench_r32_mode13(void);
void execute_bench_mode13(void);
void get_results_mode13(unsigned char to_file);

#endif
