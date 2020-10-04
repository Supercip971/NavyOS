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

#include "kernel/memory/alloc.h"

uint8_t page_bitmap[BITLENGTH];

void
init_bitmap(void)
{
    size_t i;

    for (i = 0; i < BITLENGTH / 8; i++)
    {
        page_bitmap[i] = USED;
    }
}

void
set_status_bitmap(uintptr_t start, uintptr_t end, uint8_t status)
{
    size_t start_bitmap;
    size_t end_bitmap;
    size_t i;

    start_bitmap = (start / 4096) / 8;
    end_bitmap = (end / 4096) / 8;

    for (i = start_bitmap; i < end_bitmap; i++)
    {
        page_bitmap[i] = status;
    }
}

size_t
get_index_bitmap(uintptr_t addr)
{
    return (addr / 4096) / 8;
}

uintptr_t
allocate_page(size_t pagenbr)
{
    size_t i;
    uintptr_t addr;
    size_t free_page = 0;

    for (i = 0; i < BITLENGTH; i++)
    {
        if (page_bitmap[i] == FREE)
        {
            free_page++;
        }

        else
        {
            free_page = 0;
        }

        if (free_page == pagenbr)
        {
            break;
        }
    }

    addr = i * 8;
    set_status_bitmap(addr, addr + (8 * pagenbr), USED);

    return addr;
}
