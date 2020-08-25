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


#include "arch/x86/serial.h"
#include "arch/x86/io.h"


void
serial_init(Com com)
{
	outb(com + 1, 0x00);		// Disable all interrupts
	outb(com + 3, 0x80);		// Enable DLAB (set baud rate divisor)
	outb(com + 0, 0x03);		// Set divisor to 3 (lo byte) 38400 baud
	outb(com + 1, 0x00);		// (hi byte)
	outb(com + 3, 0x03);		// 8 bits, no parity, one stop bit
	outb(com + 2, 0xC7);		// Enable FIFO, clear them, with 14-byte
	// threshold
	outb(com + 4, 0x0B);		// IRQs enabled, RTS/DSR set
}


int32_t
is_transmit_empty(Com com)
{
	return inb(com + 5) & 0x20;
}


void
serial_putc(Com com, char c)
{
	while (is_transmit_empty(com) == 0);
	outb(com, c);
}

void
serial_print(Com com, const char *s)
{
	while (*s != 0)
	{
		serial_putc(com, *s++);
	}
}
