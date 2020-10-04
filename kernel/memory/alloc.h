/*
 * Copyright (C) 2020 Jordan DALCQ & contributors
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.  
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _NAVY_X86_ALLOC_H
#define _NAVY_X86_ALLOC_H

#include <stdint.h>
#include <stddef.h>

#define FREE    0x00
#define USED    0xff
#define BITLENGTH 0x10000

void init_bitmap(void);
void set_status_bitmap(uintptr_t, uintptr_t, uint8_t);
size_t get_index_bitmap(uintptr_t);

uintptr_t allocate_memory(size_t);

#endif
