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

#include <stdio.h>
#include <stddef.h>

#include "arch/arch.h"
#include "kernel/log.h"

int
getc(void)
{
    return (int) kbd_getc();
}

char *
gets(char *s)
{
    size_t i;

    while(kbd_lastKeyCode() != 28)
    {
        s[i] = getc();
        vga_putc(s[i]);
        klog(LOG, "%d\n", s[i]);
        i++;  
    }

    return s;
}