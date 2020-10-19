/*
 * Copyright (C) 2020  Jordan DALCQ & contributors
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


#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

char *
itoa(int32_t value, char *str, uint16_t base)
{
    size_t index = 0;
    int8_t digit;

    if (value < 0)
    {
        str[index++] = '-';
    }

    do
    {
        digit = value % base;

        value /= base;

        if (digit < 0xa)
        {
            str[index++] = digit + '0';
        }

        else
        {
            str[index++] = (digit - 0xa) + 'A';
        }

    }
    while (value);

    str[index] = '\0';
    str = strrev(str);

    return str;

}

int32_t
atoi(const char *nptr)
{
    bool is_negative = false;
    int32_t return_value = 0;
    size_t index = 0;

    if (nptr[index] == '-')
    {
        is_negative = true;
        nptr++;
    }

    while (nptr[index] != '\0')
    {
        uint16_t power = strlen(nptr) - index - 1;

        return_value += (nptr[index] - '0') * (uint32_t) pow(10, power);
        index++;
    }

    if (is_negative)
    {
        return_value *= -1;
    }

    return return_value;
}
