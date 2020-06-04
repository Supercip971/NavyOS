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


		for(uint8_t i = length; i > 0; i--) {
				digit = (value - (value % (uint32_t)pow(10, i-1)));
				value -= digit;
				buffer[length-i+negative] = (digit / (uint32_t)pow(10,i-1)) + '0';
		}
		
		buffer[length+negative] = '\0';
		return buffer;
}

