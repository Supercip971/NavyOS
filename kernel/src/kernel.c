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


#include <navy/warning.h>
#include <navy/vga.h>
#include <stdlib.h>

void
kmain(void)
{  
    char buffer[5];
	char bin[32];
	char hex[5];

    itoa(42, buffer, 10);
	itoa(42, bin, 2);
	itoa(42, hex, 16);

    term_init();
    term_puts("Hello Navy !\n", LIGHT_GREY, BLACK);
	term_puts(bin, GREEN, BLACK);
	term_puts("\n", WHITE, BLACK);
	term_puts(hex, RED, BLACK);
}

