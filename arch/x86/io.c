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

#include "arch/x86/io.h"

void
outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ("outb %0, %1"::"a" (val), "Nd"(port));
}


uint8_t
inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ("inb %1, %0":"=a" (ret):"Nd"(port));

    return ret;
}

uint16_t
inw(uint16_t port)
{
    uint16_t ret;
    __asm__ volatile ("inw %1, %0":"=a" (ret):"Nd"(port));

    return ret;
}

void
io_wait(void)
{
    __asm__ volatile ("jmp 1f\n\t" "1:jmp 2f\n\t" "2:");
}
