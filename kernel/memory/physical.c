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
#include "kernel/memory/physical.h"
#include "kernel/log.h"

#include "arch/arch.h"

#include <Navy/range.h>

size_t USED_MEMORY = 0;
size_t TOTAL_MEMORY = 0;

uint8_t page_bitmap[1024 * 1024 / 8] = { };

size_t best_bet = 0;

void
init_bitmap(void)
{
    size_t i;

    for (i = 0; i < 1024 * 1024 / 8; i++)
    {
        page_bitmap[i] = USED;
    }
}

bool
physical_page_is_used(uintptr_t addr)
{
    uintptr_t page = addr / PAGE_SIZE;

    return page_bitmap[page / 8] & (1 << (page % 8));
}

void
physical_page_set_used(uintptr_t addr)
{
    uintptr_t page = addr / PAGE_SIZE;

    if (page == best_bet)
    {
        best_bet++;
    }

    page_bitmap[page / 8] |= 1 << (page % 8);
}

void
physical_set_free(Range range)
{
    size_t i;
    uintptr_t addr;

    if (!is_range_page_aligned(range))
    {
        klog(ERROR, "Range not page aligned !\n");
        disable_interrupts();
        hlt();
    }

    for (i = 0; i < range.size / PAGE_SIZE; i++)
    {
        addr = range.begin + i * PAGE_SIZE;

        if (physical_page_is_used(addr))
        {
            USED_MEMORY -= PAGE_SIZE;
            physical_page_set_free(addr);
        }
    }
}

bool
physical_is_used(Range range)
{
    size_t i;
    uintptr_t addr;

    if (!is_range_page_aligned(range))
    {
        klog(ERROR, "RANGE NOT ALIGNED!\n");
        disable_interrupts();
        hlt();
    }

    for (i = 0; i < range.size / PAGE_SIZE; i++)
    {
        addr = range.begin + i * PAGE_SIZE;

        if (physical_page_is_used(addr))
        {
            return true;
        }
    }

    return false;
}

void
physical_set_used(Range range)
{
    size_t i;
    uintptr_t address;

    if (!is_range_page_aligned(range))
    {
        klog(ERROR, "This memory range is not page aligned ! (BEGIN: %d, SIZE: %d)\n",
             range.begin, range.size);
        disable_interrupts();
        hlt();
    }

    for (i = 0; i < range.size / PAGE_SIZE; i++)
    {
        address = range.begin + i * PAGE_SIZE;

        if (!physical_page_is_used(address))
        {
            USED_MEMORY += PAGE_SIZE;
            physical_page_set_used(address);
        }
    }
}

void
physical_page_set_free(uintptr_t addr)
{
    uintptr_t page = addr / PAGE_SIZE;

    if (page < best_bet)
    {
        best_bet = page;
    }

    page_bitmap[page / 8] &= ~(1 << (page % 8));
}

void
set_total_memory(size_t mem)
{
    TOTAL_MEMORY = mem;
}
