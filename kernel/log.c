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

#include "kernel/log.h"

#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static const char *LOG_MSG[] = {
    "\e[34mLOG\e[39m", "\e[31mERROR\e[39m", "\e[33mWARNING\e[39m"
};

void
klog(Level level, char *restrict format, ...)
{
    if(level != NONE) {
        debug_print("[ ");
        debug_print(LOG_MSG[level]);
        debug_print(" ] ");
    }

    va_list ap;
    va_start(ap, format);
    char *ptr = format;
    char nbr[64];

    while(*ptr) {
        if(*ptr == '%') {
            ptr++;

            switch(*ptr++) {
                case 's':
                    debug_print(va_arg(ap, char *));
                    break;
                case 'd':
                    itoa(va_arg(ap, int), nbr, 10);
                    debug_print(nbr);
                    break;
                case 'x':
                    itoa(va_arg(ap, int), nbr, 16);
                    debug_print(nbr);
                    break;
                case '%':
                    debug_putc('%');
                    break;
            }
        } else {
            debug_putc(*ptr++);
        }
    }

    debug_print("\n");
}