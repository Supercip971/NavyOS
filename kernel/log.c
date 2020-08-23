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

int32_t
klog(Level level, char *format, ...)
{
    debug_print("[");
    debug_print(LOG_MSG[level]);
    debug_print("] ");

    va_list parameters;
    va_start(parameters, format);

    uint32_t written = 0;

    while(*format != '\0') {
        size_t maxrem = 2147483647 - written;

        if(format[0] != '%' || format[1] == '%') {
            if(format[0] == '%') {
                format++;
            }

            size_t amount = 1;
            while(format[amount] && format[amount] != '%') {
                amount++;
            }

            if(maxrem < amount) {
                // EOVERFLOW
                return -1;
            }

            debug_print(format);
            format += amount;
            written += amount;
            continue;
        }

        char *format_begun_at = format++;

        if(*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int);
            if(!maxrem) {
                // EOVERFLOW 
                return -1;
            }

            debug_print(&c);
            written++;

        } else if(*format == 's') {
            format++;
            
            const char *str = va_arg(parameters, const char *);
            size_t len = strlen(str);

            if(maxrem < len) {
                // EOVERFLOW
                return -1;
            }

            debug_print(str);
            written += len;

        } else if(*format == 'd') {
            format++;
            int d = (int) va_arg(parameters, int);

            char nbr[64];
            itoa(d, nbr, 10);
            size_t len = strlen(nbr);

            if(maxrem < len) {
                // EOVERFLOW
                return -1;
            }

            debug_print(nbr);
            written += len;

        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            
            if(maxrem < len) {
                return -1;
            }

            debug_print(format);

            written += len;
            format += len;
        }
    }

    debug_print("\n");
    va_end(parameters);
    return written;
}