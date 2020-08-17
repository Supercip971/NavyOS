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
#include <string.h>
#include <math.h>

#include <navy/serial.h>


char *
itoa(int32_t value, char buffer[], uint16_t base)
{
    uint8_t length = 0;
    int32_t n = value;
    bool negative = false;

    uint32_t digit;

    do {
        length++;
        n /= base;
    } while(n);

    if(value < 0) {
        negative = true;
        buffer[0] = '-';
        value *= -1;
    }

    if(base != 10) {
        if(base > 16 || base < 2) {
            char error[12];
            itoa(base, error, 10);
            serial_println(COM1, strcat("[ STDLIB.H : ITOA() ] Unknown base : ", error));
            return buffer;
        }
        else {
            uint8_t i = 0;
            uint8_t j = 0;
            uint8_t index = 0;

            char tmp;

            while(value > 0) {
                if((value % base) < 10)
                    buffer[index++] = (value % base) + '0';
                else
                    buffer[index++] = (value % base) + '7';

                value /= base;
            }

            if(negative)
                buffer[index++] = '-';

            j = index-1;

            while(i < index) {
                tmp = buffer[j];
                buffer[j] = buffer[i];
                buffer[i] = tmp;

                i++;
                j--;
            }

            buffer[index] = '\0';
            return buffer;
        }

    }


    for(uint8_t i = length; i > 0; i--) {
        digit = (value - (value % (uint32_t)pow(10, i-1)));
        value -= digit;
        buffer[length-i+negative] = (digit / (uint32_t)pow(10,i-1)) + '0';
    }

    buffer[length+negative] = '\0';

    return buffer;
}

