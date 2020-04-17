/*
 * Copyright (C) 2020 Jordan DALCQ & Contributors 
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
#include <math.h>

char* itoa(int32_t value, char *buffer, uint8_t base)
{
    bool        is_negative            = false;
    uint32_t    sanitized_value        = value;
    uint16_t    length                 = 1;
    uint32_t    digit;
    
    if(base != 10) {
        buffer[0] = '-';
        buffer[1] = '1';
        return buffer; // Yes I'm lazy
    }
    
    if(value < 0) {
        is_negative = true;
        buffer[0] = '-';
        sanitized_value *= -1;
    }

    while(sanitized_value >= (uint32_t)pow(10, length-1)) {
        digit = sanitized_value % (uint32_t)pow(10, length) / (uint32_t)pow(10, length-1);
        if(is_negative)
            buffer[length-2] = digit + '0';
        else
            buffer[length-1] = digit + '0';

        length++;
        sanitized_value -= digit;
    }

    buffer[length - 1] = '\0';
    
    return buffer;
}

