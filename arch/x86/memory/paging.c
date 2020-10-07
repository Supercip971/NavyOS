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


#include "arch/x86/memory/paging.h"
#include "kernel/memory/alloc.h"
#include "kernel/log.h"

#include <stdint.h>
#include <stddef.h>
#include <multiboot2.h>
#include <macro.h>

extern uint32_t __start;
extern uint32_t __end;

static struct PAGE_DIR page_dir __attribute__((aligned(PAGE_SIZE)));
static struct PAGE_TABLE page_table[256] __attribute__((aligned(PAGE_SIZE)));
size_t page_table_index = 0;

void
virtual_free(struct PAGE_DIR *page_dir, Range range)
{
    size_t i;
    size_t offset;
    size_t dir_index;
    size_t table_index;

    PageDirEntry *dir_entry;
    PageTableEntry *table_entry;
    struct PAGE_TABLE *table;

    for (i = 0; i < range.begin / PAGE_SIZE; i++)
    {
        offset = i * PAGE_SIZE;

        dir_index = __pd_index(range.begin + offset);
        dir_entry = &page_dir->entries[dir_index];

        table = (struct PAGE_TABLE *) (dir_entry->page_framenbr * PAGE_SIZE);

        table_index = __pt_index(range.begin + offset);
        table_entry = &table->entries[table_index];

        if (table_entry->present)
        {
            table_entry->as_uint = 0;
        }
    }
}

void
init_paging(void)
{
    Range kernel_range;
    Range page_zero;

    size_t i;
    PageDirEntry *dir_entry;

    kernel_range.begin = (uintptr_t) & __start;
    kernel_range.end = (uintptr_t) & __end;

    page_zero.begin = 0;
    page_zero.end = PAGE_SIZE;

    for (i = 0; i < 256; i++)
    {
        dir_entry = &page_dir.entries[i];

        dir_entry->user_supervisor = 0;
        dir_entry->read_write = 1;
        dir_entry->present = 1;
        dir_entry->page_framenbr = (size_t) &page_table[i] / 4096;
    }

    map_memory(kernel_range, KERNEL);
    klog(OK, "Kernel mapped\n");

    virtual_free(&page_dir, page_zero);
    set_status_bitmap(page_zero, USED);

    _asm_load_pagedir(page_dir.entries);
    _asm_init_paging();
}


bool
is_virtual_free(struct PAGE_DIR *page_dir, uintptr_t addr)
{
    size_t directory_index;
    size_t table_index;
    PageDirEntry page_dir_entry;
    PageTableEntry page_table_entry;
    struct PAGE_TABLE *page_table;

    directory_index = __pd_index(addr);
    page_dir_entry = page_dir->entries[directory_index];

    if (!page_dir_entry.present)
    {
        return false;
    }

    page_table = (struct PAGE_TABLE *) (page_dir_entry.page_framenbr * PAGE_SIZE);
    table_index = __pt_index(addr);
    page_table_entry = page_table->entries[table_index];

    return !page_table_entry.present;
}

/*
int 
memory_alloc_identity(struct PAGE_DIR *page_dir, Mode mode, uintptr_t *out_addr)
{
    size_t i;

    for(i = 1; i < 256 * 1024; i++)
    {
        Range mem_range;
        mem_range.begin = i * PAGE_SIZE;
        mem_range.end = PAGE
    }
}*/

int
virtual_map(struct PAGE_DIR *page_dir, Range range, uintptr_t addr, Mode mode)
{
    size_t i;
    size_t offset;
    size_t dir_index;
    size_t table_index;

    int success;

    PageDirEntry dir_entry;
    PageTableEntry table_entry;
    struct PAGE_TABLE *table;

    __unused(table_entry);

    for (i = 0; i < get_range_size(range) / PAGE_SIZE; i++)
    {
        offset = i * PAGE_SIZE;
        dir_index = __pd_index(addr + offset);
        dir_entry = page_dir->entries[dir_index];

        table = (struct PAGE_TABLE *) (dir_entry.page_framenbr * PAGE_SIZE);

        if (!dir_entry.present)
        {
            /* success = memory_alloc_identity(page_dir, CLEAR, (uintptr_t) &page_table);  */

            dir_entry.present = 1;
            dir_entry.read_write = 1;
            dir_entry.user_supervisor = 1;  /* TODO Will need to double check that in the 
                                             * future */
            dir_entry.page_framenbr = (uint32_t) (table) >> 12;
        }

        table_index = __pt_index(addr + offset);
        table_entry = table->entries[table_index];

        table_entry.present = 1;
        table_entry.read_write = 1;
        table_entry.user_supervisor = mode & USER;
        table_entry.page_framenbr = (range.begin + offset) >> 12;
    }

    _asm_reload_pagedir();
    return 0;
}

void
map_memory(Range range, Mode mode)
{
    size_t i;
    uintptr_t virt_addr;
    Range physical_range;

    if (!is_range_page_aligned(range))
    {
        klog(ERROR, "This memory range page aligned !");
        disable_interrupts();
        hlt();
    }

    klog(OK, "%d\n", get_range_size(range));
    for (i = 0; i < get_range_size(range) / PAGE_SIZE; i++)
    {
        virt_addr = range.begin + i * PAGE_SIZE;
        klog(LOG, "%d\n", i);

        if (is_virtual_free(&page_dir, virt_addr))
        {
            physical_range = allocate_memory(PAGE_SIZE);
            if (virtual_map(&page_dir, physical_range, virt_addr, mode))
            {
                klog(ERROR, "Couldn't map memory !\n");
                disable_interrupts();
                hlt();
            }
        }
    }

}
