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

#include "arch/x86/memory/paging.h"
#include "kernel/memory/alloc.h"
#include "kernel/log.h"

#include <stdint.h>
#include <stddef.h>
#include <macro.h>
#include <multiboot2.h>


static struct PAGE_DIR page_dir __attribute__((aligned(4096)));
static struct PAGE_TABLE page_table[256] __attribute__((aligned(4096)));


void
__init_page_dir(struct PAGE_DIR *page_dir)
{
    size_t i;

    for (i = 0; i < 256; i++)
    {
        page_dir->entries[i].present = 1;
        page_dir->entries[i].read_write = 1;
        page_dir->entries[i].user_supervisor = 0;
        page_dir->entries[i].page_framenbr = (uintptr_t) (&page_table[i]) >> 12;
    }
}


void
__paging_ident(struct PAGE_TABLE *page_table, size_t index)
{
    size_t i;

    for (i = 0; i < 1024; i++)
    {
        page_table->entries[i].read_write = 1;
        page_table->entries[i].user_supervisor = 0;
        page_table->entries[i].page_framenbr = index * 1024 + i;
        page_table->entries[i].present = 1;
    }
}


void
init_paging(void)
{
    size_t i;

    __init_page_dir(&page_dir);
    for (i = 0; i < 256; i++)
    {
        __paging_ident(&page_table[i], i);
    }

    _asm_load_pagedir(page_dir.entries);
    _asm_init_paging();
}

/*
 * TODO + Physical2Virtual & Vice Versa void allocate_page(size_t pagenbr) { uintptr_t
 * addr;
 * 
 * addr = allocate_memory(pagenbr); } 
 */
