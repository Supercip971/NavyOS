/*
 * Copyright (C) 2020 Jordan DALCQ & contributors
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
#include "arch/arch.h"

#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static const char *LOG_MSG[] = {
    "\033[34mLOG\033[39m", "\033[31mERROR\033[39m", "\033[33mWARNING\033[39m",
    "\033[35mOK\033[39m "
};

void
klog(Level level, const char *format, ...)
{
    va_list ap;
    char pad[2];
    uint32_t padding = 0;
    const char *ptr = format;
    char nbr[64];

    bool is_parsing = false;

    va_start(ap, format);


    if (level != NONE)
    {
        debug_print("[ ");
        debug_print(LOG_MSG[level]);
        debug_print(" ] ");
    }

    while (*ptr)
    {
        if (*ptr == '%')
        {
            if (is_parsing)
            {
                debug_putc('%');
                ptr++;
                is_parsing = false;
            }

            else
            {
                is_parsing = true;
                ptr++;
                continue;
            }
        }

        if (*ptr == '0' && is_parsing)
        {
            pad[0] = *++ptr;
            pad[1] = '\0';
            padding = atoi(pad);
            ptr++;
        }

        if (*ptr == 's' && is_parsing)
        {
            debug_print(va_arg(ap, char *));

            is_parsing = false;
            ptr++;
        }

        if (*ptr == 'd' && is_parsing)
        {
            itoa(va_arg(ap, int), nbr, 10);

            while (padding && padding - strlen(nbr) > 0)
            {
                debug_print("0");
                padding--;
            }

            padding = 0;
            debug_print(nbr);
            is_parsing = false;
            ptr++;
        }

        if (*ptr == 'c' && is_parsing)
        {
            debug_putc((char) va_arg(ap, int));

            is_parsing = false;
            ptr++;
        }

        if (*ptr == 'x' && is_parsing)
        {
            itoa(va_arg(ap, int), nbr, 16);

            while (padding && padding - strlen(nbr) > 0)
            {
                debug_print("0");
                padding--;
            }

            padding = 0;
            debug_print(nbr);
            is_parsing = false;
        }

        else
        {
            debug_putc(*ptr);
        }

        ptr++;
    }
}
