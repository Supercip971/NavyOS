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

#define tofind "RSD PTR "

#include "arch/x86/rsdp.h"
#include <string.h>

uint8_t
check_rsdp(uint64_t addr)
{
    uint8_t sum = 0;
    size_t i;

    for(i = 0; i < 20; i++) {
        sum += *(uint8_t *)(addr + i);
    }

    return sum;

}

uint64_t 
find_rsdp()
{
    uint64_t location;
    uint64_t ebda_start = (*(uint16_t *)(0x40e)) << 4;

    for(location = 0; location < 0x400; location += 16) {
        if(!memcmp((char *) ebda_start + location, tofind, sizeof(tofind) - 1)) {
            if(check_rsdp(ebda_start + location)) {
                continue;
            }

            return ebda_start + location;
        }
    }

    for(location = 0; location < 0x20000; location += 16) {
        if(!memcmp((char *) 0xe0000 + location, tofind, sizeof(tofind) - 1)){ 
            if(check_rsdp(0xe0000 + location)) {
                continue;
            }

            return 0xe0000 + location;
        }
    }

    return 0;
}