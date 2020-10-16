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


#ifndef NAVY_LIB_RANGE_H
#define NAVY_LIB_RANGE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct RANGE
{
    uintptr_t begin;
    uintptr_t end;
} Range;

bool is_range_page_aligned(Range);
size_t get_range_size(Range);
void align_range(Range *);

#endif
