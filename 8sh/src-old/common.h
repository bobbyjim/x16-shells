/*
  
    8SH: a command interpreter for 8 bit 'retro' systems.
    Copyright (C) 2020 Robert Eaglestone

    This file is part of 8SH.

    8SH is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    8SH is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with 8SH.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef _common_h
#define _common_h

#include <stdbool.h>
#include <stdint.h>

#define DEBUG_PRINT_CODE
#define DEBUG_TRACE_EXECUTION
#define UINT8_COUNT (UINT8_MAX + 1)


//#undef DEBUG_PRINT_CODE
//#undef DEBUG_TRACE_EXECUTION

#define BLACK           0
#define WHITE           1
#define RED             2
#define CYAN            3
#define PURPLE          4
#define GREEN           5
#define BLUE            6
#define YELLOW          7
#define AMBER           8
#define LTRED           10
#define LTGREEN         13
#define LTBLUE          14
#define LTGREY          15

void logo(uint8_t x, uint8_t y);
#endif

