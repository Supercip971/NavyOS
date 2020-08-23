/*
 * Copyright (C) 2020 Jordan DALCQ & Contributors
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
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

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


char *
itoa(int32_t value, char *str, uint16_t base) // Took from OSDEV, my implementation was not good
{
    char * rc;
    char * ptr;
    char * low;
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    if ( value < 0 && base == 10 ) {
        *ptr++ = '-';
    }
    low = ptr;
    do
    {
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    *ptr-- = '\0';
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

int32_t 
atoi(const char *nptr)
{
    bool is_negative = false;
    int32_t return_value = 0;
    size_t index = 0;

    if(nptr[index] == '-') {
        is_negative = true;
        nptr++;
    }

    while(nptr[index] != '\0') {
        uint16_t power = strlen(nptr) - index - 1;
        return_value += (nptr[index] - '0') * (uint32_t) pow(10, power);
        index++;
    }

    if(is_negative) {
        return_value *= -1;
    }

    return return_value;
}