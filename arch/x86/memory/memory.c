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

#include "kernel/log.h"
#include "arch/arch.h"

#include "arch/x86/memory/memory.h"
#include "arch/x86/memory/paging.h"
#include "kernel/memory/alloc.h"
#include <macro.h>

#include <Navy/range.h>

#include <multiboot2.h>
#include <stddef.h>


size_t TOTAL_MEMORY = 0;
size_t USED_MEMORY = 0;

void
_parse_mmap(struct multiboot_tag_mmap *mmap)
{
    size_t i;
    uintptr_t lastaddr;
    struct multiboot_mmap_entry entry;
    Range mmap_range;

    lastaddr = (uintptr_t) mmap;
    for (i = 0; i < mmap->entry_size; i++)
    {
        entry = mmap->entries[i];

        if (entry.type == 1)
        {
            mmap_range.begin = lastaddr;
            mmap_range.end = lastaddr + entry.len;
            set_status_bitmap(mmap_range, FREE);
            TOTAL_MEMORY += entry.len;
        }

        if (entry.type == 5)
        {
            klog(ERROR, "BADRAM !\n");  /* Friendly TODO: MAKE A PANIC SCREEN */
            disable_interrupts();
            hlt();
        }
    }
}


void
init_memory(uint32_t addr)
{
    struct multiboot_tag_mmap *mmap =
        (struct multiboot_tag_mmap *) get_tag(MULTIBOOT_TAG_TYPE_MMAP, addr);

    _parse_mmap(mmap);

    klog(OK, "Available memory: %dMib\n", TOTAL_MEMORY / (1024 * 1024));
    init_paging();

}
