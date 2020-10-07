/*
 * Copyright (C) 2020  Jordan DALCQ & contributors 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "arch/arch.h"
#include "kernel/memory/alloc.h"
#include "kernel/log.h"

#include "arch/arch.h"

#include <Navy/range.h>

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
set_status_bitmap(Range range, uint8_t status)
{
    size_t start_bitmap;
    size_t end_bitmap;
    size_t i;

    start_bitmap = (range.begin / PAGE_SIZE) / 8;
    end_bitmap = (range.end / PAGE_SIZE) / 8;

    for (i = start_bitmap; i < end_bitmap; i++)
    {
        page_bitmap[i] = status;
    }
}

size_t
get_index_bitmap(uintptr_t addr)
{
    return (addr / PAGE_SIZE) / 8;
}

Range
allocate_memory(size_t size)
{
    size_t i;
    Range range;
    size_t pagenbr;
    size_t free_page = 0;

    if (!is_page_aligned(size))
    {
        klog(ERROR, "NOT ALIGNED !!!");
        disable_interrupts();
        hlt();
    }

    pagenbr = free_page / PAGE_SIZE;

    for (i = 0; i < BITLENGTH && free_page < pagenbr; i++)
    {
        if (page_bitmap[i] == FREE)
        {
            if (free_page == 0)
            {
                range.begin = i * 8;
            }

            free_page++;
        }

        else
        {
            free_page = 0;
        }
    }

    if (page_bitmap[BITLENGTH - 1] == USED)
    {
        klog(ERROR, "MEMORY FULL !\n");
        disable_interrupts();
        hlt();
    }

    range.end = i * 8;
    set_status_bitmap(range, USED);

    return range;
}
