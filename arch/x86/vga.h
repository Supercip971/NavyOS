/*
 * Copyright (C) 2020 Jordan DALCQ & contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _NAVY_X86_VGA_H
#define _NAVY_X86_VGA_H
#define GDTSIZE 5

#include <stdint.h>				// We need our types

enum VGA_COLOR
{
	BLACK = 0x0,
	BLUE = 0x1,
	GREEN = 0x2,
	CYAN = 0x3,
	RED = 0x4,
	MAGENTA = 0x5,
	BROWN = 0x6,
	LIGHT_GREY = 0x7,
	DARK_GREY = 0x8,
	LIGHT_BLUE = 0x9,
	LIGT_GREEN = 0xA,
	LIGHT_CYAN = 0xB,
	LIGHT_RED = 0xC,
	LIGHT_MAGENTA = 0xD,
	LIGHT_BROWN = 0xE,
	WHITE = 0xF,
};

typedef enum VGA_COLOR Colors;

static const uint8_t VGA_COL = 80;
static const uint8_t VGA_ROW = 25;
static const Colors DEFAULT_FGCOLOR = LIGHT_GREY;
static const Colors DEFAULT_BGCOLOR = BLACK;

void term_init(void);
void term_clear(void);
void term_putc(char, Colors, Colors);	// This function allows to put a char
void term_puts(char *, Colors, Colors);	// That one for strings, x and y is
										// the start position
void term_shift(void);
void move_cursor(uint8_t, uint8_t);
void movcur(uint8_t, uint8_t);

#endif
