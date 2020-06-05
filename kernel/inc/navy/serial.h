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


#ifndef _NAVY_SERIAL_H
#define _NAVY_SERIAL_H

#include <stdint.h>

enum SERIAL_COM {
	COM1	=	0x3f8,
	COM2	=	0x2f8,
	COM3	=	0x3e8,
	COM4	=	0x2e8,
};

typedef enum SERIAL_COM Com;

void serial_init(Com com);
void serial_putc(Com com, char c);
void serial_print(Com com, char* s);
int32_t is_transmit_empty(Com com);

#endif
