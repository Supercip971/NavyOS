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

#include "kernel/log.h"

#include "arch/arch.h"

#include "arch/x86/memory/memory.h"
#include "arch/x86/memory/paging.h"
#include "kernel/memory/alloc.h"

#include <multiboot2.h>
#include <stddef.h>

extern uint32_t __start;
extern uint32_t __end;

void
_parse_mmap(struct multiboot_tag_mmap *mmap)
{
    size_t i;
    uintptr_t lastaddr;
    struct multiboot_mmap_entry entry;

    lastaddr = (uintptr_t) mmap;
    for (i = 0; i < mmap->entry_size; i++)
    {
        entry = mmap->entries[i];

        if (entry.type == 1)
        {
            set_status_bitmap(lastaddr, lastaddr + entry.len, FREE);
        }

        if (entry.type == 5)
        {
            klog(ERROR, "BADRAM !\n");  /* Friendly todo: MAKE A PANIC SCREEN */
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

    init_paging();
    klog(OK, "Paging enabled !");

    set_status_bitmap((uintptr_t) & __start, (uintptr_t) & __end, USED);
    _parse_mmap(mmap);
}
