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

#include "messages.h"

const char MSG_MODE1_8BIT[]    = "TXT 40x25 16c: W8  %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODE3_8BIT[]    = "TXT 80x25 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODE4_8BIT[]    = "CGA 320x200 4c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODE6_8BIT[]    = "CGA 640x200 2c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODE7_8BIT[]    = "TXT 80x25 2c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODE8_8BIT[]    = "PCjr/Tandy 160x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODE9_8BIT[]    = "PCjr/Tandy 320x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODE10_8BIT[]   = "EGA 640x350 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODE13_8BIT[]   = "VGA 320x200 256c (13h): W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODEATI_8BIT[]  = "ATI 640x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODEC16_8BIT[]  = "CGA 160x100 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODED_8BIT[]    = "EGA 320x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODEE_8BIT[]    = "EGA 640x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODEHGC_8BIT[]  = "HGC 640x400 2c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODEPCP_8BIT[]  = "PCP 320x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODEV16_8BIT[]  = "VGA 160x200 16c: W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_MODEY_8BIT[]    = "VGA 320x200 256c (Y): W8 %.2lf kb/s, R8 %.2lf kb/s\n";
const char MSG_GENERIC_16BIT[] = "                        W16 %.2lf kb/s, R16 %.2lf kb/s\n";
const char MSG_GENERIC_32BIT[] = "                        W32 %.2lf kb/s, R32 %.2lf kb/s\n";
